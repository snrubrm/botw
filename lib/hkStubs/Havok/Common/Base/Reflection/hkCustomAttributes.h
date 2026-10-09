#pragma once

#include <Havok/Common/Base/Container/Array/hkSimpleArray.h>

// Reflection initializer 177F2A8 declares the 0x18 Attribute and 0x10 owner.
// Records 2560658/2560680 name the string and variant; 25606A8 declares
// a simple array of Attribute. Lookups 15839D4/1587D60 use the same records.
class hkCustomAttributes {
public:
    struct Attribute {
        const char* m_name;
        hkVariant m_value;
    };

    hkSimpleArray<Attribute> m_attributes;
};

static_assert(sizeof(hkCustomAttributes::Attribute) == 0x18);
static_assert(sizeof(hkCustomAttributes) == 0x10);
