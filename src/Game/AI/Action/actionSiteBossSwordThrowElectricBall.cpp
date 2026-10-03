#include "Game/AI/Action/actionSiteBossSwordThrowElectricBall.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_710073fa90.h"

namespace uking::action {

// NON_MATCHING: the original loads the vtable address before the first member store (scheduling)
SiteBossSwordThrowElectricBall::SiteBossSwordThrowElectricBall(const InitArg& arg)
    : SiteBossThrowParts(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SiteBossSwordThrowElectricBall::~SiteBossSwordThrowElectricBall() {
    ;
}

bool SiteBossSwordThrowElectricBall::init_(sead::Heap* heap) {
    if (!SiteBossThrowParts::init_(heap))
        return false;
    _110[0].format("ElectricBall0");
    _110[1].format("ElectricBall1");
    _110[2].format("ElectricBall2");
    return true;
}

// NON_MATCHING: the original interleaves the position loads with the stores of _d8 (no stp pair)
void SiteBossSwordThrowElectricBall::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossThrowParts::enter_(params);
    const sead::Vector3f& pos = mActor->getMtx().getTranslation();
    _d8.x = pos.x;
    _d8.y = pos.y;
    _d8.z = pos.z;
    _d8 += *mParams.mMoveOffset_s;
    const f32 limit = mTargetPos_d->y + mParams.mMoveOffset_s->y * 1.5f;
    if (_d8.y > limit)
        _d8.y = limit;
    _e4 = 0.0f;
    sub_710073FA90(&_e8, mActor);
}

void SiteBossSwordThrowElectricBall::leave_() {
    SiteBossThrowParts::leave_();
}

void SiteBossSwordThrowElectricBall::loadParams_() {
    SiteBossThrowParts::loadParams_();
    getStaticParam(&mParams.mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mParams.mMoveOffset_s, "MoveOffset");
}

void SiteBossSwordThrowElectricBall::calc_() {
    SiteBossThrowParts::calc_();
}

void SiteBossSwordThrowElectricBall::m35() {
    sub_710026E3B0(false);
}

}  // namespace uking::action
