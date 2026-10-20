#include <math/seadMathCalcCommon.h>
#include <cstring>
#include "KingSystem/Physics/SupportBone/physSupportBoneResource.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/physConversions.h"

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
        if (sub_710122AD34(&rotate, work._0, *bone.aim, *bone.up, bone.side))
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

// NON_MATCHING: the state-buffer checks and weight maximum are scheduled differently.
bool SupportBoneInstanceMaybe::updateWeightsMaybe(f32 step) {
    const s32 num_bones = *mResource->mSupportBoneNum;
    if (num_bones <= 0)
        return false;
    f32 max_weight = 0.0f;
    for (s32 i = 0; i < num_bones; ++i) {
        f32 target = 0.0f;
        if ((_44 & 1) && _48[i].enabled && _48[i]._1)
            target = _48[i]._2 ? 1.0f : 0.0f;
        sead::Mathf::chase(&_48[i].weight, target, step);
        max_weight = sead::Mathf::max(max_weight, _48[i].weight);
    }
    return max_weight != 0.0f;
}

void SupportBoneInstanceMaybe::updateBonesMaybe() {
    if (!_8 || !mResource)
        return;
    sub_7101226E44();
    const s32 num_bones = *mResource->mSupportBoneNum;
    for (s32 i = 0; i < num_bones; ++i) {
        const f32 weight = _48[i].weight;
        if (weight != 0.0f)
            sub_7101227580(mResource->mSupportBoneBuffer[i], weight);
    }
}

f32 SupportBoneInstanceMaybe::getOutputDoubleMaybe(u32 index) {
    f32 first = 0.0f;
    const u32 connection_0 = *mResource->mOutputDoubleBuffer[index].connection_0;
    if (connection_0 != 0xffffffff) {
        switch (connection_0 >> 16) {
        case 0:
            first = getLinearConnectionMaybe(connection_0 & 0xffff);
            break;
        case 1:
            first = getCurveConnectionMaybe(connection_0 & 0xffff);
            break;
        }
    }
    f32 second = 0.0f;
    const u32 connection_1 = *mResource->mOutputDoubleBuffer[index].connection_1;
    if (connection_1 != 0xffffffff) {
        switch (connection_1 >> 16) {
        case 0:
            second = getLinearConnectionMaybe(connection_1 & 0xffff);
            break;
        case 1:
            second = getCurveConnectionMaybe(connection_1 & 0xffff);
            break;
        }
    }
    return first * *mResource->mOutputDoubleBuffer[index].weight_0 +
           second * *mResource->mOutputDoubleBuffer[index].weight_1;
}

// NON_MATCHING: local transforms, connection evaluation and quaternion interpolation are scheduled differently.
void SupportBoneInstanceMaybe::sub_7101227580(const SupportBoneResource::SupportBone& bone,
                                             f32 weight) {
    const auto& index = _18[*bone.bone];
    if (index.unk == -1 || index.havok_index == -1)
        return;
    const s32 space = *bone.space;
    hkQsTransformf transform;
    if (space == -1) {
        transform = _8->getBoneLocalSpace(index);
    } else if (space == -2) {
        transform = _8->getBoneModelSpace(index);
    } else {
        const auto& parent = _18[space];
        if (parent.unk == -1 || parent.havok_index == -1)
            return;
        transform.setMulInverseMul(_8->getBoneModelSpace(parent), _8->getBoneModelSpace(index));
    }
    const hkVector4 translation = transform.m_translation;
    if (u32(*bone.translateX) != 0xffffffff)
        transform.m_translation(0) = getOutputMaybe(*bone.translateX) + bone.base_translate->x;
    if (u32(*bone.translateY) != 0xffffffff)
        transform.m_translation(1) = getOutputMaybe(*bone.translateY) + bone.base_translate->y;
    if (u32(*bone.translateZ) != 0xffffffff)
        transform.m_translation(2) = getOutputMaybe(*bone.translateZ) + bone.base_translate->z;
    if (weight != 1.0f)
        transform.m_translation.setInterpolate(translation, transform.m_translation, hkSimdReal(weight));
    if (u32(*bone.bendH) != 0xffffffff) {
        const sead::Vector3f angles{getOutputMaybe(*bone.bendH), getOutputMaybe(*bone.bendV),
                                   getOutputMaybe(*bone.roll)};
        sead::Quatf rotation;
        if (sub_710122AD34(&rotation, angles, *bone.aim, *bone.up, bone.side)) {
            rotation.setMul(*bone.base_rotate, rotation);
            rotation.normalize();
            if (weight != 1.0f)
                rotation.slerpTo(toQuat(transform.m_rotation), rotation, weight);
            toHkQuat(&transform.m_rotation, rotation);
        }
    }
    if (space == -1) {
        _8->setBoneLocalSpace(index, transform);
    } else {
        if (space != -2)
            transform.setMul(_8->getBoneModelSpace(_18[space]), transform);
        _8->setBoneModelSpace(index, transform, BoneAccessor::Propagate::Yes);
    }
}

