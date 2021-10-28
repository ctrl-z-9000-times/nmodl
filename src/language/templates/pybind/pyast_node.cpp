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
#include "visitors/json_visitor.hpp"
#include "visitors/nmodl_visitor.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace nmodl::ast;
using namespace pybind11::literals;

{% macro args(children) %}
{% for c in children %}{{ c.get_shared_typename() }}{%- if not loop.last %}, {% endif %}{% endfor %}
{%- endmacro -%}

namespace nmodl {
namespace ast {
namespace impl {
py::class_<{{node.class_name}}, std::shared_ptr<{{node.class_name}}>> init_{{node.class_name}}(
        py::module const& ast,
        py::class_<{{node.base_class}}, std::shared_ptr<{{node.base_class}}>> const& {{node.base_class | snake_case}}_) {
    py::class_<{{node.class_name}}, std::shared_ptr<{{node.class_name}}>> ret{ast, "{{node.class_name}}", {{node.base_class | snake_case}}_};
    ret.doc() = "{{node.brief}}";
    {% if node.children %}
    ret.def(py::init<{{args(node.children)}}>());
    {% endif %}
    {% if node.is_program_node or node.is_ptr_excluded_node %}
    ret.def(py::init<>());
    {% endif %}

    ret.def("__repr__", []({{node.class_name}} & n) {
        std::stringstream ss;
        nmodl::visitor::JSONVisitor v(ss);
        v.compact_json(true);
        n.accept(v);
        v.flush();
        return ss.str();
    });

    ret.def("__str__", []({{node.class_name}} & n) {
        std::stringstream ss;
        nmodl::visitor::NmodlPrintVisitor v(ss);
        n.accept(v);
        return ss.str();
    });

    {% for member in node.public_members() %}
    ret.def_readwrite("{{ member[1] }}", &{{ node.class_name }}::{{ member[1] }});
    {% endfor %}

    {% for member in node.properties() %}
    {% if member[2] == True %}
        ret.def_property("{{ member[1] }}", &{{ node.class_name }}::get_{{ member[1] }},
            &{{ node.class_name }}::set_{{ member[1] }});
    {% else %}
        ret.def_property("{{ member[1] }}", &{{ node.class_name }}::get_{{ member[1] }},
                static_cast<void ({{ node.class_name }}::*)(const {{ member[0] }}&)>(&{{ node.class_name }}::set_{{ member[1] }}));
    {% endif %}
    {% endfor %}

    ret.def("visit_children", static_cast<void ({{ node.class_name }}::*)(visitor::Visitor&)>(&{{ node.class_name }}::visit_children), docstring::visit_children_method)
    .def("accept", static_cast<void ({{ node.class_name }}::*)(visitor::Visitor&)>(&{{ node.class_name }}::accept), docstring::accept_method)
    .def("accept", static_cast<void ({{ node.class_name }}::*)(visitor::ConstVisitor&) const>(&{{ node.class_name }}::accept), docstring::accept_method)
    .def("clone", &{{ node.class_name }}::clone, docstring::clone_method)
    .def("get_node_type", &{{ node.class_name }}::get_node_type, docstring::get_node_type_method)
    .def("get_node_type_name", &{{ node.class_name }}::get_node_type_name, docstring::get_node_type_name_method)
    {% if node.nmodl_name %}
    .def("get_nmodl_name", &{{ node.class_name }}::get_nmodl_name, docstring::get_nmodl_name_method)
    {% endif %}
    {% if node.is_data_type_node %}
    .def("eval", &{{ node.class_name }}::eval, docstring::eval_method)
    {% endif %}
    .def("is_{{ node.class_name | snake_case }}", &{{ node.class_name }}::is_{{ node.class_name | snake_case }}, "Check if node is of type ast.{{ node.class_name}}");
    return ret;
}
}  // namespace impl
}  // namespace ast
}  // namespace nmodl
