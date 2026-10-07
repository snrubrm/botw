#include "Game/AI/Action/actionForkFollowGround.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

ForkFollowGround::ForkFollowGround(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkFollowGround::~ForkFollowGround() = default;

bool ForkFollowGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the fallback `ey` is copied through integer registers (the original keeps the three components in
// float registers across the join) and the fneg / fmul register order of the normalisation differs.
void ForkFollowGround::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (controller) {
        if (!controller->sub_7100F5F234(&_48)) {
            sead::Vector3f up = -controller->get70();
            if (up.normalize() < sead::Mathf::epsilon())
                up = sead::Vector3f::ey;
            _48 = up;
        }
        mActor->getMtx().getTranslation(_54);

        const s32 frames = *mParams.mUpdateFrameCountAfterNoMove_s;
        _60.reset(frames < 0 ? 1.0f : f32(frames), frames < 0 ? 0.0f : -1.0f);
        sub_7100741034(&_6c, mActor);
        f32 speed = mActor->getAngVelocity().length();
        if (speed > *mParams.mRotSpd_s)
            speed = *mParams.mRotSpd_s;
        _90 = speed;
        mFlags.set(Flag::Changeable);
    } else {
        setFailed();
    }
}

void ForkFollowGround::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkFollowGround::loadParams_() {
    getStaticParam(&mParams.mUpdateFrameCountAfterNoMove_s, "UpdateFrameCountAfterNoMove");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mParams.mUpdateTargetUpDirMinAngle_s, "UpdateTargetUpDirMinAngle");
    getStaticParam(&mParams.mUpdateTargetUpDirRatio_s, "UpdateTargetUpDirRatio");
}

void ForkFollowGround::m32(ksys::phys::CharacterController* controller) {
    sub_7100741038(&_6c, mActor);
    const f32 rot_spd = *mParams.mRotSpd_s;
    const f32 base_ratio = *mParams.mBaseRotRatio_s;
    ksys::VFR::lerp(&_90, rot_spd, base_ratio);
    m33(controller);

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.normalize();
    sead::Matrix34f mtx;
    ksys::util::sub_71011F00EC(&mtx, front, _48, sead::Vector3f::zero, true);
    sub_710074149C(&_6c, mtx, base_ratio, *mParams.mRotSpd_s, 0.1f);

    const f32 speed = mActor->getAngVelocity().length();
    if (_90 > speed)
        _90 = speed;
    sub_71007419F4(_6c, controller);
}

void ForkFollowGround::m33(ksys::phys::CharacterController* controller) {
    // NON_MATCHING: the original reloads _48.z from memory for the final dot term; ours keeps it
    // in a register. Everything else matches.
    sead::Vector3f translation;
    mActor->getMtx().getTranslation(translation);
    const f32 dx = translation.x - _54.x;
    const f32 dy = translation.y - _54.y;
    const f32 dz = translation.z - _54.z;
    const f32 d2 = dx * dx + dy * dy + dz * dz;
    f32 dist = std::sqrt(d2);
    if (!(dist < sead::Mathf::epsilon())) {
        const s32 count = *mParams.mUpdateFrameCountAfterNoMove_s;
        const f32 v = count < 0 ? 1.0f : static_cast<f32>(count);
        const f32 rate = count < 0 ? 0.0f : -1.0f;
        _60.value = v;
        _60.previous_value = v;
        _60.rate = rate;
    } else {
        _60.update();
        dist = _60.value;
    }
    _54 = translation;
    if (dist <= sead::Mathf::epsilon())
        return;
    sead::Vector3f vel;
    if (!controller->sub_7100F5F234(&vel)) {
        const sead::Vector3f& fallback = controller->get70();
        const f32 fx = fallback.x;
        const f32 fy = fallback.y;
        const f32 fz = fallback.z;
        const f32 fb2 = fx * fx + fy * fy + fz * fz;
        const f32 len = std::sqrt(fb2);
        f32 vx = -fx;
        f32 vy = -fy;
        f32 vz = -fz;
        if (len > 0.0f) {
            const f32 inv = 1.0f / len;
            vx *= inv;
            vy *= inv;
            vz *= inv;
        }
        if (!(len < sead::Mathf::epsilon())) {
            vel.x = vx;
            vel.y = vy;
            vel.z = vz;
        } else {
            vel.x = sead::Vector3f::ey.x;
            vel.y = sead::Vector3f::ey.y;
            vel.z = sead::Vector3f::ey.z;
        }
    }
    if (*mParams.mUpdateTargetUpDirMinAngle_s > 0.0f) {
        const f32 dot = _48.x * vel.x + _48.y * vel.y + _48.z * vel.z;
        if (dot >= cosf(*mParams.mUpdateTargetUpDirMinAngle_s))
            return;
        if (!(*mParams.mUpdateTargetUpDirRatio_s < 0.9999999f)) {
            _48 = vel;
        } else {
            ksys::util::sub_71011EE6FC(&_48, &vel);
        }
    }
}

void ForkFollowGround::calc_() {
    if (auto* controller = mActor->getCharacterController())
        m32(controller);
    else
        setFailed();
}

}  // namespace uking::action
