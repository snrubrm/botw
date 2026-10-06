#include "Game/AI/Action/actionJumpTo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

namespace {
/// inline-only in the original; name is a guess. The same sequence (the normalised velocity `_70` of
/// the controller scaled by `-speed` and set again) appears in JumpTo::m42 and JumpTo::leave_.
inline void applyReverseVelocity(ksys::phys::CharacterController* controller, f32 speed) {
    sead::Vector3f dir;
    dir.set(controller->get70());
    dir.normalize();
    dir *= -speed;
    controller->sub_7100F5EE1C(dir);
}
}  // namespace

JumpTo::JumpTo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

JumpTo::~JumpTo() = default;

bool JumpTo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void JumpTo::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.reset(Flag::Changeable);
    f32 value = 0.0f;
    if (auto* controller = mActor->getCharacterController())
        value = -(controller->get70().length() * controller->get110());
    _94 = value;
    if (m35())
        m32();
    const auto& ang_velocity = mActor->getAngVelocity();
    const f32 speed = sead::Vector2f(ang_velocity.x, ang_velocity.z).length();
    _58.value = speed;
    _58.prev_value = speed;
    sub_710073FA90(&_64, mActor);
    _98 = 0;
    const sead::Vector3f& target = *mParams.mTargetPos_d;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    _88.set(target.x - pos.x, 0.0f, target.z - pos.z);
    if (auto* controller = mActor->getCharacterController()) {
        const sead::Vector3f up = getUpDir(controller->get70());
        ksys::util::sub_71011EFA00(&_88, _88, up);
    }
    if (_88.x == 0.0f && _88.y == 0.0f && _88.z == 0.0f)
        mActor->getMtx().getBase(_88, 2);
    _88.normalize();
}

void JumpTo::leave_() {
    const f32 speed = _94;
    if (auto* controller = mActor->getCharacterController())
        applyReverseVelocity(controller, speed);
}

void JumpTo::loadParams_() {
    getStaticParam(&mParams.mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mParams.mJumpHeight_s, "JumpHeight");
    getStaticParam(&mParams.mJumpGravity_s, "JumpGravity");
    getStaticParam(&mParams.mPosReduceRatioOnGround_s, "PosReduceRatioOnGround");
    getStaticParam(&mParams.mRotReduceRatioOnGround_s, "RotReduceRatioOnGround");
    getStaticParam(&mParams.mInWaterDepth_s, "InWaterDepth");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

// NON_MATCHING: only the test of the water-depth bool in the controller branch (`tbz w8, #0` in the original,
// `cbz w8` in ours).
void JumpTo::calc_() {
    switch (_98) {
    case 0:
        m40();
        m39();
        if (!isFinishedAS(0, 0) && m35()) {
            if (!sub_71005DD780(mActor, 0x44, nullptr, 0, 0))
                return;
        } else {
            if (m36())
                m33();
        }
        m42();
        _98 = 1;
        break;
    case 1:
        if (isFinishedAS(0, 0) && m36())
            m33();
        m38();
        m39();
        if (!isBgGroundHit(mActor, false)) {
            auto* controller = mActor->getCharacterController();
            const bool in_water = sub_71001C72A8();
            f32 velocity_y;
            if (controller) {
                if (!in_water)
                    return;
                sead::Vector3f velocity;
                controller->sub_7100F5F598(&velocity);
                velocity_y = velocity.y;
            } else {
                if (!in_water)
                    return;
                velocity_y = mActor->getVelocity().y;
            }
            if (!(velocity_y < 0.0f))
                return;
        }
        if (m37()) {
            m34();
            m43();
        } else {
            m43();
            setFinished();
        }
        _98 = 2;
        break;
    case 2:
        m40();
        m41();
        if (isFinishedAS(0, 0))
            setFinished();
        break;
    }
}

bool JumpTo::m35() {
    return true;
}

bool JumpTo::m36() {
    return true;
}

bool JumpTo::m37() {
    return true;
}

void JumpTo::m43() {}

const sead::Vector3f& JumpTo::m44() {
    return sead::Vector3f::zero;
}

void JumpTo::m41() {
    if (auto* controller = mActor->getCharacterController())
        sub_7100738660(controller, *mParams.mRotReduceRatioOnGround_s);
}

void JumpTo::m38() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(_58.value * 30.0f);
        sub_710072C1B4(controller, _88);
    }
}

// NON_MATCHING: regalloc of the up-direction components in the fallback path.
void JumpTo::m39() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sub_710073FA94(&_64, mActor);
    const sead::Vector3f dir = getUpDir(controller->get70());
    sub_710074006C(&_64, _88, dir, true, 0.1f, sead::Mathf::pi2(), 0.0f);
    sub_7100740E04(_64, controller);
}

void JumpTo::m40() {
    if (auto* controller = mActor->getCharacterController()) {
        _58 *= *mParams.mPosReduceRatioOnGround_s;
        _58.updateStats();
        controller->sub_7100F5E7F0(_58.value * 30.0f);
        sub_710072C1B4(controller, _88);
    }
}

bool JumpTo::sub_71001C72A8() const {
    const f32 threshold = *mParams.mInWaterDepth_s;
    if (!(threshold >= 0.0f))
        return false;
    f32 depth = 0.0f;
    if (mActor->get68f()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    return depth >= threshold;
}

f32 JumpTo::sub_71001C72EC() {
    f32 speed = 0.0f;
    f32 time = 0.0f;
    const sead::Vector3f start = mActor->getMtx().getTranslation();
    const sead::Vector3f target = *mParams.mTargetPos_d + m44();
    const sead::Vector3f gravity = getGravity(mActor) * (1.0f / 900.0f);
    if (!sub_710072CD88(*mParams.mJumpHeight_s, &speed, &time, &start, &target, &gravity))
        speed = *mParams.mMaxSpeed_s;
    return sead::Mathf::clampMax(speed, *mParams.mMaxSpeed_s);
}

void JumpTo::m42() {
    const f32 jump_gravity = *mParams.mJumpGravity_s;
    if (jump_gravity < 0.0f) {
        if (auto* controller = mActor->getCharacterController())
            applyReverseVelocity(controller, jump_gravity);
    }
    _58.value = _58.prev_value = sub_71001C72EC();
    _58.updateStats();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5E7F0(_58.value * 30.0f);
        sub_710072C1B4(controller, _88);
        controller->sub_7100F62B70(*mParams.mJumpHeight_s);
        controller->sub_7100F5EF08(true);
    }
}

}  // namespace uking::action
