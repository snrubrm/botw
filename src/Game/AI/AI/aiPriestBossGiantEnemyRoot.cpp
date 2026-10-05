#include "Game/AI/AI/aiPriestBossGiantEnemyRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"

// Declaration only; the original source namespace is unknown.
bool sub_710071E80C(ksys::act::Actor* actor, Unk_7102450fa8* unit);

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

bool PriestBossGiantEnemyRoot::m35() {
    return sub_710071E80C(mActor, sub_7100506A40());
}

// NON_MATCHING: the range checks are folded and the bit index remains a plain integer.
bool PriestBossGiantEnemyRoot::handleMessage_(const ksys::Message* message) {
    PriestBossActorEnemyRoot::handleMessage_(message);
    if (mActor->getLifeRecoverInfo() && message->getType() == ksys::MessageType(0x80000dd)) {
        mActor->getLifeRecoverInfo()->sub_7100D68E54(message);
        return true;
    }
    if (!_2a8.m2(*message))
        return false;
    const s32 index = _2a8._34._8;
    if (index < 0) {
        _2e8._28 = 0;
    } else {
        const u32 enabled = _2a8._34._4;
        if (_2e8._60() && index >= 11 && index <= 29 && index != 19) {
            const u32 mask = 1u << (index - 11);
            if (enabled)
                _2e8._28 |= mask;
            else
                _2e8._28 &= ~mask;
        }
    }
    return true;
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

bool PriestBossGiantEnemyRoot::m51() {
    if (sub_7100506A40() && !isCurrentChild("フェイズ開始") && !m45() &&
        _1e8 != int(sub_7100506A40()->_3c)) {
        sub_7100506DB0();
        changeChild("フェイズ開始", nullptr);
        return true;
    }
    return PriestBossActorEnemyRoot::m51();
}

bool PriestBossGiantEnemyRoot::m53() {
    if (!_1c8 && sub_7100506A40() && sub_7100506A40()->_3c == Unk_7102450fa8::Phase::_3 &&
        !m52()) {
        return m45();
    }
    return PriestBossActorEnemyRoot::m53();
}

}  // namespace uking::ai
