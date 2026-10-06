#include "Game/AI/AI/aiUnarmedEnemyNoiseTarget.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

// NON_MATCHING: scheduling / register allocation of the inlined FixedObjList setup stores (the node addresses now match)
UnarmedEnemyNoiseTarget::UnarmedEnemyNoiseTarget(const InitArg& arg) : UnarmedEnemySearch(arg) {}

UnarmedEnemyNoiseTarget::~UnarmedEnemyNoiseTarget() = default;

void UnarmedEnemyNoiseTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _e0 = sub_71005D9330(mActor);
    _100.clear();
    _c8 = *mLostTime_s;
    UnarmedEnemySearch::enter_(params);
}

void UnarmedEnemyNoiseTarget::m35(const sead::Vector3f& target) {
    sub_71005D4C28();
    UnarmedEnemySearch::m35(target);
}

void UnarmedEnemyNoiseTarget::leave_() {
    UnarmedEnemySearch::leave_();
    sub_71005DB3EC(mActor);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->sub_7100019C58(sub_71005D83E8(enemy, *mWeaponIdx_s));
        enemy->sub_7100019D38(_d0);
    }
    _100.clear();
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

// 0x71005d4ab0
void UnarmedEnemyNoiseTarget::sub_71005D4AB0() {
    ksys::act::ai::InlineParamPack pack;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(_d0.getProc(nullptr, nullptr));
    pack.acquireActor(actor, "TargetWeapon", -1);
    changeChild("武器発見", &pack);
}

}  // namespace uking::ai
