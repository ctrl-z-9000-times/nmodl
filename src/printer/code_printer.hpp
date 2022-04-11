/*************************************************************************
 * Copyright (C) 2018-2019 Blue Brain Project
 *
 * This file is part of NMODL distributed under the terms of the GNU
 * Lesser General Public License. See top-level LICENSE file for details.
 *************************************************************************/

#pragma once

/**
 * \dir
 * \brief Code printer implementations
 *
 * \file
 * \brief \copybrief nmodl::printer::CodePrinter
 */

#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

namespace nmodl {
/// implementation of various printers
namespace printer {

/**
 * @defgroup printer Code Printers
 * @brief Printers for translating AST to different forms
 * @{
 */

/**
 * \class CodePrinter
 * \brief Helper class for printing C/C++ code
 *
 * This class provides common functionality required by code
 * generation visitor to print C/C++/Cuda code.
 */
class CodePrinter {
  private:
    std::ofstream ofs;
    std::streambuf* sbuf = nullptr;
    std::shared_ptr<std::ostream> result;
    size_t indent_level = 0;
    const int NUM_SPACES = 4;

  public:
    CodePrinter()
        : result(std::make_shared<std::ostream>(std::cout.rdbuf())) {}

    CodePrinter(std::ostream& stream)
        : result(std::make_shared<std::ostream>(stream.rdbuf())) {}

    CodePrinter(const std::string& filename);

    ~CodePrinter() {
        ofs.close();
    }

    /// print whitespaces for indentation
    void add_indent();

    /// start a block scope (i.e. start with "{")
    void start_block();

    template <typename... Args>
    void start_block(const std::string&& text, Args&&... args) {
        add_indent();
        add_text(text + "{", std::forward<Args>(args)...);
        add_newline();
        indent_level++;
    }

    template <typename... Args>
    void add_text(const std::string&& text, Args&&... args) {
        if (sizeof...(Args) > 0) {
            *result << fmt::format(text, std::forward<Args>(args)...);
        } else {
            *result << text;
        }
    }

    template <typename... Args>
    void add_line(const std::string&& text, Args&&... args) {
        add_indent();
        add_text(text, std::forward<Args>(args)...);
        add_newline();
    }

    void add_newline(int n = 1);

    void increase_indent() {
        indent_level++;
    }

    void decrease_indent() {
        indent_level--;
    }

    /// end of current block scope (i.e. end with "}")
    void end_block(int num_newlines = 0);

    int indent_spaces() {
        return NUM_SPACES * indent_level;
    }
};

/** @} */  // end of printer

}  // namespace printer
}  // namespace nmodl
