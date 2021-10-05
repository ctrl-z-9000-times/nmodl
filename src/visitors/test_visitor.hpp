/*************************************************************************
 * Copyright (C) 2018-2019 Blue Brain Project
 *
 * This file is part of NMODL distributed under the terms of the GNU
 * Lesser General Public License. See top-level LICENSE file for details.
 *************************************************************************/

#pragma once

/**
 * \file
 * \brief \copybrief nmodl::visitor::TestVisitor
 */

#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "visitors/ast_visitor.hpp"

namespace nmodl {
namespace visitor {

class TestVisitor: public AstVisitor {
  private:
    /// ast::Ast* node
    std::shared_ptr<ast::Program> ast;

  public:
    /// \name Ctor & dtor
    /// \{

    /// Default constructor
    TestVisitor() = delete;

    /// Constructor that takes as parameter the AST
    explicit TestVisitor(std::shared_ptr<ast::Program> node)
        : ast(std::move(node)) {}

    /// \}

    void visit_indexed_name(ast::IndexedName& node) override;
};

/** \} */  // end of visitor_classes

}  // namespace visitor
}  // namespace nmodl
