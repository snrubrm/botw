#include "Game/AI/AI/aiForestGiantStoneShootBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ForestGiantStoneShootBattle::ForestGiantStoneShootBattle(const InitArg& arg)
    : StoneShootEnemyBattle(arg) {}

// The SafeString member makes the original keep the vtable store that a defaulted destructor drops;
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
ForestGiantStoneShootBattle::~ForestGiantStoneShootBattle() { ; }

void ForestGiantStoneShootBattle::calc_() {
    if (isCurrentChild("戦闘準備") && getCurrentChild()->isChangeable()) {
        const auto& pos = mActor->getMtx().getTranslation();
        if ((pos - sub_71005D9330(mActor)).length() <= *mForceAttackArea_s) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("近接攻撃", &pack);
            return;
        }
    }

    if (isCurrentChild("近接攻撃")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            if (getCurrentChild()->isFailed()) {
                setFailed();
                return;
            }
            sub_7100381ED4();
            m37();
            return;
        }
    }

    StoneShootEnemyBattle::calc_();
}

bool ForestGiantStoneShootBattle::init_(sead::Heap* heap) {
    return StoneShootEnemyBattle::init_(heap);
}

void ForestGiantStoneShootBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    StoneShootEnemyBattle::enter_(params);
}

void ForestGiantStoneShootBattle::leave_() {
    StoneShootEnemyBattle::leave_();
}

void ForestGiantStoneShootBattle::loadParams_() {
    StoneShootEnemyBattle::loadParams_();
    getStaticParam(&mShootItemRate1_s, "ShootItemRate1");
    getStaticParam(&mForceAttackArea_s, "ForceAttackArea");
    getStaticParam(&mShootItemName2_s, "ShootItemName2");
}

bool ForestGiantStoneShootBattle::m41() {
    return true;
}

}  // namespace uking::ai
