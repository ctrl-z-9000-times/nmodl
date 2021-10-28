/*************************************************************************
 * Copyright (C) 2021 Blue Brain Project
 *
 * This file is part of NMODL distributed under the terms of the GNU
 * Lesser General Public License. See top-level LICENSE file for details.
 *************************************************************************/

///
/// THIS FILE IS GENERATED AT BUILD TIME AND SHALL NOT BE EDITED.
///

#include "pybind/pyast.hpp"
#include "pybind/pyast_docstrings.hpp"
#include "ast/ast_common.hpp"

#include <pybind11/pybind11.h>

namespace nmodl {
namespace ast {
namespace impl {
void init_AstNodeType(pybind11::module const& ast) {
    pybind11::enum_<AstNodeType>(ast, "AstNodeType", docstring::ast_nodetype_enum)
    // clang-format off
    {% for node in nodes %}
        .value("{{node.class_name | snake_case | upper}}", AstNodeType::{{node.class_name | snake_case | upper}}, "AST node of type ast.{{node.class_name}}")
    {% endfor %}
        .export_values();
    // clang-format on
}
}  // namespace impl
}  // namespace ast
}  // namespace nmodl
