#include "Game/Actor/Behavior/behaviorAnimalNeckRotate.h"
#include <cmath>
#include <limits>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <nn/g3d/SkeletonObj.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007398C0.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::behavior {

AnimalNeckRotate::AnimalNeckRotate(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AnimalNeckRotate::~AnimalNeckRotate() = default;

bool AnimalNeckRotate::init_(sead::Heap* heap) {
    return true;
}

// NON_MATCHING: the last node address is computed as base + size * 0x180 - 0xa8 in the original and its key
// halves are reloaded through it; the key stores are also swapped.
void AnimalNeckRotate::enter() {
    sub_71005DB068(mActor, sub_71005D960C(mActor));
    auto* model = mActor->getModel();
    auto* unit = sub_71007398C0(mActor);
    if (!model || !unit)
        return;

    if (unit->_18.size() > 0) {
        const auto& key = unit->_18.back()._a8.getKey();
        const s16 unit_index = key.model_unit_index;
        auto* model_unit = sead::DynamicCast<gsys::ModelNW>(model->getUnits()(unit_index)->mModelUnit);
        if (model_unit && model_unit->getSkeletonObj() && model_unit->getSkeletonObj()->GetRes()) {
            const auto* skeleton = model_unit->getSkeletonObj()->GetRes();
            if (const auto* bone = skeleton->GetBone(key.bone_index)) {
                gsys::BoneAccessKey parent_key;
                parent_key.model_unit_index = unit_index;
                parent_key.bone_index = bone->GetParentIndex();
                _48.search(model, parent_key);
            }
        }
    }

    if (*mRotRate_s >= 0.0f)
        unit->sub_7100D8A9D0(*mRotRate_s);
    else
        unit->_9c = unit->_98;

    if (*mResetRotRate_s >= 0.0f)
        unit->sub_7100D8A9EC(*mResetRotRate_s);
    else
        unit->_a4 = unit->_a0;
}

void AnimalNeckRotate::leave() {
    if (auto* unit = sub_71007398C0(mActor)) {
        sub_71005DB3EC(mActor);
        unit->sub_7100D8A830(0.0f, false);
        unit->_9c = unit->_98;
        unit->_a4 = unit->_a0;
    }
}

void AnimalNeckRotate::loadParams() {
    getStaticParam(&mLimitAngleLR_s, "LimitAngleLR");
    getStaticParam(&mRotRate_s, "RotRate");
    getStaticParam(&mResetRotRate_s, "ResetRotRate");
    getStaticParam(&mIsUseParentRotOffset_s, "IsUseParentRotOffset");
}

// Turns the animal's neck toward the direction the controller asks for, then limits the angle against
// LimitAngleLR (flag 2 of the controller's _d4).
// NON_MATCHING: register allocation and the isNan loads differ (the original tests the raw words and keeps the
// direction vector in its stack slot); the sign select is mirrored. Same instructions otherwise.
void AnimalNeckRotate::calc() {
    sub_71005DB404(mActor, sub_71005D960C(mActor));
    auto* unit = sub_71007398C0(mActor);
    if (!unit)
        return;

    // The animal looks along its own ground-projected forward axis (the matrix z basis).
    sead::Vector3f forward(mActor->getMtx()(0, 2), 0.0f, mActor->getMtx()(2, 2));
    forward.normalize();

    sead::Vector3f neck_dir;
    const auto& key = _48.getKey();
    if (key.isValid()) {
        sead::Matrix34f mtx;
        mActor->getModel()->getBoneWorldMatrix(key, &mtx);
        neck_dir.set(mtx(0, 0), 0.0f, mtx(2, 0));
        neck_dir.normalize();

        f32 dot = forward.dot(neck_dir);
        if (dot < -1.0f)
            dot = -1.0f;
        else if (dot > 1.0f)
            dot = 1.0f;

        f32 angle = std::acos(dot);
        f32 sign = 1.0f;
        if (forward.x * neck_dir.z - forward.z * neck_dir.x < 0.0f)
            sign = -1.0f;
        angle *= sign;

        const f32 prev = unit->_90;
        f32 diff = angle - prev;
        if (diff < 0.0f)
            diff = -diff;
        if (diff > 0.01f) {
            f32 step = (angle - prev) * 0.7f;
            f32 abs_step = step;
            if (abs_step < 0.0f)
                abs_step = -abs_step;
            if (abs_step <= 3.1415927f) {
                if (abs_step < 0.01f)
                    step = step < 0.0f ? -0.01f : 0.01f;
            } else {
                step = step < 0.0f ? -3.1415927f : 3.1415927f;
            }
            angle = prev + step;
        }
        unit->sub_7100D8A830(angle, false);
    } else {
        unit->sub_7100D8A830(0.0f, false);
    }

    if (*mLimitAngleLR_s < 0.0f)
        return;

    const f32 nan = std::numeric_limits<f32>::quiet_NaN();
    sead::Vector3f pos(nan, nan, nan);
    sead::Vector3f target(nan, nan, nan);
    unit->sub_7100D88CF4(&pos);
    unit->sub_7100D89324(&target);

    sead::Vector3f dir;
    if (sead::Mathf::isNan(pos.x) || sead::Mathf::isNan(pos.y) || sead::Mathf::isNan(pos.z) ||
        sead::Mathf::isNan(target.x) || sead::Mathf::isNan(target.y) ||
        sead::Mathf::isNan(target.z)) {
        dir.set(-neck_dir.x, 0.0f, -neck_dir.z);
    } else {
        dir.set(target.x - pos.x, 0.0f, target.z - pos.z);
    }
    dir.normalize();

    f32 dot = neck_dir.dot(dir);
    if (dot < -1.0f)
        dot = -1.0f;
    else if (dot > 1.0f)
        dot = 1.0f;
    const f32 angle = std::acos(dot);
    if (angle > *mLimitAngleLR_s)
        unit->_d4 &= ~0xc03u;
    else
        unit->_d4 |= 2;
}

}  // namespace uking::behavior
