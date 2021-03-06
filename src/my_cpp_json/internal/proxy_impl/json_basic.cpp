#include "json_basic.h"

#include <string>

#include "const_json_ref.h"

using std::string;
using std::nullptr_t;
using std::runtime_error;

using my_cpp_json::internal::repr::JsonString;
using my_cpp_json::internal::repr::JsonNumber;
using my_cpp_json::internal::repr::JsonBool;

namespace my_cpp_json { namespace internal { namespace proxy_impl {

string const &JsonBasic::AsString() const {
    return ApplyToValueAs<JsonString>(
        "convert to string",
        [](JsonString *s) -> string const & { return s->value(); }
    );
}

double JsonBasic::AsDouble() const {
    return ApplyToValueAs<JsonNumber>(
        "convert to double",
        [](JsonNumber *n) { return n->value(); }
    );
}

bool JsonBasic::AsBool() const {
    return ApplyToValueAs<JsonBool>(
        "convert to bool",
        [](JsonBool *b) { return b->value(); }
    );
}

nullptr_t JsonBasic::AsNull() const {
    auto &val = Value();
    if(val) {
        throw runtime_error(InvalidAction(val->type(), "convert to nullptr"));
    }
    return nullptr;
}

inline string JsonBasic::InvalidAction(JType const &t, string const &descr) {
    return "invalid action on type " + JTypeUtils::ToString(t) + ": " + descr;
}

}}}