#include "Game/AI/AI/aiForestGiantBattle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

ForestGiantBattle::ForestGiantBattle(const InitArg& arg) : EnemyBattle(arg) {}

ForestGiantBattle::~ForestGiantBattle() = default;

bool ForestGiantBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void ForestGiantBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void ForestGiantBattle::calc_() {
    EnemyBattle::calc_();
}

void ForestGiantBattle::leave_() {
    EnemyBattle::leave_();
}

void ForestGiantBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mForceAttackArea_s, "ForceAttackArea");
}

bool ForestGiantBattle::m39() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const auto& target_pos = sub_71005D9330(mActor);
    if ((pos - target_pos).length() <= *mForceAttackArea_s)
        return true;
    return EnemyBattle::m39();
}

void ForestGiantBattle::m43(ksys::act::ai::InlineParamPack* params) {
    if (auto* link = sub_71005D9050(mActor))
        params->addActor(*link, "ShootItem", -1);
    else
        params->addActor(ksys::act::sUnk_71026505e0, "ShootItem", -1);
}

}  // namespace uking::ai
