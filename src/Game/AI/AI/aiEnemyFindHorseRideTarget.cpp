#include "Game/AI/AI/aiEnemyFindHorseRideTarget.h"
#include <random/seadGlobalRandom.h>
#include <limits>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyFindHorseRideTarget::EnemyFindHorseRideTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyFindHorseRideTarget::~EnemyFindHorseRideTarget() = default;

bool EnemyFindHorseRideTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyFindHorseRideTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _a4 = *mLostTimer_s;
    _a8 = _a4 + 5;
    _a0 = sead::GlobalRandom::instance()->getS32Range(_a4, _a8);
    _ac = sead::GlobalRandom::instance()->getS32Range(*mChaseTime_s, *mChaseTime_s + 5);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("追跡", &pack);
}

bool EnemyFindHorseRideTarget::sub_710038D018() {
    const sead::Vector3f& velocity = sub_71005D9548(mActor);
    if (sead::Mathf::sqrt(velocity.x * velocity.x + velocity.z * velocity.z) < *mAttackTargetSpeed_s) {
        const auto& target = sub_71005D9330(mActor);
        auto* actor = mActor;
        const f32 max_dist = *mAttackRange_s + sub_71007320F0(actor, *mWeaponIdx_s);
        return inlineIsTargetInReach(target, max_dist, *mAttackVMin_s, *mAttackVMax_s,
                                     actor->getMtx(), sead::Mathf::pi(), sead::Mathf::maxNumber(),
                                     0.8f);
    }
    return false;
}

void EnemyFindHorseRideTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyFindHorseRideTarget::loadParams_() {
    getStaticParam(&mSurpriseAttackPer_s, "SurpriseAttackPer");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mChaseTime_s, "ChaseTime");
    getStaticParam(&mSurpriseAttackRange_s, "SurpriseAttackRange");
    getStaticParam(&mAttackRange_s, "AttackRange");
    getStaticParam(&mAttackVMin_s, "AttackVMin");
    getStaticParam(&mAttackVMax_s, "AttackVMax");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mLostRange_s, "LostRange");
    getStaticParam(&mAttackTargetSpeed_s, "AttackTargetSpeed");
    getStaticParam(&mReChaseDist_s, "ReChaseDist");
}

}  // namespace uking::ai
