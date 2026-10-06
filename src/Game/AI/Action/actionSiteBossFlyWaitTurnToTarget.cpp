#include "Game/AI/Action/actionSiteBossFlyWaitTurnToTarget.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

SiteBossFlyWaitTurnToTarget::SiteBossFlyWaitTurnToTarget(const InitArg& arg)
    : LastBossFlyWaitTurnToTarget(arg) {}

SiteBossFlyWaitTurnToTarget::~SiteBossFlyWaitTurnToTarget() = default;

bool SiteBossFlyWaitTurnToTarget::init_(sead::Heap* heap) {
    return LastBossFlyWaitTurnToTarget::init_(heap);
}

void SiteBossFlyWaitTurnToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossFlyWaitTurnToTarget::enter_(params);
}

void SiteBossFlyWaitTurnToTarget::leave_() {
    LastBossFlyWaitTurnToTarget::leave_();
}

void SiteBossFlyWaitTurnToTarget::loadParams_() {
    LastBossFlyWaitTurnToTarget::loadParams_();
}

void SiteBossFlyWaitTurnToTarget::calc_() {
    LastBossFlyWaitTurnToTarget::calc_();
}

void SiteBossFlyWaitTurnToTarget::m34() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_1558.isOnBit(4)) {
            boss->sub_71002D20B8();
            boss->x_5(false);
            boss->x_6(false);
            ksys::eft::searchAndEmitELink(mActor, "Elec_Sword_Off");
            ksys::eft::searchAndEmitELink(mActor, "Elec_Shield_Off");
            ksys::eft::searchAndEmitSLink(mActor, "Elec_Sword_Off", false);
        }
    }
}

}  // namespace uking::action
