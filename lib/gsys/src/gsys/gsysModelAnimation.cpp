#include "gsys/gsysModelAnimation.h"
#include <gsys/gsysModelResource.h>
#include <nn/g3d/ResFile.h>

namespace gsys {

sead::SafeString ModelAnimation::getMaterialAnmName(AnimationAccessKey<MaterialAnmType> key) const {
    if (!key.isValid())
        return sead::SafeString::cEmptyString;
    s32 index = key.index;
    if (key.type != 0)
        index += mMaterialAnmEnd[key.type - 1];
    return mMaterialAnmResources[index].resource->name;
}

sead::SafeString ModelAnimation::getMaterialAnmSlotName(int slot) const {
    auto key = mMaterialAnms[slot].getKey();
    if (!key.isValid())
        return sead::SafeString::cEmptyString;
    return getMaterialAnmName(key);
}

void ModelAnimation::forceRebindSkeletalAnm() {
    for (auto& animation : mSkeletalAnms)
        animation.flags |= 2;
}

void ModelAnimation::forceRebindMaterialAnm() {
    for (auto& animation : mMaterialAnms)
        animation.flags |= 1;
}

nn::g3d::ResFile* ModelAnimation::searchResFile(AnimationAccessKey<SkeletalAnmType> key) const {
    if (!key.isValid())
        return nullptr;
    s32 count = 0;
    for (auto& resource : mResources) {
        auto* file = resource.getResFile();
        count += file->mSkeleAnimCount;
        if (key.index < count)
            return file;
    }
    return nullptr;
}

void ModelAnimation::sub_7100BFD598(s32 slot) {
    setSkeletalAnmByKey(slot, AnimationAccessKey<SkeletalAnmType>{}, nullptr);
}

void ModelAnimation::sub_7100BFDBF4(bool enabled) {
    mSelfReferenceMaybe = enabled ? this : nullptr;
}

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

// 0x7100bff2a0
bool ModelAnimation::sub_7100BFF2A0() {
    return false;
}

void ModelAnimation::setEnableDebugSkeletalAnm(bool) {}
void ModelAnimation::setDebugSkeletalAnmKey(AnimationAccessKey<SkeletalAnmType>,
                                            DebugSkeletalAnmSlotType) {}
AnimationAccessKey<SkeletalAnmType> ModelAnimation::getDebugSkeletalAnmKey(
    DebugSkeletalAnmSlotType) const {
    return {};
}
f32 ModelAnimation::getDebugSkeletalAnmFrame(DebugSkeletalAnmSlotType) const {
    return 0.0f;
}

}  // namespace gsys
