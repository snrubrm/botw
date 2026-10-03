#include "Game/AI/AI/aiSiteBossReaction.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

SiteBossReaction::SiteBossReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SiteBossReaction::~SiteBossReaction() {
    ;
}

bool SiteBossReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void SiteBossReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

// NON_MATCHING: the original addresses SiteBoss _2378-_237b through one base register (see
// SiteBossSpearThrow); everything else matches
void SiteBossReaction::leave_() {
    EnemyDefaultReaction::leave_();

    if (_70) {
        if (auto* physics = mActor->getPhysics()) {
            if (auto* cloth = physics->getClothSet()) {
                auto& entry = cloth->_18[0];
                if (!(entry._18 & 0x400))
                    entry._3c = 1.0f;
            }
        }
    }

    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (actor->_868 && actor->_868->sub_71006EDDD4())
            actor->sub_71006DD92C(true);
    }

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_2378) {
            boss->_237a = boss->_237b;
            boss->_2378 = 0;
        }
        if (boss->_14c8._30.isOnBit(9)) {
            boss->_14c8._30.resetBit(9);
            changeAS("Wait_Battle", false, 2, 0);
            boss->_1518 = 0;
        }
        if (boss->_14c8._30.isOnBit(1))
            boss->_14c8._30.resetBit(1);
    }
}

void SiteBossReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mIsChangeEffectiveDamage_s, "IsChangeEffectiveDamage");
}

bool SiteBossReaction::m36(int damage_type) {
    if (_74++ >= 3) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
            boss->_1558.set(4);
    }
    return false;
}

}  // namespace uking::ai
