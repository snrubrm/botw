#include "Game/AI/AI/aiPriestBossIronBallRoot.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

const char* sUnk_7102414060 = "Explosion";
const char* sUnk_7102414068 = "Disappear";

PriestBossIronBallRoot::PriestBossIronBallRoot(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossIronBallRoot::~PriestBossIronBallRoot() {
    if (_70.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool PriestBossIronBallRoot::init_(sead::Heap* heap) {
    if (!PriestBossMode::init_(heap))
        return false;

    if (!sub_71005D6D10()) {
        ksys::act::InstParamPack pack;
        pack->add(*mAttackPower_s, "AttackPower");
        pack->add(*mAttackPowerForPlayer_s, "AttackPowerForPlayer");
        pack->add(*mAtMinDamage_s, "AtMinDamage");
        auto* actor = ksys::act::ActorCreator::instance()->createActor(
            mActorName_m.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack,
            true, false);
        if (actor) {
            _70.acquire(actor, false);
            if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor))
                bullet->sub_710000497C(mActor);
        }
    }

    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return false;
    actor->_a70 = &_248;
    return true;
}

void PriestBossIronBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossIronBallRoot::leave_() {
    PriestBossMode::leave_();
    m35();
    _27c = 0;
}

void PriestBossIronBallRoot::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mMagneLightningTime_s, "MagneLightningTime");
    getMapUnitParam(&mActorName_m, "ActorName");
}

// NON_MATCHING: the Flag temporaries of the first two branches get their own stack slots, and mActor
// is loaded after the payload lock (lane2 log: inline-helper forms)
bool PriestBossIronBallRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x3000007) {
        _80.setBit(Flag(Flag::_8));
        if (mActor->getConnectedCalcChild())
            mActor->resetConnectedCalcChild(false);
        {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&_70, &accessor);
            if (accessor.hasProc())
                accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
        mActor->fadeOutSleep(ksys::act::BaseProc::SleepWakeReason::_0);
        return true;
    }

    if (message.getType().value == 0x3000003) {
        if (auto* body = mActor->getMainBody(); body && _268 > 0)
            body->setMass(_268 * 5.0f);
        m35();
        _90.x();
        m42();
        if (auto* body = mActor->getMainBody())
            body->setGroundHitMask(body->getContactLayer(), 0);
        _80.setBit(Flag(Flag::_4));
        return true;
    }

    if (message.getType().value == 0x3000004) {
        if (!_80.isOnBit(Flag(Flag::_0)) || mActor->getConnectedCalcChild()) {
            if (!_80.isOnBit(Flag(Flag::_6))) {
                if (_80.isOnBit(Flag(Flag::_7))) {
                    _80.resetBit(Flag(Flag::_7));
                    auto* unit = sub_7100505BE4();
                    ksys::act::ActorConstDataAccess accessor;
                    if (unit && unit->sub_71007194CC(&accessor)) {
                        {
                            sead::ScopedLock<sead::JobQueueLock> lock(&_1d0._18.mLock);
                            _1d0._18._0 = 3;
                            _1d0._18._4 = sead::Vector3f::zero;
                        }
                        _1d0._18.mLink.acquire(mActor, false);
                        _1d0.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
                    }
                    m38(true);
                    sub_71005221EC(true);
                    _270 = 5.0f;
                    _274 = 5.0f;
                    _26c = true;
                    _278 = -1.0f;
                } else if (auto* body = mActor->getMainBody(); body && _268 > 0) {
                    body->setMass(_268);
                }
                m42();
            }
        } else {
            _80.setBit(Flag(Flag::_9));
            _80.setBit(Flag(Flag::_6));
        }
    }

    if (_170.m2(message)) {
        switch (_170._38._0) {
        case 1:
            if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
                _80.setBit(Flag(Flag::_6));
            else
                m39();
            break;
        case 4:
            m41();
            break;
        }
        _170.x();
        return true;
    }

    if (isCurrentChild("待機")) {
        if (_90._30)
            return false;
        if (auto* unk = mActor->m128(); unk && unk->m2())
            return false;
        if (!_90.m2(message))
            return false;
        if ((_90._38._48 & ~1) != 2)
            return true;
        _90.x();
        return false;
    }

    if (_120.m2(message))
        return true;
    if (_90.m2(message) && _90._38._48 == 0)
        return true;
    return false;
}