// NON_MATCHING: main-bone index extension and buffer loads differ in scheduling.
f32 SupportBoneInstanceMaybe::getLinearConnectionMaybe(u32 index) {
    const u32 attribute = *mResource->mConnectionLinearBuffer[index].bone_attribute;
    const u32 bone = attribute >> 16;
    f32 value;
    switch (attribute & 0xffff) {
    case 0:
        if (!_28[bone]._18)
            sub_71012285F4(bone);
        value = _28[bone]._0.x;
        break;
    case 1:
        if (!_28[bone]._18)
            sub_71012285F4(bone);
        value = _28[bone]._0.y;
        break;
    case 2:
        if (!_28[bone]._18)
            sub_71012285F4(bone);
        value = _28[bone]._0.z;
        break;
    case 3:
        if (!_28[bone]._19)
            sub_71012288A8(bone);
        value = _28[bone].translate.x;
        break;
    case 4:
        if (!_28[bone]._19)
            sub_71012288A8(bone);
        value = _28[bone].translate.y;
        break;
    case 5:
        if (!_28[bone]._19)
            sub_71012288A8(bone);
        value = _28[bone].translate.z;
        break;
    default:
        return 0.0f;
    }
    return mResource->somethingGetLinearConnection(index, value);
}

// NON_MATCHING: main-bone index extension and buffer loads differ in scheduling.
f32 SupportBoneInstanceMaybe::getCurveConnectionMaybe(u32 index) {
    const u32 attribute = *mResource->mConnectionCurveBuffer[index].bone_attribute;
    const u32 bone = attribute >> 16;
    f32 value;
    switch (attribute & 0xffff) {
    case 0:
        if (!_28[bone]._18)
            sub_71012285F4(bone);
        value = _28[bone]._0.x;
        break;
    case 1:
        if (!_28[bone]._18)
            sub_71012285F4(bone);
        value = _28[bone]._0.y;
        break;
    case 2:
        if (!_28[bone]._18)
            sub_71012285F4(bone);
        value = _28[bone]._0.z;
        break;
    case 3:
        if (!_28[bone]._19)
            sub_71012288A8(bone);
        value = _28[bone].translate.x;
        break;
    case 4:
        if (!_28[bone]._19)
            sub_71012288A8(bone);
        value = _28[bone].translate.y;
        break;
    case 5:
        if (!_28[bone]._19)
            sub_71012288A8(bone);
        value = _28[bone].translate.z;
        break;
    default:
        return 0.0f;
    }
    return mResource->getInterpolatedConnectionCurve(index, value);
}


// NON_MATCHING: quaternion and buffer temporaries differ in scheduling.
void SupportBoneInstanceMaybe::sub_71012285F4(u32 index) {
    const auto& bone = mResource->mMainBoneBuffer[index];
    const auto& bone_index = _18[*bone.bone];
    if (bone_index.unk == -1 || bone_index.havok_index == -1)
        return;
    const s32 space = *bone.space;
    hkQuaternionf rotation;
    if (space == -1) {
        rotation = _8->getBoneLocalSpace(bone_index).m_rotation;
    } else if (space == -2) {
        rotation = _8->getBoneModelSpace(bone_index).m_rotation;
    } else {
        const auto& parent = _18[space];
        if (parent.unk == -1 || parent.havok_index == -1)
            return;
        const auto& parent_transform = _8->getBoneModelSpace(parent);
        rotation.setInverseMul(parent_transform.m_rotation,
                                _8->getBoneModelSpace(bone_index).m_rotation);
    }
    sead::Quatf adjusted;
    adjusted.setMul(bone.reverse_rotate, toQuat(rotation));
    sead::Matrix34f matrix;
    matrix.fromQuat(adjusted);
    sub_710122A9AC(&_28[index]._0, matrix, *bone.aim, *bone.up, bone.side);
    _28[index]._18 = true;
}

// NON_MATCHING: translation and buffer temporaries differ in scheduling.
void SupportBoneInstanceMaybe::sub_71012288A8(u32 index) {
    const auto& bone = mResource->mMainBoneBuffer[index];
    const auto& bone_index = _18[*bone.bone];
    if (bone_index.unk == -1 || bone_index.havok_index == -1)
        return;
    const s32 space = *bone.space;
    hkVector4 translation;
    if (space == -1) {
        translation = _8->getBoneLocalSpace(bone_index).m_translation;
    } else if (space == -2) {
        translation = _8->getBoneModelSpace(bone_index).m_translation;
    } else {
        const auto& parent = _18[space];
        if (parent.unk == -1 || parent.havok_index == -1)
            return;
        const auto& parent_transform = _8->getBoneModelSpace(parent);
        translation.setTransformedInversePos(parent_transform,
                                               _8->getBoneModelSpace(bone_index).m_translation);
    }
    _28[index]._19 = true;
    _28[index].translate.set(translation(0) - bone.base_translate->x,
                              translation(1) - bone.base_translate->y,
                              translation(2) - bone.base_translate->z);
}

}  // namespace ksys::phys
