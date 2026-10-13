#include "gsys/gsysModelShaderVariationKey.h"

namespace gsys {

ModelShaderVariationKey::ModelShaderVariationKey() : mCount(0) {}

// Preserve the native vtable store, following GameDataFlagSelector's empty-statement
// destructor (upstream 96101229).
ModelShaderVariationKey::~ModelShaderVariationKey() { ; }

void ModelShaderVariationKey::pushBack(const char* name, const char* value) {
    mNames[mCount] = name;
    mValues[mCount] = value;
    ++mCount;
}

}  // namespace gsys
