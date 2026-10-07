#include "Game/AI/Action/actionForkStalPartApplyDamageImpulse.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkStalPartApplyDamageImpulse::ForkStalPartApplyDamageImpulse(const InitArg& arg) : Fork(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkStalPartApplyDamageImpulse::~ForkStalPartApplyDamageImpulse() {
    ;
}

bool ForkStalPartApplyDamageImpulse::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkStalPartApplyDamageImpulse::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    _a8 = false;
    _ac.set(0.0f, 0.0f, 0.0f);
    sub_710073FA90(&_c4, mActor);
}

void ForkStalPartApplyDamageImpulse::leave_() {
    Fork::leave_();
}

void ForkStalPartApplyDamageImpulse::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mMaxAddSpeed_s, "MaxAddSpeed");
    getStaticParam(&mSwordRate_s, "SwordRate");
    getStaticParam(&mSpearRate_s, "SpearRate");
    getStaticParam(&mLswordRate_s, "LswordRate");
    getStaticParam(&mArrowRate_s, "ArrowRate");
    getStaticParam(&mBombRate_s, "BombRate");
    getStaticParam(&mGustRate_s, "GustRate");
    getStaticParam(&mLargeAttackAddRate_s, "LargeAttackAddRate");
    getStaticParam(&mMaxAddSpeedY_s, "MaxAddSpeedY");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mRotAccMaxSpeedRatio_s, "RotAccMaxSpeedRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsViewHitDir_s, "IsViewHitDir");
}

// NON_MATCHING: the original loads the matrix translation components before the _ac
// components in the two direction subtractions below (the s8/s9 assignment cascades from that
// order); this version is otherwise instruction-identical.
void ForkStalPartApplyDamageImpulse::calc_() {
    Fork::calc_();
    sub_7100165930();
    if (!_a8)
        return;
    sub_710073FA94(&_c4, mActor);
    _b8.lerp(*mRotSpd_s, *mRotAccRatio_s, (*mRotSpd_s) * (*mRotAccMaxSpeedRatio_s));
    _b8.updateStats();
    sead::Vector3f dir;
    dir.x = _ac.x - mActor->getMtx().m[0][3];
    dir.y = 0.0f;
    dir.z = _ac.z - mActor->getMtx().m[2][3];
    dir.normalize();
    sub_710074006C(&_c4, dir, sead::Vector3f::ey, false, *mBaseRotRatio_s, _b8.value,
                   _b8.value / 10.0f);
    sub_7100740F1C(_c4, mActor);
}

}  // namespace uking::action
