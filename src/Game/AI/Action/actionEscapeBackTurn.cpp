#include "Game/AI/Action/actionEscapeBackTurn.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

EscapeBackTurn::EscapeBackTurn(const InitArg& arg) : ActionEx(arg) {}

EscapeBackTurn::~EscapeBackTurn() = default;

void EscapeBackTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("BackTurn", false, 0, 0, -1.0f);
    _80 = 0;
    sub_7100113950();
}

void EscapeBackTurn::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
}

void EscapeBackTurn::loadParams_() {
    if (!mActor->getParam())
        return;

    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTurnDir_d, "TurnDir");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
}

void EscapeBackTurn::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    switch (_80) {
    case 0: {
        const sead::Vector3f up = getUpDir(controller->get70());
        sub_7100113D4C(up);
        sub_7100740E04(_28, controller);
        _1c *= 0.65f;
        _1c.updateStats();
        controller->sub_7100F5E7F0(_1c.value * 30.0f);

        ksys::as::ASList::Unk4 query;
        if (sub_71005DD5B0(mActor, 0x29, &query, 0, 0)) {
            _80 = 1;
            sub_7100113EF8(s32(query._10));
        }
        break;
    }
    case 1: {
        const sead::Vector3f up = getUpDir(controller->get70());
        sub_710073FA94(&_28, mActor);
        _4c.update();
        sub_7100740D50(&_28, _58, up, up, true, true, _4c.value);
        _1c *= 0.99f;
        _1c.updateStats();
        sub_7100740E04(_28, controller);
        controller->sub_7100F5E7F0(_1c.value * 30.0f);
        if (isFinishedAS(0, 0))
            setFinished();
        break;
    }
    }
}

bool EscapeBackTurn::isChangeable() const {
    return false;
}

void EscapeBackTurn::sub_7100113950() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    const sead::Vector3f up = getUpDir(controller->get70());
    sead::Vector3f velocity;
    velocity.set(mActor->getVelocity());
    ksys::util::sub_71011EFA00(&velocity, velocity, up);
    const f32 length = velocity.normalize();
    _1c.value = length;
    _1c.prev_value = length;
    sub_710072C1B4(controller, velocity);
}

// NON_MATCHING: only the load order of the copy of *mTargetPos_d differs (the original loads x/y before z)
void EscapeBackTurn::sub_7100113D4C(const sead::Vector3f& up) {
    sub_710073FA94(&_28, mActor);

    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f forward;
    mActor->getMtx().getBase(forward, 2);
    ksys::util::sub_71011EFA00(&forward, forward, up);
    forward.normalize();

    sub_710074006C(&_28, forward, up, true, 0.2f, sead::Mathf::pi2(), 0.0f);
}

void EscapeBackTurn::sub_7100113EF8(s32 duration) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    _4c.reset(f32(duration));
    _58 = *mTurnDir_d;
    const sead::Vector3f up = getUpDir(controller->get70());
    sub_7100113D4C(up);
    _1c.value = *mMoveSpeed_s;
    _1c.prev_value = *mMoveSpeed_s;
    sub_710072C1B4(controller, _58);
}

}  // namespace uking::action

