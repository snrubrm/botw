#include "Game/AI/Action/actionPlayerTurnAndLookToObjectNow.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerTurnAndLookToObjectNow::PlayerTurnAndLookToObjectNow(const InitArg& arg)
    : PlayerLookAtObjectNow(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
PlayerTurnAndLookToObjectNow::~PlayerTurnAndLookToObjectNow() {
    ;
}

bool PlayerTurnAndLookToObjectNow::init_(sead::Heap* heap) {
    return PlayerLookAtObjectNow::init_(heap);
}

void PlayerTurnAndLookToObjectNow::enter_(ksys::act::ai::InlineParamPack* params) {
    LookAtObjectBase::enter_(params);
    m33();
    ksys::act::BaseProcLink link;
    sead::Vector3f pos;
    pos = sead::Vector3f::zero;
    if (_30 == 0) {
        if (!m34(&link, &pos, _48, _58)) {
            _c8 = true;
            _34 = 0;
        }
    }
    if (link.hasProc())
        m36(&link, sead::Vector3f::zero);
    else
        m36(nullptr, pos);
    switch (_34) {
    case 0:
        static_cast<ksys::act::Player*>(mActor)->sub_7100859FC0(_45);
        break;
    case 1:
        static_cast<ksys::act::Player*>(mActor)->sub_7100859EDC(_45, 0, &sead::Vector3f::zero, nullptr,
                                                               &sead::Vector3f::zero);
        break;
    }
    m40();
}

void PlayerTurnAndLookToObjectNow::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    static_cast<ksys::act::Player*>(mActor)->_2d64 = true;
}

void PlayerTurnAndLookToObjectNow::m41(ksys::phys::CharacterController* controller) {
    static_cast<ksys::act::Player*>(mActor)->sub_7100868D7C(2.0f, &_38);
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe(_d0.cstr(), true, 0.0f);
    setFinished();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
}

void PlayerTurnAndLookToObjectNow::loadParams_() {
    PlayerLookAtObjectNow::loadParams_();
}

// NON_MATCHING: regalloc (this / controller registers swapped: x19 / x20)
void PlayerTurnAndLookToObjectNow::calc_() {
    PlayerLookAtObjectNow::calc_();
    auto* controller = mActor->getCharacterController();
    if (isFinished()) {
        if (controller)
            controller->sub_7100F5FB24(sead::Vector3f::zero);
    } else if (isFailed()) {
        if (controller)
            controller->sub_7100F5FB24(sead::Vector3f::zero);
    } else if (controller) {
        m41(controller);
    }
}

void PlayerTurnAndLookToObjectNow::m40() {
    auto* controller = mActor->getCharacterController();
    if (_c8) {
        setFinished();
        return;
    }

    _38.y = 0;
    _38.normalize();
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0;
    front.normalize();
    if (controller) {
        controller->sub_7100F5EDD8(0.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

}  // namespace uking::action
