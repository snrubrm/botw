#include "Game/AI/AI/aiUnarmedEnemyNoiseTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

// NON_MATCHING: FixedObjList<Unk_7100d78e50, 8> free-node links start at 0x12c in the original (nodes packed at 4-byte alignment), we emit 0x130 and a different store order
UnarmedEnemyNoiseTarget::UnarmedEnemyNoiseTarget(const InitArg& arg) : UnarmedEnemySearch(arg) {}

UnarmedEnemyNoiseTarget::~UnarmedEnemyNoiseTarget() = default;

void UnarmedEnemyNoiseTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _e0 = sub_71005D9330(mActor);
    _100.clear();
    _c8 = *mLostTime_s;
    UnarmedEnemySearch::enter_(params);
}

void UnarmedEnemyNoiseTarget::leave_() {
    UnarmedEnemySearch::leave_();
}

void UnarmedEnemyNoiseTarget::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mLostTime_s, "LostTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLostRange_s, "LostRange");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mSearchWeaponDist_s, "SearchWeaponDist");
    getStaticParam(&mSearchBaseWeaponDist_s, "SearchBaseWeaponDist");
    getStaticParam(&mAbsorpDist_s, "AbsorpDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mSearchWeaponTargetDist_s, "SearchWeaponTargetDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
