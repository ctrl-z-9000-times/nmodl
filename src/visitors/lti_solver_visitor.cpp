/*************************************************************************
 * Copyright (C) 2022 Blue Brain Project
 *
 * This file is part of NMODL distributed under the terms of the GNU
 * Lesser General Public License. See top-level LICENSE file for details.
 *************************************************************************/

#include "visitors/lti_solver_visitor.hpp"

#include "ast/all.hpp"
#include "parser/nmodl_driver.hpp"
#include "pybind/pyembed.hpp"
#include "symtab/symbol.hpp"
#include "utils/logger.hpp"
#include "visitors/visitor_utils.hpp"


namespace pywrap = nmodl::pybind_wrappers;

namespace nmodl {
namespace visitor {

void LtiSolverVisitor::visit_solve_block(ast::SolveBlock& node) {
    using nmodl::ast::Name;
    using nmodl::ast::String;

    // Use the sparse solver as the intial steadystate solver.
    auto steadystate = node.get_steadystate();
    if (steadystate && steadystate.get()->get_node_name() == "lti") {
        node.set_steadystate(std::make_shared<Name>(Name(new String("sparse"))));
    }

    // Replace the solve block with a new block that calls the lti solver.
    auto method = node.get_method();
    if (method && method.get()->get_node_name() == "lti") {
        node.set_block_name(std::make_shared<Name>(Name(new String("lti_verbatim_shim"))));
    }
}

void LtiSolverVisitor::visit_program(ast::Program& node) {
    // Go to python and call the lti-sim program.
    const auto deleter = [](nmodl::pybind_wrappers::LtiSolverExecutor* ptr) {
        pywrap::EmbeddedPythonLoader::get_instance().api()->destroy_lti_executor(ptr);
    };
    std::unique_ptr<nmodl::pybind_wrappers::LtiSolverExecutor, decltype(deleter)> lti_solver{
        pywrap::EmbeddedPythonLoader::get_instance().api()->create_lti_executor(), deleter};
    // Inputs to python wrapper
    lti_solver->nmodl_filename  = nmodl_filename;
    lti_solver->data_type       = data_type;
    lti_solver->target          = target;
    lti_solver->verbose         = verbose;

    (*lti_solver)(); // Execute python wrapper.

    auto exception_message = lti_solver->exception_message;
    if (!exception_message.empty()) {
        logger->error("LtiSolverVisitor :: python exception: " + exception_message);
        return;
    }

    node.visit_children(*this);

    // Generate an AST containing the solver and the code to call it.
    nmodl::parser::NmodlDriver driver;
    auto solver_ast = driver.parse_string(R"(
        DERIVATIVE lti_verbatim_shim {
            VERBATIM
)" + lti_solver->call_solver + R"(
            ENDVERBATIM
        }

        VERBATIM
)" + lti_solver->impl_solver + R"(
        ENDVERBATIM
    )");
    // Append the solver and the shim to end of the program.
    for (auto& block : solver_ast->get_blocks()) {
        node.emplace_back_node(block);
        block->set_parent(&node);
    }

    // TODO: Include assert statements in the shim to verify that dt & C are correct?
}

}  // namespace visitor
}  // namespace nmodl
