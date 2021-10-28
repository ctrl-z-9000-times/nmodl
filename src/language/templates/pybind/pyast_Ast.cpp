/*************************************************************************
 * Copyright (C) 2021 Blue Brain Project
 *
 * This file is part of NMODL distributed under the terms of the GNU
 * Lesser General Public License. See top-level LICENSE file for details.
 *************************************************************************/
#include "pybind/pyast.hpp"
#include "pybind/pyast_docstrings.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

namespace nmodl {

namespace ast {
namespace impl {
py::class_<Ast, PyAst, std::shared_ptr<Ast>> init_Ast(py::module const& ast) {
    py::class_<Ast, PyAst, std::shared_ptr<Ast>> ast_{ast, "Ast", docstring::ast_class};
    ast_.def(py::init<>())
        .def("visit_children",
             static_cast<void (Ast::*)(visitor::Visitor&)>(&Ast::visit_children),
             "v"_a,
             docstring::visit_children_method)
        .def("accept",
             static_cast<void (Ast::*)(visitor::Visitor&)>(&Ast::accept),
             "v"_a,
             docstring::accept_method)
        .def("accept",
             static_cast<void (Ast::*)(visitor::ConstVisitor&) const>(&Ast::accept),
             "v"_a,
             docstring::accept_method)
        .def("get_node_type", &Ast::get_node_type, docstring::get_node_type_method)
        .def("get_node_type_name", &Ast::get_node_type_name, docstring::get_node_type_name_method)
        .def("get_node_name", &Ast::get_node_name, docstring::get_node_name_method)
        .def("get_nmodl_name", &Ast::get_nmodl_name, docstring::get_nmodl_name_method)
        .def("get_token", &Ast::get_token, docstring::get_token_method)
        .def("get_symbol_table",
             &Ast::get_symbol_table,
             py::return_value_policy::reference,
             docstring::get_symbol_table_method)
        .def("get_statement_block",
             &Ast::get_statement_block,
             docstring::get_statement_block_method)
        .def("clone", &Ast::clone, docstring::clone_method)
        .def("negate", &Ast::negate, docstring::negate_method)
        .def("set_name", &Ast::set_name, docstring::set_name_method)
        .def("is_ast", &Ast::is_ast, docstring::is_ast_method)
    // clang-format off
    {% for node in nodes %}
        .def("is_{{node.class_name | snake_case}}", &Ast::is_{{node.class_name | snake_case}}, "Check if node is of type ast.{{node.class_name}}")
    {% if loop.last -%};{% endif %}
    {% endfor %}
    // clang-format on

    return ast_;
}
}  // namespace impl
}  // namespace ast
}  // namespace nmodl
