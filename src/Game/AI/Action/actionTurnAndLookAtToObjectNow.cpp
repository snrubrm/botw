#include "Game/AI/Action/actionTurnAndLookAtToObjectNow.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

TurnAndLookAtToObjectNow::TurnAndLookAtToObjectNow(const InitArg& arg) : LookAtObject(arg) {}

TurnAndLookAtToObjectNow::~TurnAndLookAtToObjectNow() = default;

bool TurnAndLookAtToObjectNow::init_(sead::Heap* heap) {
    return LookAtObject::init_(heap);
}

void TurnAndLookAtToObjectNow::enter_(ksys::act::ai::InlineParamPack* params) {
    m33();
    ksys::act::BaseProcLink link;
    sead::Vector3f pos;
    pos = sead::Vector3f::zero;
    switch (_30) {
    case 0:
        if (!m34(&link, &pos, _48, _58)) {
            _d0 = true;
            _34 = 0;
        }
        break;
    case 4:
        if (!m35(&link, &pos, _48, _58)) {
            _d0 = true;
            _34 = 0;
        }
        break;
    }

    if (link.hasProc())
        m36(&link, sead::Vector3f::zero);
    else
        m36(nullptr, pos);

    if (auto* npc = sead::DynamicCast<uking::act::NPC>(mActor)) {
        switch (_34) {
        case 0:
            npc->sub_7100022E3C(_45);
            break;
        case 1:
            npc->sub_7100022D44(_45, 0, sead::Vector3f::zero, nullptr, sead::Vector3f::zero);
            break;
        }
    } else {
        setFailed();
    }
    m40();
}

// NON_MATCHING: same as TurnAndLookToObject::m33 (NPC::_fe8 is loaded as a half word here; register swap)
void TurnAndLookAtToObjectNow::m33() {
    LookAtObject::m33();
    auto* actor = mActor;
    auto* npc = sead::DynamicCast<uking::act::NPC>(actor);
    if (!npc) {
        setFailed();
        return;
    }
    _d0 = false;
    if (npc->_fe8 & 0x40100000) {
        _d0 = true;
        if (_34 == 0)
            setFailed();
    }
    if (mActor->getPlayerRideInfo() && (mActor->getPlayerRideInfo()->_30 & 1)) {
        _d0 = true;
        if (_34 == 0)
            setFailed();
    }
    if (auto* schedule = npc->getSchedule()) {
        if (!schedule->_88.isEmpty())
            npc->_104c = _30 == -1 ? 2 : 1;
    }
}

void TurnAndLookAtToObjectNow::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
}

void TurnAndLookAtToObjectNow::loadParams_() {
    LookAtObject::loadParams_();
    getDynamicParam(&mIsConfront_d, "IsConfront");
}

void TurnAndLookAtToObjectNow::calc_() {
    LookAtObject::calc_();
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    auto* controller = mActor->getCharacterController();
    if (isFinished() || isFailed()) {
        sub_7100738AA8(mActor, 0.0f);
        return;
    }
    if (controller)
        m41(controller);
}

void TurnAndLookAtToObjectNow::m40() {
    auto* controller = mActor->getCharacterController();
    if (_d0) {
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
        controller->sub_7100F5E7F0(0.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

}  // namespace uking::action
