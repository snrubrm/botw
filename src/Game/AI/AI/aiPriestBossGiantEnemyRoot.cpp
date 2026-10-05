#include "Game/AI/AI/aiPriestBossGiantEnemyRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

// NON_MATCHING: the first stores (params, contact callbacks, sender) are scheduled differently
PriestBossGiantEnemyRoot::PriestBossGiantEnemyRoot(const InitArg& arg)
    : PriestBossActorEnemyRoot(arg) {}

PriestBossGiantEnemyRoot::~PriestBossGiantEnemyRoot() = default;

bool PriestBossGiantEnemyRoot::init_(sead::Heap* heap) {
    if (!PriestBossActorEnemyRoot::init_(heap))
        return false;
    _268._8 = &mActor->getMessageTransceiver();
    return true;
}

void PriestBossGiantEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorEnemyRoot::enter_(params);
}

void PriestBossGiantEnemyRoot::leave_() {
    PriestBossActorEnemyRoot::leave_();
    sub_71005DB3EC(mActor);
    mActor->getDamageMgr()->removeDamageCallback(&_2e8);
    mActor->getDamageMgr()->removeDamageCallback(&_368);
}

void PriestBossGiantEnemyRoot::loadParams_() {
    PriestBossActorEnemyRoot::loadParams_();
    getStaticParam(&mInvalidateIronBallDamageFrame_s, "InvalidateIronBallDamageFrame");
    getAITreeVariable(&mPriestBossDownSideASPlaying_a, "PriestBossDownSideASPlaying");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

bool PriestBossGiantEnemyRoot::m45() {
    if (_1c8)
        return true;
    if (!sub_7100506A40())
        return false;
    switch (sub_7100506A40()->_3c) {
    case Unk_7102450fa8::Phase::_2:
        return true;
    case Unk_7102450fa8::Phase::_3: {
        const s32* life = mActor->getLife();
        return life && *life < 1;
    }
    default:
        return false;
    }
}

bool PriestBossGiantEnemyRoot::m47() {
    return false;
}

bool PriestBossGiantEnemyRoot::m46() {
    if (sub_7100506A40())
        (void)int(sub_7100506A40()->_3c);
    return false;
}

void PriestBossGiantEnemyRoot::m49() {
    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_20))
        ksys::act::disableAttClient(mActor, "LockOn");
    else
        ksys::act::enableAttClient(mActor, "LockOn");
}

bool PriestBossGiantEnemyRoot::m52() {
    return PriestBossActorEnemyRoot::m52();
}

bool PriestBossGiantEnemyRoot::m53() {
    if (!_1c8 && sub_7100506A40() && sub_7100506A40()->_3c == Unk_7102450fa8::Phase::_3 &&
        !m52()) {
        return m45();
    }
    return PriestBossActorEnemyRoot::m53();
}

}  // namespace uking::ai
