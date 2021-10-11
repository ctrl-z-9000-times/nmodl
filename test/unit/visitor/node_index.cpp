/*************************************************************************
 * Copyright (C) 2018-2019 Blue Brain Project
 *
 * This file is part of NMODL distributed under the terms of the GNU
 * Lesser General Public License. See top-level LICENSE file for details.
 *************************************************************************/

#include <catch/catch.hpp>
#include <utility>

#include "ast/program.hpp"
#include "parser/nmodl_driver.hpp"
#include "test/unit/utils/test_utils.hpp"
#include "visitors/test_visitor.hpp"
#include "visitors/visitor_utils.hpp"

using namespace nmodl;
using namespace visitor;

//=============================================================================
// get indexed name visitor tests
//=============================================================================

std::string run_test_indexed_name(ast::Program& node) {
    TestVisitor testvisitor;
    testvisitor.visit_program(node);
    return testvisitor.get_indexed_name();
}

std::pair<std::string, std::unordered_set<std::string>> run_test_dependencies(ast::Program& node) {
   TestVisitor testvisitor;
   testvisitor.visit_program(node);
   return testvisitor.get_dependencies();
}

SCENARIO("Get node name with index TestVisitor", "[visitor][node_index]") {
    auto to_ast = [](const std::string& text) {
        parser::NmodlDriver driver;
        return driver.parse_string(text);
    };

    GIVEN("A simple NMODL block") {
        std::string nmodl_text = R"(
            STATE {
                m[1]
            }
            BREAKPOINT  {
                SOLVE states METHOD euler
            }
            DERIVATIVE states {
                m'[0] = mInf/mTau
            }
        )";

        auto ast = to_ast(nmodl_text);
        
        WHEN("get node with index") {
            THEN("Can find variables") {
                // REQUIRE(run_test_indexed_name(*ast) == "h[0]");

                auto print_dependencies = [](std::pair<std::string, std::unordered_set<std::string>> var) {
                    std::cout<<var.first<<" { ";
                    for (auto i : var.second){
                        std::cout<<i<<" ";
                    }
                    std::cout<<"}"<<std::endl;
                };

                std::unordered_set<std::string> vars{"mInf", "mTau"};
                std::string var("m[0]");
                auto expect = std::make_pair(var,vars);
                auto result1 = run_test_indexed_name(*ast);
                auto result = run_test_dependencies(*ast);
                print_dependencies(result);
                REQUIRE(result.first == expect.first);
            }
        }

    }

}
