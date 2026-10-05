#include "Game/AI/AI/aiPriestBossGiantEnemyRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710071edf8.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

// Declaration only; the original source namespace is unknown.
bool sub_710071E80C(ksys::act::Actor* actor, Unk_7102450fa8* unit);
bool sub_710071EB88(ksys::act::Actor* actor);

namespace uking::ai {

static const sead::SafeString sUnk_7102413930 = "Priest_Boss_IronBall";
static const sead::SafeString sUnk_7102413950 = "ironball_attack";

void Unk_7102413808::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 >= 0) {
        _24 = 0;
        sub_710051A6B8();
        if (_24 == 1) {
            *a1 = 0;
            *a2 = 0;
            *a3 = 0;
            *a5 = -1;
            *a4 = 0xffffffff;
        }
    }
}

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
    if (!_2e8.mDamageManager)
        mActor->getDamageMgr()->addDamageCallback(0, &_2e8);
    if (!_368.mDamageManager)
        mActor->getDamageMgr()->addDamageCallback(2, &_368);
    if (mInvalidateIronBallDamageFrame_s)
        _2e8._2c = *mInvalidateIronBallDamageFrame_s;
    _2e8._40.bind(this, &PriestBossGiantEnemyRoot::sub_710051AD38);
    _2e8._60.bind(this, &PriestBossGiantEnemyRoot::sub_7100506A40);
    sub_71007214A0(&_248, mActor, "DyanmicBody", "Body", sead::SafeString::cEmptyString,
                   sead::Mathf::infinity());
    if (auto* lod = mActor->getLodState())
        lod->mFlags10.set(2);
    getActorAttackSensor(mActor)->_20 |= 8;
    _368._28 = -1;
}

// NON_MATCHING: separate string objects produce different offsets and load scheduling.
void PriestBossGiantEnemyRoot::calc_() {
    sub_710071EB3C(mActor);
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        auto* handler = actor->_868;
        if (_368._28 >= 0) {
            if (handler) {
                auto* instance = mActor->getPhysics();
                if (actor->sub_71011CEA90()) {
                    if (instance && instance->sub_7100FBDA2C(sUnk_7102413950) != handler->_c8)
                        _368._28 = handler->_c8;
                } else {
                    handler->_c8 = _368._28;
                    _368._28 = -1;
                }
            }
        } else {
            auto* manager = sead::DynamicCast<dmg::DamageManager>(mActor->getDamageMgr());
            if (manager && manager->getField50() == 5) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(manager->m37(), &accessor);
                if (accessor.hasProc() && accessor.getName() == sUnk_7102413930 && handler) {
                    _368._28 = handler->_c8;
                    handler->sub_71006EE280(sUnk_7102413950);
                }
            }
        }
    }
    sub_710051B0F8();
    PriestBossActorEnemyRoot::calc_();
    *mPriestBossDownSideASPlaying_a = sub_710071EB88(mActor);
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
