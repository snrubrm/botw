#include "Game/AI/Action/actionBackStepToTarget.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/AI/aiUnk_71007320F0.h"

namespace uking::action {

BackStepToTarget::BackStepToTarget(const InitArg& arg) : ActionEx(arg) {}

void BackStepToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getCharacterController();
    m34();
    _58 = 0;
    sub_7100741034(&_5c, mActor);
    _bc = 0;
    sub_7100741034(&_5c, mActor);
    if (auto* controller = mActor->getCharacterController())
        _b4 = -(controller->_70.length() * controller->_110);
    else
        _b4 = 0.0f;
    if (auto* controller = mActor->getCharacterController())
        _b8 = controller->sub_7100F62B78();
    else
        _b8 = 0.0f;
    setDamageCallbackTiming(mActor, 4, &_80);
}

// NON_MATCHING: operand order of the normalize multiplies (original `x * inv`, ours `inv * x`)
void BackStepToTarget::leave_() {
    {
        const f32 b4 = _b4;
        if (auto* controller = mActor->getCharacterController()) {
            sead::Vector3f dir = controller->_70;
            dir.normalize();
            dir *= -b4;
            controller->sub_7100F5EE1C(dir);
        }
    }
    const f32 b8 = _b8;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62B70(b8);
    sub_71005DA114(mActor, &_80);
}

// NON_MATCHING: the original keeps `this + 0x20` (and the SafeString vtable) in extra callee-saved registers
void BackStepToTarget::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mJumpGravity_s, "JumpGravity");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mCheckRotEvent_s, "CheckRotEvent");
}

void BackStepToTarget::calc_() {
    switch (_bc) {
    case 0:
        m38();
        if (isFinishedAS(0, 0)) {
            sub_71000B3D5C();
            _bc = 1;
        }
        break;
    case 1:
        m38();
        if (sub_71000B3F38()) {
            m36();
            _bc = 2;
            break;
        }
        [[fallthrough]];
    case 2:
        if (isBgGroundHit(mActor, false)) {
            m37();
            _bc = 3;
        }
        break;
    case 3:
        m39();
        if (isFinishedAS(0, 0))
            setFinished();
        break;
    }
    m32();
}

bool BackStepToTarget::isChangeable() const {
    return false;
}

f32 BackStepToTarget::m42() {
    return *mJumpHeight_s;
}

void BackStepToTarget::m39() {
    sub_7100738428(mActor, *mStopSpeedRatio_s);
}

void BackStepToTarget::m40() {
    if (auto* controller = mActor->getCharacterController())
        sub_7100738660(controller, *mStopRotSpeedRatio_s);
}

void BackStepToTarget::m38() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(_58 * 30.0f);
        sub_710072C1B4(controller, _a8);
    }
}

void BackStepToTarget::m33(sead::Vector3f* dir, const sead::Vector3f& up) {
    sead::Vector3f d = *mTargetPos_d - mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&d, d, up);
    d.normalize();
    *dir = d;
}

// NON_MATCHING: operand order of the normalize multiplies (original `x * inv`, ours `inv * x`)
void BackStepToTarget::sub_71000B3D5C() {
    m35();
    if (auto* controller = mActor->getCharacterController())
        _b4 = -(controller->_70.length() * controller->_110);
    else
        _b4 = 0.0f;
    const f32 gravity = *mJumpGravity_s;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f dir = controller->_70;
        dir.normalize();
        dir *= -gravity;
        controller->sub_7100F5EE1C(dir);
    }
    if (auto* controller = mActor->getCharacterController())
        _b8 = controller->sub_7100F62B78();
    else
        _b8 = 0.0f;
    const f32 height = m42();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62B70(height);
    m41(&_58, &_a8);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F5E7F0(_58 * 30.0f);
        sub_710072C1B4(controller, _a8);
    }
}

// NON_MATCHING: scheduling only (a once-used local `rise = gravity / 900 * 0.5 + vel.y` before the translation
// read reproduces the original; not applied)
bool BackStepToTarget::sub_71000B3F38() {
    const f32 gravity = *mJumpGravity_s;
    auto* controller = mActor->getCharacterController();
    sead::Vector3f vel = {0, 0, 0};
    if (!controller)
        return false;
    controller->sub_7100F5F598(&vel);
    vel = vel * (1.0f / 30.0f);
    if (!(vel.y < 0.0f))
        return false;
    sead::Vector3f top = mActor->getMtx().getTranslation();
    const sead::Vector3f bottom = top;
    top.y = gravity / 900.0f * 0.5f + vel.y + top.y;
    return sub_710072E928(top, bottom, nullptr, nullptr, nullptr, 0.0f);
}

void BackStepToTarget::sub_71000B4170() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    const sead::Vector3f up = -controller->_7c;
    sead::Vector3f dir;
    m33(&dir, up);
    sub_7100741038(&_5c, mActor);
    sub_7100741578(&_5c, dir, up, true, *mRotRatio_s, sead::Mathf::pi2(), 0.0f);
    sub_71007419F4(_5c, controller);
}

void BackStepToTarget::m32() {
    if (*mCheckRotEvent_s) {
        auto* as_list = mActor->getASList();
        if (!as_list)
            return;
        if (!as_list->x(41, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
            m40();
            return;
        }
    } else {
        if (_bc == 2)
            return;
        if (_bc == 3) {
            m40();
            return;
        }
    }
    sub_71000B4170();
}

}  // namespace uking::action
