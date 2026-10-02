#include "Game/AI/AI/aiPriestBossShadowCloneEnemyRoot.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::ai {

PriestBossShadowCloneEnemyRoot::PriestBossShadowCloneEnemyRoot(const InitArg& arg)
    : PriestBossActorEnemyRoot(arg) {}

PriestBossShadowCloneEnemyRoot::~PriestBossShadowCloneEnemyRoot() = default;

bool PriestBossShadowCloneEnemyRoot::init_(sead::Heap* heap) {
    return PriestBossActorEnemyRoot::init_(heap);
}

void PriestBossShadowCloneEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorEnemyRoot::enter_(params);
    if (!_230.mDamageManager)
        mActor->getDamageMgr()->addDamageCallback(2, &_230);
    mActor->clearFadeInCreate();

    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* unk = sead::DynamicCast<act::Unk_710244dd20>(actor->m159()))
            unk->_88.x();
    }
}

void PriestBossShadowCloneEnemyRoot::calc_() {
    PriestBossActorEnemyRoot::calc_();
}

void PriestBossShadowCloneEnemyRoot::leave_() {
    PriestBossActorEnemyRoot::leave_();
    sub_710052D6E8();
    mActor->getDamageMgr()->removeDamageCallback(&_230);
}

void PriestBossShadowCloneEnemyRoot::loadParams_() {
    PriestBossActorEnemyRoot::loadParams_();
}

bool PriestBossShadowCloneEnemyRoot::m45() {
    return m35();
}

}  // namespace uking::ai
