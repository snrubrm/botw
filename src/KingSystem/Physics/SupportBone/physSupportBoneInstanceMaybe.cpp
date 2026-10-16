#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/SupportBone/physSupportBoneResource.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace ksys::phys {

SupportBoneInstanceMaybe::SupportBoneInstanceMaybe() = default;

SupportBoneInstanceMaybe::~SupportBoneInstanceMaybe() {
    finalize_();
}

bool SupportBoneInstanceMaybe::init(BoneAccessor* accessor, SupportBoneResource* resource,
                                    sead::Heap* heap) {
    finalize_();
    if (!accessor || !resource)
        return false;

    _8 = accessor;
    mResource = resource;

    const s32 num_bones = *resource->mBoneNum;
    if (num_bones > 0) {
        _18.tryAllocBuffer(num_bones, heap);
        for (s32 i = 0; i < num_bones; ++i)
            _18[i] = _8->getBoneIndex(mResource->boneBuffer[i].name->cstr());
    }

    const s32 num_main_bones = *mResource->mMainBoneNum;
    _40 = sead::Mathi::roundUpPow2(num_main_bones * s32(sizeof(MainBoneWork)), 0x20);
    if (_40 != 0) {
        _38 = new (heap, 0x20) u8[_40];
        if (!_38)
            return false;
        // _38 is the raw storage of _28
        _28.setBuffer(num_main_bones, reinterpret_cast<MainBoneWork*>(_38));
        sub_7101226E44();
    }

    const s32 num_support_bones = *mResource->mSupportBoneNum;
    if (num_support_bones > 0)
        _48.tryAllocBuffer(num_support_bones, heap);
    return true;
}

s32 SupportBoneInstanceMaybe::sub_71012273A8(const sead::SafeString& name) const {
    if (!mResource)
        return -1;
    return mResource->getSupportBoneIndexByName(name);
}

}  // namespace ksys::phys
