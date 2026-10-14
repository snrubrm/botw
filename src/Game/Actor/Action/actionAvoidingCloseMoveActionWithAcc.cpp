#include "Game/Actor/Action/actionAvoidingCloseMoveActionWithAcc.h"

#include <cmath>

#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

AvoidingCloseMoveActionWithAcc::AvoidingCloseMoveActionWithAcc(const InitArg& arg) : AvoidingCloseMoveBase(arg) {}

AvoidingCloseMoveActionWithAcc::~AvoidingCloseMoveActionWithAcc() = default;

bool AvoidingCloseMoveActionWithAcc::init_(sead::Heap* heap) {
    return AvoidingCloseMoveBase::init_(heap);
}

void AvoidingCloseMoveActionWithAcc::enter_(ksys::act::ai::InlineParamPack* params) {
    AvoidingCloseMoveBase::enter_(params);
}

void AvoidingCloseMoveActionWithAcc::leave_() {
    AvoidingCloseMoveBase::leave_();
}

void AvoidingCloseMoveActionWithAcc::loadParams_() {
    AvoidingCloseMoveBase::loadParams_();
    getStaticParam(&mAccRatio_s, "AccRatio");
}

void AvoidingCloseMoveActionWithAcc::calc_() {
    AvoidingCloseMoveBase::calc_();
}

bool AvoidingCloseMoveActionWithAcc::m37(ksys::phys::CharacterController* controller, f32 speed,
                                   const sead::Vector3f& dir) {
    // NON_MATCHING: scheduling only — the original interleaves the forward loads/stores/squares
    // differently, keeps the two scale arms as separate branches (ours if-converts them into an
    // fcsel), and uses fmov+str w for the z store. Calls, values, branch structure and the
    // Vector3f::zero/ey/HALF_PI constants are identical.
    f32 angle;
    auto* actor = mActor;
    const f32 base_speed = m35();
    sead::Vector3f vec = dir * base_speed;
    sead::Vector3f forward;
    forward.x = actor->getMtx().m[0][2];
    forward.y = actor->getMtx().m[1][2];
    forward.z = actor->getMtx().m[2][2];
    const f32 len = std::sqrt(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z);
    if (len > 0.0f) {
        const f32 inv_len = 1.0f / len;
        forward.x *= inv_len;
        forward.y *= inv_len;
        forward.z *= inv_len;
    }
    sead::Vector3f axis;
    ksys::util::sub_71011EEB08(&axis, &angle, forward, dir, sead::Vector3f::ey);
    if (angle >= 1.5707964f) {
        vec = sead::Vector3f::zero;
    } else {
        const f32 rot_speed = *mParams.mRotSpd_s;
        const f32 move_speed = m35();
        if (angle > rot_speed * 2.5f) {
            const f32 s = move_speed * 0.5f;
            vec.x = forward.x * s;
            vec.y = forward.y * s;
            vec.z = forward.z * s;
        } else {
            vec.x = forward.x * move_speed;
            vec.y = forward.y * move_speed;
            vec.z = forward.z * move_speed;
        }
    }
    sub_71005E2540(controller, actor, vec, *mAccRatio_s);
    return true;
}

}  // namespace uking::action