void PriestBossIronBallRoot::m35() {
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    if (!body)
        return;
    sub_71007A2D34(body);
    sub_71007A3258(body, nullptr);
}

void PriestBossIronBallRoot::m36() {
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    if (!body)
        return;
    if (!body->isAddedToWorld())
        body->setTransform(actor->getMtx());
    getActorAttackSensor(actor)->activateAttackSensor(
        0x2000, 2, actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(),
        actor->getParam()->getRes().mGParamList->getAttack()->mImpulseLarge.ref(), 0.0f, 0,
        actor->getParam()->getRes().mGParamList->getAttack()->mGuardBreakPower.ref(), -1, false, 1,
        -1);
    sub_71007A2B64(body, nullptr);
    sub_71007A2EB0(body, actor, nullptr);
}

void PriestBossIronBallRoot::m37() {
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBodyPlayer");
    if (!body)
        return;
    sub_71007A2D34(body);
    sub_71007A3258(body, nullptr);
}

void PriestBossIronBallRoot::m38(bool for_player) {
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBodyPlayer");
    if (!body)
        return;
    if (!body->isAddedToWorld())
        body->setTransform(actor->getMtx());
    s32 power = 0;
    if (auto* unit = sub_7100505BE4()) {
        if (for_player)
            power = unit->_440;
        else
            power = unit->_43c;
    }
    getActorAttackSensor(actor)->activateAttackSensor(
        0x2000, 2, power, 1, 0.0f, 1,
        actor->getParam()->getRes().mGParamList->getAttack()->mGuardBreakPower.ref(), -1, false, 1,
        -1);
    sub_71007A2B64(body, nullptr);
    sub_71007A2EB0(body, actor, nullptr);
}

void PriestBossIronBallRoot::m39() {
    xlinkSearchAndEmit(mActor, sUnk_7102414060, 2, nullptr);
    mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_70, &accessor);
    if (accessor.hasProc())
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void PriestBossIronBallRoot::m40() {
    xlinkSearchAndEmit(mActor, sUnk_7102414068, 2, nullptr);
    mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_70, &accessor);
    if (accessor.hasProc())
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

// NON_MATCHING: the Flag temporary does not share the matrix's stack slot (lane2 log)
void PriestBossIronBallRoot::m41() {
    sead::Vector3f scale = sead::Vector3f::ones;
    if (_70.hasProc()) {
        scale *= 1.5f;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        if (!accessor.isStateCalc()) {
            sead::Matrix34f mtx;
            mtx.makeIdentity();
            sead::Vector3f pos = mActor->getMtx().getTranslation();
            pos.y += 0.1f;
            mtx.setTranslation(pos);
            accessor.setThisActorAsChild(mActor, false);
            accessor.setProperties(mtx, nullptr, nullptr, &scale, false, 0, -1);
        }
        _80.setBit(Flag(Flag::_0));
    }
}

void PriestBossIronBallRoot::m42() {
    changeChild("待機");
}

void PriestBossIronBallRoot::m43(s32 command, const sead::Vector3f& base_pos, s32 wait_time) {
    _120.x();
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_238, &accessor);
    accessor.getActorMtx();
    ksys::act::ai::InlineParamPack params;
    params.addActor(_238, "TargetActor", -1);
    params.addVec3(base_pos, "BasePos", -1);
    params.addInt(wait_time, "WaitTime", -1);
    params.addInt(command, "Command", -1);
    changeChild("念受信", &params);
}

// NON_MATCHING: the u32 temporary for sub_710070E2BC gets another stack slot (x29-0x14 vs -0x18)
void PriestBossIronBallRoot::sub_71005221EC(bool value) {
    auto* unit = sub_7100505BE4();
    if (!unit)
        return;
    ksys::act::ActorConstDataAccess accessor;
    unit->sub_71007194D4(1, &accessor);
    if (accessor.hasProc()) {
        const s32 idx = unit->sub_7100719534(mActor);
        if (idx != -1) {
            _210.sub_710070E2BC(value, idx);
            if (_210.sub_710070DBB0(*accessor.getMessageTransceiverId(), true))
                _27c = value;
        }
    }
}

}  // namespace uking::ai
