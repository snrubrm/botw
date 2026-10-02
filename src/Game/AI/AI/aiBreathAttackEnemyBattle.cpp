#include "Game/AI/AI/aiBreathAttackEnemyBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

BreathAttackEnemyBattle::BreathAttackEnemyBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BreathAttackEnemyBattle::~BreathAttackEnemyBattle() = default;

bool BreathAttackEnemyBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BreathAttackEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BreathAttackEnemyBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BreathAttackEnemyBattle::loadParams_() {
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mBreathSize_s, "BreathSize");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mGlobalNoAtkTime_s, "GlobalNoAtkTime");
    getStaticParam(&mIsEndAfterAttack_s, "IsEndAfterAttack");
    getStaticParam(&mIsDeleteBreath_s, "IsDeleteBreath");
    getStaticParam(&mBreathName_s, "BreathName");
    getStaticParam(&mIsUpdateNoticeState_s, "IsUpdateNoticeState");
}

ksys::act::BaseProcLink& BreathAttackEnemyBattle::m34() {
    auto* link = sub_71005D9050(mActor);
    if (link != nullptr)
        return *link;
    return ksys::act::getDummyBaseProcLink();
}

const sead::Vector3f* BreathAttackEnemyBattle::m35() {
    return &sub_71005D9330(mActor);
}

const sead::SafeString& BreathAttackEnemyBattle::m36() {
    return mBreathName_s;
}

void BreathAttackEnemyBattle::m41() {}

bool BreathAttackEnemyBattle::m44() {
    return _90.isProcReady();
}

}  // namespace uking::ai
