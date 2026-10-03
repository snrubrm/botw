#include "Game/AI/Action/actionSiteBossSwordThrowElectricBall.h"

namespace uking::action {

SiteBossSwordThrowElectricBall::SiteBossSwordThrowElectricBall(const InitArg& arg)
    : SiteBossThrowParts(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SiteBossSwordThrowElectricBall::~SiteBossSwordThrowElectricBall() {
    ;
}

bool SiteBossSwordThrowElectricBall::init_(sead::Heap* heap) {
    return SiteBossThrowParts::init_(heap);
}

void SiteBossSwordThrowElectricBall::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossThrowParts::enter_(params);
}

void SiteBossSwordThrowElectricBall::leave_() {
    SiteBossThrowParts::leave_();
}

void SiteBossSwordThrowElectricBall::loadParams_() {
    SiteBossThrowParts::loadParams_();
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveOffset_s, "MoveOffset");
}

void SiteBossSwordThrowElectricBall::calc_() {
    SiteBossThrowParts::calc_();
}

void SiteBossSwordThrowElectricBall::m35() {
    sub_710026E3B0(false);
}

}  // namespace uking::action
