#include "Game/AI/Action/actionSiteBossBowBlowOff.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::action {

SiteBossBowBlowOff::SiteBossBowBlowOff(const InitArg& arg) : SiteBossBlowOff(arg) {}

SiteBossBowBlowOff::~SiteBossBowBlowOff() = default;

bool SiteBossBowBlowOff::init_(sead::Heap* heap) {
    return SiteBossBlowOff::init_(heap);
}

void SiteBossBowBlowOff::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossBlowOff::enter_(params);
}

void SiteBossBowBlowOff::leave_() {
    SiteBossBlowOff::leave_();
}

void SiteBossBowBlowOff::loadParams_() {
    SiteBossBlowOff::loadParams_();
    getStaticParam(&mAddForceRecoverTime_s, "AddForceRecoverTime");
    getStaticParam(&mIsRemoveCharacterController_s, "IsRemoveCharacterController");
    getStaticParam(&mForceRecoverDist_s, "ForceRecoverDist");
    getStaticParam(&mForceRecoverOffset_s, "ForceRecoverOffset");
}

void SiteBossBowBlowOff::calc_() {
    SiteBossBlowOff::calc_();
}

s32 SiteBossBowBlowOff::m37() {
    const s32 time = SiteBossBlowOff::m37();
    int level = getNumberOfDeadBlights();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        const s32 kind = boss->_1534 & ~3;
        if (kind == 4)
            level = 3;
        else if (kind == 8)
            level = 4;
    }
    return time + *mAddForceRecoverTime_s * level;
}

}  // namespace uking::action
