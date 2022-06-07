/*************************************************************************
 * Copyright (C) 2022 Blue Brain Project
 *
 * This file is part of NMODL distributed under the terms of the GNU
 * Lesser General Public License. See top-level LICENSE file for details.
 *************************************************************************/

#pragma once

/**
 * \file
 * \brief \copybrief nmodl::visitor::LtiSolverVisitor
 */

#include "ast/ast.hpp"
#include "visitors/ast_visitor.hpp"

namespace nmodl {
namespace visitor {

/**
 * @addtogroup visitor_classes
 * @{
 */

/**
 * \class LtiSolverVisitor
 * \brief %Visitor for linear & time-invariant systems of differential equations
 *
 */
class LtiSolverVisitor: public AstVisitor {
  private:
    std::string nmodl_filename;
    std::string data_type;
    std::string target;
    std::string verbose;

  public:
    explicit LtiSolverVisitor(std::string nmodl_filename, std::string data_type,
                              std::string target, std::string verbose):
                  nmodl_filename(nmodl_filename),
                  data_type(data_type),
                  target(target),
                  verbose(verbose) {};

    void visit_solve_block(ast::SolveBlock& node) override;
    void visit_program(ast::Program& node) override;
};

/** @} */  // end of visitor_classes

}  // namespace visitor
}  // namespace nmodl
