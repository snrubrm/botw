#include "gsys/gsysModelAnimation.h"

namespace gsys {

// 0x7100bfa214
ModelAnimation::CreateArg::CreateArg() : _0(4), _4(4), _8(nullptr) {}

// 0x7100bfa52c
void ModelAnimation::destroy(ModelAnimation* animation) {
    delete animation;
}

// 0x7100bfdc60
s32 ModelAnimation::getMaterialAnmNum(MaterialAnmType type) const {
    const s32 index = static_cast<s32>(type);
    s32 num = mMaterialAnmEnd[index];
    if (index != 0)
        num -= mMaterialAnmEnd[index - 1];
    return num;
}

}  // namespace gsys
