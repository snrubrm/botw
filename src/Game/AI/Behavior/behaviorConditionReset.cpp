#include "Game/AI/Behavior/behaviorConditionReset.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

namespace uking::behavior {

ConditionReset::ConditionReset(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ConditionReset::~ConditionReset() = default;

bool ConditionReset::m6(sead::Heap* heap) {
    return true;
}

void ConditionReset::m7() {}

void ConditionReset::m9() {}

void ConditionReset::loadParams() {
    getStaticParam(&mIsResetBurn_s, "IsResetBurn");
    getStaticParam(&mIsResetIce_s, "IsResetIce");
    getStaticParam(&mIsResetElectric_s, "IsResetElectric");
}

void ConditionReset::m8() {
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (!actor)
        return;
    if (*mIsResetBurn_s)
        actor->m149(2);
    if (*mIsResetIce_s)
        actor->m149(1);
    if (*mIsResetElectric_s)
        actor->m149(4);
}

void ConditionReset::m11() {
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (!actor)
        return;
    if (*mIsResetBurn_s)
        actor->m149(2);
    if (*mIsResetIce_s)
        actor->m149(1);
    if (*mIsResetElectric_s)
        actor->m149(4);
}

}  // namespace uking::behavior
