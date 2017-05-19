#include "json_model.h"

#include <stdexcept>

#include "utils.h"

using std::initializer_list;
using std::pair;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::make_pair;

namespace json_cpp { namespace internal { namespace repr {

JsonObject::JsonObject(initializer_list<pair<string const, shared_ptr<JsonValue>>> const &lst)
    : value_(lst)
{}

JsonArray::JsonArray(initializer_list<shared_ptr<JsonValue>> const &lst)
    : value_(lst)
{}

shared_ptr<JsonValue> CopyJsonTree(shared_ptr<JsonValue> const &original) {
    if(!original) {
        return shared_ptr<JsonValue>();
    }
    switch(original->type()) {
        case JType::JSTRING:
            return make_shared<JsonString>(*as<JsonString>(original));
        case JType::JNUMBER:
            return make_shared<JsonNumber>(*as<JsonNumber>(original));
        case JType::JBOOL:
            return make_shared<JsonBool>(*as<JsonBool>(original));
        case JType::JARRAY: {
            auto arr = as<JsonArray>(original);
            auto copy_arr = make_shared<JsonArray>();
            auto &copy_vals = copy_arr->value();
            for(auto const &v: arr->value()) {
                copy_vals.push_back(CopyJsonTree(v));
            }
            return copy_arr;
        }
        case JType::JOBJECT: {
            auto obj = as<JsonObject>(original);
            auto copy_obj = make_shared<JsonObject>();
            auto &copy_map = copy_obj->value();
            for(auto const &p: obj->value()) {
                copy_map.insert(p.first, CopyJsonTree(p.second));
            }
            return copy_obj;
        }
        default:
            throw std::runtime_error("unexcepted JType enum value");
    }
}

}}}