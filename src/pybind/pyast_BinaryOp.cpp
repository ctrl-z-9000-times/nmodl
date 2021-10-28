/*************************************************************************
 * Copyright (C) 2021 Blue Brain Project
 *
 * This file is part of NMODL distributed under the terms of the GNU
 * Lesser General Public License. See top-level LICENSE file for details.
 *************************************************************************/
#include "ast/ast_common.hpp"
#include "pybind/pyast.hpp"
#include "pybind/pyast_docstrings.hpp"

#include <pybind11/pybind11.h>

namespace nmodl {
namespace ast {
namespace impl {
void init_ast_module_BinaryOp(pybind11::module const& ast) {
    pybind11::enum_<BinaryOp>(ast, "BinaryOp", docstring::binary_op_enum)
        .value("BOP_ADDITION", BinaryOp::BOP_ADDITION)
        .value("BOP_SUBTRACTION", BinaryOp::BOP_SUBTRACTION)
        .value("BOP_MULTIPLICATION", BinaryOp::BOP_MULTIPLICATION)
        .value("BOP_DIVISION", BinaryOp::BOP_DIVISION)
        .value("BOP_POWER", BinaryOp::BOP_POWER)
        .value("BOP_AND", BinaryOp::BOP_AND)
        .value("BOP_OR", BinaryOp::BOP_OR)
        .value("BOP_GREATER", BinaryOp::BOP_GREATER)
        .value("BOP_LESS", BinaryOp::BOP_LESS)
        .value("BOP_GREATER_EQUAL", BinaryOp::BOP_GREATER_EQUAL)
        .value("BOP_LESS_EQUAL", BinaryOp::BOP_LESS_EQUAL)
        .value("BOP_ASSIGN", BinaryOp::BOP_ASSIGN)
        .value("BOP_NOT_EQUAL", BinaryOp::BOP_NOT_EQUAL)
        .value("BOP_EXACT_EQUAL", BinaryOp::BOP_EXACT_EQUAL)
        .export_values();
}
}  // namespace impl
}  // namespace ast
}  // namespace nmodl
