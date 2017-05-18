#ifndef __CONST_JSON_REF_H__
#define __CONST_JSON_REF_H__ 

#include "json_basic.h"

namespace json_cpp {

class Json;
class JsonRef;

class ConstJsonRef: public JsonBasic {
    friend Json;
    friend JsonRef;
public:
    ConstJsonRef(ConstJsonRef const &r) = default;
    ConstJsonRef(ConstJsonRef &&r);

    ConstJsonRef operator[](std::string const &field_name) const;

    ConstJsonRef operator[](ArraySizeType index) const;
protected:
    JsonValuePtr const &Value() const override { return value_ref_; }
private:
    ConstJsonRef(JsonValuePtr const& value_ref);

    JsonValuePtr const &value_ref_;
};

}

#endif