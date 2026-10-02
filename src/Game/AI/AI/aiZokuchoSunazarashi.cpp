#include "Game/AI/AI/aiZokuchoSunazarashi.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

ZokuchoSunazarashi::ZokuchoSunazarashi(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ZokuchoSunazarashi::~ZokuchoSunazarashi() = default;

bool ZokuchoSunazarashi::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ZokuchoSunazarashi::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_70.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        if (accessor.isStateSleep())
            accessor.wakeUp(ksys::act::BaseProc::SleepWakeReason(0));
    }
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.set(1);
    if (auto* controller = mActor->getCharacterController()) {
        controller->mFlags.set(0x10);
        controller->sub_7100F62DD0(0.0f);
    }
    if (auto* nav = mActor->m45()) {
        if (!nav->_18)
            ksys::phys::HavokAI::instance()->sub_7100F82DD8(nav);
    }
    _90 = false;
    _91 = false;
    _92 = false;
    m35();
}

void ZokuchoSunazarashi::leave_() {
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(0.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        controller->sub_7100F62DD0(1.0f);
    }
    if (auto* nav = mActor->m45())
        nav->inlineReset();
    if (_70.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        _b0.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000090), nullptr,
                        false);
    }
}

void ZokuchoSunazarashi::loadParams_() {
    getStaticParam(&mPlayerLostDis_s, "PlayerLostDis");
    getStaticParam(&mLeadPlayerAngle_s, "LeadPlayerAngle");
    getStaticParam(&mMoveTargetDist_s, "MoveTargetDist");
    getStaticParam(&mStopMoveDist_s, "StopMoveDist");
    getStaticParam(&mStayAwayDist_s, "StayAwayDist");
}

void ZokuchoSunazarashi::m34() {
    if (isCurrentChild("停止"))
        return;
    if (auto* nav = mActor->m45())
        nav->inlineReset();
    changeChild("停止");
    if (_70.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        _b0.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800008d), nullptr,
                        true);
    }
}

void ZokuchoSunazarashi::m35() {
    if (isCurrentChild("待機"))
        return;
    changeChild("待機");
    if (_70.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        _b0.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800008e), nullptr,
                        true);
    }
}

}  // namespace uking::ai
