#pragma once

#include <basis/seadTypes.h>

namespace gsys {

// C6D5C8 creates a 0x210-byte key. Native pushBack C83EF8 independently
// establishes the two arrays; the full table 24D20F8 has only D1/D0.
class ModelShaderVariationKey {
public:
    ModelShaderVariationKey();
    virtual ~ModelShaderVariationKey();
    void pushBack(const char* name, const char* value);

private:
    s32 mCount;
    const char* mNames[32];
    const char* mValues[32];
};
static_assert(sizeof(ModelShaderVariationKey) == 0x210);
}  // namespace gsys
