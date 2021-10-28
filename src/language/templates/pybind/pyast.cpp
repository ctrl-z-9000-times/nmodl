/*************************************************************************
 * Copyright (C) 2018-2021 Blue Brain Project
 *
 * This file is part of NMODL distributed under the terms of the GNU
 * Lesser General Public License. See top-level LICENSE file for details.
 *************************************************************************/

///
/// THIS FILE IS GENERATED AT BUILD TIME AND SHALL NOT BE EDITED.
///

#include "pybind/pyast.hpp"

#include <pybind11/pybind11.h>

/**
 * \file
 * \brief All AST classes for Python bindings
 */
void init_ast_module(pybind11::module& m) {
    pybind11::module ast_module =
        m.def_submodule("ast", "Abstract Syntax Tree (AST) related implementations");
    nmodl::ast::impl::init_BinaryOp(ast_module);
    nmodl::ast::impl::init_AstNodeType(ast_module);
    auto const ast_class = nmodl::ast::impl::init_Ast(ast_module);
    {% for node in nodes %}
    auto const {{node.class_name | snake_case}}_class = nmodl::ast::impl::init_{{node.class_name}}(ast_module, {{node.base_class | snake_case}}_class);
    {% endfor %}
}
