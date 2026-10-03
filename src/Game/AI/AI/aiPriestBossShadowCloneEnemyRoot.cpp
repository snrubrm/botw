#include "Game/AI/AI/aiPriestBossShadowCloneEnemyRoot.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
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

// NON_MATCHING: same as NPCHorseRideWait::leave_ (the original rematerialises &accessor for the destructor
// instead of keeping it in a callee-saved register; regalloc only)
void PriestBossShadowCloneEnemyRoot::sub_710052D6E8() {
    auto* unit = sub_7100506A40();
    if (!unit)
        return;
    if (!unit->sub_7100719978(unit->sub_7100719534(mActor)))
        return;

    ksys::act::ActorConstDataAccess accessor;
    if (unit->sub_71007194CC(&accessor)) {
        {
            // inline-only in the original; the same sequence as setPayload() in PriestBossShadowCloneThrow
            // (the actor is loaded before the lock)
            auto* actor = mActor;
            sead::ScopedLock<sead::JobQueueLock> lock(&_258._18.mLock);
            _258._18._0 = 4;
            _258._18._18 = false;
            _258._18.mLink.acquire(actor, false);
        }
        _258.sub_710070DBB0(*accessor.getMessageTransceiverId(), false);
    }
}

bool PriestBossShadowCloneEnemyRoot::m45() {
    return m35();
}

}  // namespace uking::ai
