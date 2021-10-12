/*************************************************************************
 * Copyright (C) 2018-2019 Blue Brain Project
 *
 * This file is part of NMODL distributed under the terms of the GNU
 * Lesser General Public License. See top-level LICENSE file for details.
 *************************************************************************/

#include <iostream>
#include <memory>
#include <unordered_set>

#include "ast/global.hpp"
#include "ast/indexed_name.hpp"
#include "ast/all.hpp"
//#include "ast/diff_eq_expression.hpp"
#include "ast/program.hpp"
#include "ast/range.hpp"
#include "ast/statement_block.hpp"
#include "visitors/test_visitor.hpp"
#include "visitors/visitor_utils.hpp"

namespace nmodl {
namespace visitor {

void TestVisitor::visit_indexed_name(ast::IndexedName& node) {
    indexed_name = nmodl::get_indexed_name(node);
}

void TestVisitor::visit_diff_eq_expression(ast::DiffEqExpression& node) {
    node.visit_children(*this);
    const auto& bin_exp = std::static_pointer_cast<ast::BinaryExpression>(node.get_expression()); 
    auto lhs = bin_exp->get_lhs();
    auto rhs = bin_exp->get_rhs();
    dependencies = nmodl::statement_dependencies(lhs, rhs);
 }

void TestVisitor::visit_program(ast::Program& node) {
    node.visit_children(*this);
}
std::pair<std::string, std::unordered_set<std::string>> TestVisitor::get_dependencies() {
    return dependencies;    
}
std::string TestVisitor::get_indexed_name() {
    return indexed_name;
}

}  // namespace visitor
}  // namespace nmodl
