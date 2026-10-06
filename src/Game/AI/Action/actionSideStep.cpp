#include "Game/AI/Action/actionSideStep.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SideStep::SideStep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SideStep::~SideStep() = default;

void SideStep::sub_71002530E0() {
    sead::Vector3f to_target = *mParams.mTargetPos_d;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    to_target -= pos;
    to_target.y = 0.0f;
    to_target.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0.0f;
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    axis.normalize();
    mActor->getASList()->x_6(9, 0, angle * sead::Mathf::rad2deg(1.0f) * axis.y);
    playAS("SideStep", false, 0, 0, -1.0f);
}

void SideStep::sub_7100252B24() {
    if (auto* link = sub_71005D9050(mActor); link && link->hasProc()) {
        sead::Vector3f dir = sub_71005D9330(mActor);
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        dir -= pos;
        dir.y = 0.0f;
        dir.normalize();
        if (auto* controller = mActor->getCharacterController()) {
            sub_710073FA94(&_5c, mActor);
            const sead::Vector3f up = getUpDir(controller->get70());
            sub_710074006C(&_5c, dir, up, true, *mParams.mRotSpeedRatio_s, sead::Mathf::pi2(), 0.0f);
            sub_7100740E04(_5c, controller);
        }
    } else {
        sub_7100738AA8(mActor, *mParams.mStopRotSpeedRatio_s);
    }
}

// NON_MATCHING: normalisation multiply operand order (same as leave_) and the order of the static param loads
// before the sub_71005DF66C call.
void SideStep::sub_7100252CFC() {
    const f32 gravity = *mParams.mGravity_s;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f direction = controller->get70();
        direction.normalize();
        direction.multScalar(-gravity);
        controller->sub_7100F5EE1C(direction);
    }
    const f32 jump_height = *mParams.mJumpHeight_s;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62B70(jump_height);

    sead::Vector3f velocity;
    sub_71005DF66C(&velocity, mActor, mParams.mTargetPos_d, nullptr, *mParams.mJumpHeight_s,
                   *mParams.mGravity_s / 900.0f);
    const f32 speed = velocity.normalize();
    _50.value = speed;
    _50.prev_value = speed;
    _50.updateStats();
    _b4 = velocity;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(_50.value * 30.0f);
        sub_710072C1B4(controller, _b4);
        controller->sub_7100F5EF08(true);
    }
    _d4 = 1;
}

void SideStep::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71002530E0();
    _50.value = 0;
    _50.prev_value = 0;
    sub_710073FA90(&_5c, mActor);
    _d4 = 0;
    f32 speed = 0.0f;
    if (auto* controller = mActor->getCharacterController())
        speed = -(controller->get70().length() * controller->get110());
    _cc = speed;
    f32 gravity_scale = 0.0f;
    if (auto* controller = mActor->getCharacterController())
        gravity_scale = controller->sub_7100F62B78();
    _d0 = gravity_scale;
    setDamageCallbackTiming(mActor, 4, &_80);
}

// NON_MATCHING: operand order of the normalisation multiplies (`s10 * s0` in the original)
void SideStep::leave_() {
    const f32 speed = _cc;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f dir;
        dir.set(controller->get70());
        dir.normalize();
        dir.multScalar(-speed);
        controller->sub_7100F5EE1C(dir);
    }
    const f32 gravity_scale = _d0;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62B70(gravity_scale);
    sub_71005DA114(mActor, &_80);
}

void SideStep::loadParams_() {
    getStaticParam(&mParams.mRotSpeedRatio_s, "RotSpeedRatio");
    getStaticParam(&mParams.mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mParams.mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mParams.mGravity_s, "Gravity");
    getStaticParam(&mParams.mJumpHeight_s, "JumpHeight");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void SideStep::calc_() {
    switch (_d4) {
    case 0:
        sub_7100738428(mActor, *mParams.mStopSpeedRatio_s);
        sub_7100252B24();
        if (mActor->getASList()->x(68, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
            sub_7100252CFC();
        break;
    case 1:
        if (auto* controller = mActor->getCharacterController()) {
            controller->sub_7100F5E7F0(_50.value * 30.0f);
            sub_710072C1B4(controller, _b4);
        }
        sub_7100252B24();
        if (isBgGroundHit(mActor, false))
            _d4 = 2;
        break;
    case 2:
        sub_7100738428(mActor, *mParams.mStopSpeedRatio_s);
        sub_7100738AA8(mActor, *mParams.mStopRotSpeedRatio_s);
        if (isFinishedAS(0, 0))
            setFinished();
        break;
    }
}

bool SideStep::isChangeable() const {
    return false;
}

}  // namespace uking::action
