#include "Game/AI/AI/aiEnemyWarnNoticeSelect.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyWarnNoticeSelect::EnemyWarnNoticeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyWarnNoticeSelect::~EnemyWarnNoticeSelect() = default;

bool EnemyWarnNoticeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyWarnNoticeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyWarnNoticeSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyWarnNoticeSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool EnemyWarnNoticeSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyWarnNoticeSelect::leave_() {
    mActor->m93(0, 0.0f);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
}

void EnemyWarnNoticeSelect::loadParams_() {
    getStaticParam(&mWarnNoticeTime_s, "WarnNoticeTime");
    getStaticParam(&mWarnNoticeTimeRnd_s, "WarnNoticeTimeRnd");
    getStaticParam(&mWarnBlinkTime_s, "WarnBlinkTime");
    getStaticParam(&mLostCounter_s, "LostCounter");
    getStaticParam(&mIsSight_s, "IsSight");
    getStaticParam(&mIsWorry_s, "IsWorry");
    getDynamicParam(&mForceNotice_d, "ForceNotice");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getStaticParam(&mPenaltyStair2Num_s, "PenaltyStair2Num");
    getStaticParam(&mMaxCountUp_s, "MaxCountUp");
    getStaticParam(&mPenalty_s, "Penalty");
    getStaticParam(&mNoPenaltyNum_s, "NoPenaltyNum");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

void EnemyWarnNoticeSelect::m34() {
    setFinished();
}

bool EnemyWarnNoticeSelect::handleMessage_(const ksys::Message* message) {
    if (_b8.m2(*message) && _b8._38.mData._0 == *mTargetActor_d && _b8._38.mData._24 == 2) {
        _138 = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
