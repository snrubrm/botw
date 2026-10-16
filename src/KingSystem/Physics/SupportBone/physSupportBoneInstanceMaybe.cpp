#include <math/seadMathCalcCommon.h>
#include <cstring>
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

void SupportBoneInstanceMaybe::sub_7101226E44() {
    if (!_38)
        return;
    if (!(_44 & 2)) {
        std::memset(_38, 0, _40);
        return;
    }

    const s32 num_main_bones = *mResource->mMainBoneNum;
    for (s32 i = 0; i < num_main_bones; ++i) {
        _28[i]._18 = false;
        _28[i]._19 = false;
        const MainBoneWork& work = _28[i];
        if (!work.enabled)
            continue;

        const auto& bone = mResource->mMainBoneBuffer[i];
        const BoneAccessor::Indices& index = _18[*bone.bone];
        if (index.unk == -1 || index.havok_index == -1)
            continue;

        const sead::Vector3f translate = work.translate + *bone.base_translate;
        sead::Quatf rotate;
        if (sub_710122AD34(&rotate, work, *bone.aim, *bone.up, bone.side))
            rotate.setMul(*bone.base_rotate, rotate);
        else
            rotate.set(1, 0, 0, 0);

        const s32 space = *bone.space;
        if (space == -1) {
            hkQsTransformf transform;
            transform.m_scale = _8->getBoneLocalSpace(index).m_scale;
            transform.m_translation.set(translate.x, translate.y, translate.z, 0);
            transform.m_rotation.set(rotate.x, rotate.y, rotate.z, rotate.w);
            _8->setBoneLocalSpace(index, transform);
        } else if (space == -2) {
            hkQsTransformf transform;
            transform.m_scale = _8->getBoneModelSpace(index).m_scale;
            transform.m_translation.set(translate.x, translate.y, translate.z, 0);
            transform.m_rotation.set(rotate.x, rotate.y, rotate.z, rotate.w);
            _8->setBoneModelSpace(index, transform, BoneAccessor::Propagate::Yes);
        } else {
            const BoneAccessor::Indices& parent = _18[space];
            if (parent.unk == -1 || parent.havok_index == -1)
                continue;
            hkQsTransformf transform;
            transform.setMulInverseMul(_8->getBoneModelSpace(parent), _8->getBoneModelSpace(index));
            transform.m_translation.set(translate.x, translate.y, translate.z, 0);
            transform.m_rotation.set(rotate.x, rotate.y, rotate.z, rotate.w);
            transform.setMul(_8->getBoneModelSpace(parent), transform);
            _8->setBoneModelSpace(index, transform, BoneAccessor::Propagate::Yes);
        }

        _28[i]._18 = true;
        _28[i]._19 = true;
    }
}

s32 SupportBoneInstanceMaybe::sub_71012273A8(const sead::SafeString& name) const {
    if (!mResource)
        return -1;
    return mResource->getSupportBoneIndexByName(name);
}

}  // namespace ksys::phys
