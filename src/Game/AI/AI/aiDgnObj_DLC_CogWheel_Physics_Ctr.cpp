#include "Game/AI/AI/aiDgnObj_DLC_CogWheel_Physics_Ctr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

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

}  // namespace uking::ai
