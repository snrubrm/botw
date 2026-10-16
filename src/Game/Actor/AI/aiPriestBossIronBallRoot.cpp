#include "Game/Actor/AI/aiPriestBossIronBallRoot.h"
#include "Game/Actor/Action/actionTeleportBase.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
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

PriestBossIronBallRoot::PriestBossIronBallRoot(const InitArg& arg) : PriestBoss(arg) {}

PriestBossIronBallRoot::~PriestBossIronBallRoot() {
    if (_70.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool PriestBossIronBallRoot::init_(sead::Heap* heap) {
    if (!PriestBoss::init_(heap))
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
    PriestBoss::enter_(params);
    sub_71007A3800(mActor);
    auto* actor = mActor;
    _26c = false;
    _80.makeAllZero();
    if (auto* lod = actor->getLodState())
        lod->mFlags26.reset(1);
    action::sub_710072BEC4(actor, nullptr, false);

    auto* body = mActor->getMainBody();
    if (body)
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
    m36();
    if (body && _268 <= 0.0f)
        _268 = body->getMass();

    _120.x();
    _90.x();
    m42();
    if (auto* physics_body = mActor->getPhysicsMainBody()) {
        physics_body->setLinearVelocity(sead::Vector3f::zero);
        physics_body->setAngularVelocity(sead::Vector3f::zero);
    }
    if (auto* main_body = mActor->getMainBody()) {
        const u32 mask = ksys::phys::orEntityGroundHitMask(0, ksys::phys::GroundHit::Giant);
        main_body->setGroundHitMask(main_body->getContactLayer(), mask);
    }
    sub_710072DC9C(mActor, 1.0f);
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
    {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        if (accessor.hasProc())
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
    actor->sub_71011D0204(4);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000);
    if (auto* unit = sub_7100505BE4(); unit && unit->_3cc) {
        m43(0, mActor->getMtx().getTranslation(), 0);
    }
}

// NON_MATCHING: the original stores the timer value and previous value separately (ours merges them).
// Grab check: starts a 5 s timer when the grabbed ball moves faster than the unit's threshold, and restores the
// ball once it is slow again after the timer.
void PriestBossIronBallRoot::sub_7100521870() {
    const f32 speed = mActor->getMainBody()->getLinearVelocity().length() * mActor->m38();
    auto* unit = sub_7100505BE4();
    if (_26c) {
        _270.update();
        if (unit && speed < unit->_438 && _270.value <= sead::Mathf::epsilon()) {
            m37();
            if (_27c != 0) {
                m36();
                sub_71005221EC(false);
                if (auto* body = mActor->getMainBody(); body && _268 > 0.0f)
                    body->setMass(_268);
            }
            _26c = false;
        }
        return;
    }

    auto* grab = mActor->m128();
    if (!grab || !grab->m2())
        return;
    if (unit) {
        if (!(speed > unit->_438))
            return;
        m38(false);
        _270.reset(5.0f);
    } else {
        m38(false);
    }
    _26c = true;
}

void PriestBossIronBallRoot::leave_() {
    PriestBoss::leave_();
    m35();
    _27c = 0;
}

void PriestBossIronBallRoot::loadParams_() {
    PriestBoss::loadParams_();
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mMagneLightningTime_s, "MagneLightningTime");
    getMapUnitParam(&mActorName_m, "ActorName");
}

// NON_MATCHING: the Flag temporaries of the first two branches get their own stack slots, and mActor
// is loaded after the payload lock (lane2 log: inline-helper forms)
bool PriestBossIronBallRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000007) {
        _80.setBit(Flag(Flag::_8));
        if (mActor->getConnectedCalcChild())
            mActor->resetConnectedCalcChild(false);
        {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&_70, &accessor);
            if (accessor.hasProc())
                accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
        mActor->fadeOutSleep(ksys::act::BaseProc::SleepWakeReason::_0);
        return true;
    }

    if (message->getType() == 0x3000003) {
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

    if (message->getType() == 0x3000004) {
        if (!_80.isOnBit(Flag(Flag::_0)) || mActor->getConnectedCalcChild()) {
            if (!_80.isOnBit(Flag(Flag::_6))) {
                if (_80.isOnBit(Flag(Flag::_7))) {
                    _80.resetBit(Flag(Flag::_7));
                    auto* unit = sub_7100505BE4();
                    ksys::act::ActorLinkConstDataAccess accessor;
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
                    _270.value = 5.0f;
                    _270.previous_value = 5.0f;
                    _26c = true;
                    _270.rate = -1.0f;
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

    if (_170.m2(*message)) {
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
        if (!_90.m2(*message))
            return false;
        if ((_90._38._48 & ~1) != 2)
            return true;
        _90.x();
        return false;
    }

    if (_120.m2(*message))
        return true;
    if (_90.m2(*message) && _90._38._48 == 0)
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
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_70, &accessor);
    if (accessor.hasProc())
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void PriestBossIronBallRoot::m40() {
    xlinkSearchAndEmit(mActor, sUnk_7102414068, 2, nullptr);
    mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_70, &accessor);
    if (accessor.hasProc())
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

// NON_MATCHING: the Flag temporary does not share the matrix's stack slot (lane2 log)
void PriestBossIronBallRoot::m41() {
    sead::Vector3f scale = sead::Vector3f::ones;
    if (_70.hasProc()) {
        scale *= 1.5f;
        ksys::act::ActorLinkConstDataAccess accessor;
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
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_238, &accessor);
    accessor.getActorMtx();
    ksys::act::ai::InlineParamPack params;
    params.addActor(_238, "TargetActor", -1);
    params.addVec3(base_pos, "BasePos", -1);
    params.addInt(wait_time, "WaitTime", -1);
    params.addInt(command, "Command", -1);
    changeChild("念受信", &params);
}

// NON_MATCHING: position/impulse registers and dot-product scheduling around cross length.
void PriestBossIronBallRoot::sub_7100520874(ksys::act::Unk_71006dc134* arg) {
    arg->_21 = false;
    if (!mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
        return;

    auto* unit = sub_7100505BE4();
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!unit || !unit->sub_71007194D4(1, &accessor))
        return;

    sead::Matrix34f head_matrix;
    const sead::Matrix34f* matrix = &head_matrix;
    if (!accessor.sub_7100D12944(&head_matrix, "Head"))
        matrix = &accessor.getActorMtx();
    sead::Vector3f direction = matrix->getTranslation();
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    direction -= position;
    direction.normalize();
    const f32 impulse = arg->_0.length();
    if (!arg->_18)
        return;

    ksys::act::ActorLinkConstDataAccess source;
    if (!ksys::act::acquireActor(&arg->_18->_d8, &source) || !source.isPlayerProfile())
        return;

    sead::Vector3f contact_direction = position - arg->_18->_58.getTranslation();
    contact_direction.y = 0.0f;
    contact_direction.normalize();
    const sead::Vector3f horizontal(direction.x, 0.0f, direction.z);
    const f32 angle = std::atan2(contact_direction.cross(horizontal).length(),
                                horizontal.dot(contact_direction));
    if (sead::Mathf::abs(angle) < sead::Mathf::pi() * 0.375f) {
        arg->_0 = direction * impulse;
        _80.setBit(Flag(Flag::_7));
    }
}

void PriestBossIronBallRoot::sub_71005221EC(bool value) {
    auto* unit = sub_7100505BE4();
    if (!unit)
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
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
