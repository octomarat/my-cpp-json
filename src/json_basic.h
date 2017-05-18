#ifndef __JSON_BASIC_H__
#define __JSON_BASIC_H__

#include <memory>
#include "json_model.h"

namespace json_cpp {

class JsonMutable;
class ConstJsonRef;

// TODO prohibit pointers creation
class JsonBasic {
    friend class JsonMutable;
public:
    using ArraySizeType = inner::json_model::JsonArray::size_type;

    std::string const &AsString() const;
    double AsDouble() const;
    bool AsBool() const;
    std::nullptr_t AsNull() const;

    JType Type() const { 
        auto &val = Value();
        return val ? val->type() : JType::JNULL; 
    }

    ConstJsonRef operator[](std::string const &field_name) const;
    ConstJsonRef operator[](ArraySizeType index) const;
protected:
    using JsonValuePtr = std::shared_ptr<inner::json_model::JsonValue>;

    virtual JsonValuePtr const &Value() const = 0;

    JsonValuePtr const &AccessField(std::string const &field_name) const;
    JsonValuePtr const &AccessElem(ArraySizeType index) const;
};

}

#endif