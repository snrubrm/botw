#include "Game/AI/AI/aiDgnObj_DLC_CogWheel_Physics_Ctr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/gameGearMgr.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

DgnObj_DLC_CogWheel_Physics_Ctr::DgnObj_DLC_CogWheel_Physics_Ctr(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

DgnObj_DLC_CogWheel_Physics_Ctr::~DgnObj_DLC_CogWheel_Physics_Ctr() = default;

bool DgnObj_DLC_CogWheel_Physics_Ctr::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DgnObj_DLC_CogWheel_Physics_Ctr::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!isCurrentChild("atk有効")) {
        mActor->emitBasicSigOn();
        changeChild("atk有効");
    }
    sub_71007A44E4(mActor, true);
}

void DgnObj_DLC_CogWheel_Physics_Ctr::calc_() {
    sub_710035ED38();
}

void DgnObj_DLC_CogWheel_Physics_Ctr::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DgnObj_DLC_CogWheel_Physics_Ctr::loadParams_() {
    getStaticParam(&mStateRot_s, "StateRot");
}

void DgnObj_DLC_CogWheel_Physics_Ctr::sub_710035ED38() {
    auto* gear_mgr = GearMgr::instance();
    if (gear_mgr && *mStateRot_s && !isSlowTimeMaybe() &&
        !(gear_mgr->_10a8[gear_mgr->_28 ^ 1] & 4) && !(gear_mgr->_10c0 <= 0.6f)) {
        if (!isCurrentChild("atk有効")) {
            mActor->emitBasicSigOn();
            changeChild("atk有効");
        }
        return;
    }
    if (!isCurrentChild("無効")) {
        mActor->emitBasicSigOff();
        changeChild("無効");
    }
}

// NON_MATCHING: the original null-checks the message reference (`cbz x1`).
bool DgnObj_DLC_CogWheel_Physics_Ctr::handleMessage_(const ksys::Message* message) {
    if (!GearMgr::instance())
        return false;
    if (message->getType() == 0x3000003) {
        if (!isCurrentChild("無効")) {
            mActor->emitBasicSigOff();
            changeChild("無効");
        }
    } else if (message->getType() == 0x3000004) {
        if (!isCurrentChild("atk有効")) {
            mActor->emitBasicSigOn();
            changeChild("atk有効");
        }
        return true;
    }
    return false;
}

}  // namespace uking::ai
