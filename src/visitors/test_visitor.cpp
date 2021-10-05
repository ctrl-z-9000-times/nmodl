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
#include "ast/program.hpp"
#include "ast/range.hpp"
#include "ast/statement_block.hpp"
#include "visitors/test_visitor.hpp"
#include "visitors/visitor_utils.hpp"

namespace nmodl {
namespace visitor {

void TestVisitor::visit_indexed_name(ast::IndexedName& node) {
    std::cout << "Visiting " << node.get_node_name() << "[" << to_nmodl(node.get_length()) << "]" << std::endl;
}

}  // namespace visitor
}  // namespace nmodl
