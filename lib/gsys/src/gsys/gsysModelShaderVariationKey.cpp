#include "gsys/gsysModelShaderVariationKey.h"

namespace gsys {

ModelShaderVariationKey::ModelShaderVariationKey() : mCount(0) {}

void ModelShaderVariationKey::pushBack(const char* name, const char* value) {
    mNames[mCount] = name;
    mValues[mCount] = value;
    ++mCount;
}

}  // namespace gsys
