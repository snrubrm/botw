#include "Game/Actor/AI/aiRemainsWaterChaseBulletRoot.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

RemainsWaterChaseBulletRoot::RemainsWaterChaseBulletRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
RemainsWaterChaseBulletRoot::~RemainsWaterChaseBulletRoot() {
    ;
}

bool RemainsWaterChaseBulletRoot::init_(sead::Heap* heap) {
    mActor->sub_71011D0204(0x40);
    _3c = false;
    return true;
}

void RemainsWaterChaseBulletRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody())
        body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    auto* actor = mActor;
    _39 = false;
    _3a = false;
    _3b = false;
    sub_71007A458C(actor, true);
    actor->sub_71011D0228(0x80);
    if (auto* set = mActor->getPhysics()->findBodyByName(*sub_71007A24BC())) {
        if (auto* body = set->findBodyByHavokName("BulletAtk"))
            body->enableContactLayer(ksys::phys::ContactLayer::SensorPlayer);
    }
    if (auto* sensor = getActorAttackSensor(actor)) {
        sensor->activateAttackSensor(
            0x2000, 8, actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(),
            actor->getParam()->getRes().mGParamList->getAttack()->mImpulseLarge.ref(), 0.0f, 0,
            actor->getParam()->getRes().mGParamList->getAttack()->mGuardBreakPower.ref(), -1,
            false, *mParams.mAtkMinDamage_s, -1);
    }

    if (_3c) {
        _3c = false;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_40, "TargetPos", -1);
        changeChild("復活", &pack);
    } else {
        sub_710054AC5C();
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000);
        changeChild("待機");
    }
}

void RemainsWaterChaseBulletRoot::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("復活")) {
            sub_710054AC5C();
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000);
            changeChild("待機");
            return;
        }
        if (isCurrentChild("通常") || isCurrentChild("待機")) {
            sub_7100549E90();
            return;
        }
        if (isCurrentChild("爆発")) {
            mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
            return;
        }
        if (isCurrentChild("ダメージ")) {
            _39 = false;
            sub_710054AAD8();
            changeChild("消滅");
            return;
        }
    }

    if (isCurrentChild("通常") || isCurrentChild("待機") || isCurrentChild("ダメージ")) {
        if (sub_7100549F6C()) {
            sub_7100549E90();
            return;
        }
        sub_710054A100();
        sub_710054A2CC();
        if (_39) {
            _39 = false;
            sub_710054AAD8();
            changeChild("消滅");
        }
        if (_3b && !isCurrentChild("ダメージ")) {
            _3b = false;
            changeChild("ダメージ");
        }
    }

    if (isCurrentChild("通常") && sub_710054A6C0()) {
        sub_7100549E90();
        return;
    }

    if (_3a && isCurrentChild("待機"))
        sub_710054A930();
}

// Whether the player touches the bullet's "PlayerSensor" body.
bool RemainsWaterChaseBulletRoot::sub_7100549F6C() {
    auto* physics = mActor->getPhysics();
    if (!physics)
        return false;
    auto* set = physics->findBodyByName(*sub_71007A2548());
    if (!set)
        return false;
    auto* sensor = set->findBodyByHavokName("PlayerSensor");
    if (!sensor)
        return false;
    auto* info = sensor->getCollisionInfo();
    if (!info || info->getCollidingBodies().size() == 0)
        return false;

    auto* bodies = info->getCollidingBodies().front();
    info->lock();
    for (; bodies; bodies = info->getCollidingBodies().next(bodies)) {
        auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(bodies->bodies[1]->getUserTag());
        if (!tag)
            continue;
        bool is_player;
        {
            ksys::act::ActorLinkConstDataAccess accessor;
            tag->acquireActor(&accessor);
            is_player = accessor.isPlayerProfile();
        }
        if (is_player) {
            info->unlock();
            return true;
        }
    }
    info->unlock();
    return false;
}

// NON_MATCHING: the original tests bit 1 of _216 with ldrh / and / ccmp (ours narrows it to ldrb / tbz; same as
// SiteBossIceSplinterRoot)
// Damage handling: bursts (_39) on damage type 34 or a hit by an ice breaker / ancient weapon / another water
// bullet; otherwise a non-burst hit emits "ArrowHit" and requests the damage child (_3b).
void RemainsWaterChaseBulletRoot::sub_710054A100() {
    auto* mgr = sub_710072BA90(mActor);
    if (!mgr)
        return;

    const s32 field54 = mgr->getField54();
    const s32 field50 = mgr->getField50();
    const s32 damage = mgr->_7c;
    if (field54 == 34)
        _39 = true;
    if (field50 != 6 && !mgr->_216.isOn(2))
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(mgr->getAttacker(), &accessor)) {
        if (accessor.hasTag(ksys::act::tags::CanBreakIceMakerBlock))
            _39 = true;
        if (accessor.hasTag(ksys::act::tags::AncientWeapon))
            _39 = true;
        if (accessor.hasTag(ksys::act::tags::IsRemainsWaterBullet)) {
            if (!accessor.sub_7100D10FB8())
                sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004), nullptr);
            _39 = true;
        }
    }

    if (damage >= 1 && !_39) {
        if (mgr->getField50() == 0 || mgr->getField50() == 2 || mgr->getField50() == 1 ||
            mgr->getField50() == 3) {
            xlinkSearchAndEmit(mActor, "ArrowHit", 0, nullptr);
            _3b = true;
        }
    }
}

// NON_MATCHING: register allocation of the result flag and the tag hashes
// 0x710054a2cc (placeholder name): true when touching a body without an actor or another water bullet. Bursts (_39) when the bullet touches another water bullet (which is told to
// burst too unless it already is) or an ice maker block (which is told as well)
bool RemainsWaterChaseBulletRoot::sub_710054A2CC() {
    auto* body = mActor->getMainBody();
    if (!body || !body->isAddedToWorld())
        return false;

    bool hit = false;
    auto* info = body->getCollisionInfo();
    if (info && info->getCollidingBodies().size() != 0) {
        auto* bodies = info->getCollidingBodies().front();
        info->lock();
        for (; bodies; bodies = info->getCollidingBodies().next(bodies)) {
            auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(bodies->bodies[1]->getUserTag());
            if (!tag) {
                hit = true;
                continue;
            }
            ksys::act::ActorLinkConstDataAccess accessor;
            tag->acquireActor(&accessor);
            if (accessor.hasTag(ksys::act::tags::IsRemainsWaterBullet)) {
                if (!accessor.sub_7100D10FB8())
                    sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004), nullptr);
                hit = true;
                _39 = true;
            }
            if (accessor.hasTag(ksys::act::tags::IsIceMakerBlock)) {
                _39 = true;
                sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004), nullptr);
            }
        }
        info->unlock();
    }

    auto* points = body->getContactPointInfo();
    if (points && points->getNumContactPoints() != 0 && !points->begin().isEnd()) {
        auto it = points->begin();
        const auto end = points->end();
        for (; it != end; ++it) {
            auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>((*it)->body_b->getUserTag());
            if (!tag) {
                hit = true;
                continue;
            }
            ksys::act::ActorLinkConstDataAccess accessor;
            tag->acquireActor(&accessor);
            if (accessor.hasTag(ksys::act::tags::IsRemainsWaterBullet)) {
                if (!accessor.sub_7100D10FB8())
                    sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004), nullptr);
                hit = true;
                _39 = true;
            }
            if (accessor.hasTag(ksys::act::tags::IsIceMakerBlock)) {
                _39 = true;
                sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004), nullptr);
            }
        }
    }
    return hit;
}

// NON_MATCHING: the original sets the result after the accessor destructor in a shared block; epilogue layout
// Whether the bullet touches ground that is not part of the RemainsWater actor.
bool RemainsWaterChaseBulletRoot::sub_710054A6C0() {
    auto* body = mActor->getMainBody();
    if (!body || !body->isAddedToWorld())
        return false;

    bool hit = false;
    auto* info = body->getCollisionInfo();
    if (info && info->getCollidingBodies().size() != 0) {
        auto* bodies = info->getCollidingBodies().front();
        info->lock();
        for (; bodies; bodies = info->getCollidingBodies().next(bodies)) {
            auto* other = bodies->bodies[1];
            if (!other || other->getContactLayer() != ksys::phys::ContactLayer::EntityGround)
                continue;
            bool is_remains_water = false;
            if (auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(other->getUserTag())) {
                ksys::act::ActorLinkConstDataAccess accessor;
                tag->acquireActor(&accessor);
                is_remains_water = accessor.getName() == "RemainsWater";
            }
            if (!is_remains_water)
                hit = true;
        }
        info->unlock();
    }
    return hit;
}

// Shoots the bullet away from its owner (horizontally, ShootAddSpd per frame) and returns to the normal child.
void RemainsWaterChaseBulletRoot::sub_710054A930() {
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor)) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&bullet->_bd0._0, &accessor)) {
            const sead::Vector3f owner_pos = accessor.getActorMtx().getTranslation();
            const sead::Vector3f pos = bullet->getMtx().getTranslation();
            const f32 dx = pos.x - owner_pos.x;
            const f32 dz = pos.z - owner_pos.z;
            if (sead::Mathf::sqrt(dx * dx + dz * dz) > 0.0f) {
                sead::Vector3f dir{dx, 0.0f, dz};
                dir.normalize();
                const sead::Vector3f velocity = dir * (*mParams.mShootAddSpd_s * 30.0f);
                if (auto* body = mActor->getMainBody())
                    body->setLinearVelocity(velocity);
            }
        }
    }
    changeChild("通常");
}

void RemainsWaterChaseBulletRoot::leave_() {
    sub_710054AAD8();
}

bool RemainsWaterChaseBulletRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x80000b6) {
        mActor->sub_71011D0204(0x80);
        return true;
    }
    if (message->getType() == 0x80000b7) {
        mActor->sub_71011D0228(0x80);
        return true;
    }
    if (message->getType() == 0x8000004) {
        _39 = true;
        return true;
    }
    if (message->getType() == 0x800006b) {
        _3a = true;
        return true;
    }
    if (message->getType() == 0x3000003) {
        if (auto* body = mActor->getMainBody())
            body->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    } else if (message->getType() == 0x3000004) {
        if (auto* body = mActor->getMainBody())
            body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    }
    return false;
}

void RemainsWaterChaseBulletRoot::loadParams_() {
    getStaticParam(&mParams.mAtkMinDamage_s, "AtkMinDamage");
    getStaticParam(&mParams.mCheckPower_s, "CheckPower");
    getStaticParam(&mParams.mHighDamageAddSpd_s, "HighDamageAddSpd");
    getStaticParam(&mParams.mLowDamageAddSpd_s, "LowDamageAddSpd");
    getStaticParam(&mParams.mShootAddSpd_s, "ShootAddSpd");
    getStaticParam(&mParams.mResetASName_s, "ResetASName");
}

void RemainsWaterChaseBulletRoot::sub_710054AC5C() {
    auto* actor = mActor;
    sub_71007A2C30(actor, "BulletAtk", nullptr);
    sub_71007A34B8(actor, "BulletTgt");
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName(*sub_71007A2548())) {
            if (auto* body = set->findBodyByHavokName("PlayerSensor"))
                body->addToWorld();
        }
    }
}

void RemainsWaterChaseBulletRoot::sub_710054AAD8() {
    auto* actor = mActor;
    sub_71007A2D7C(actor, "BulletAtk");
    sub_71007A3634(actor, "BulletTgt");
    if (auto* physics = mActor->getPhysics()) {
        if (auto* set = physics->findBodyByName(*sub_71007A2548())) {
            if (auto* body = set->findBodyByHavokName("PlayerSensor"))
                body->removeFromWorld();
        }
    }
}

// 0x7100549e90
void RemainsWaterChaseBulletRoot::sub_7100549E90() {
    if (auto* as_list = mActor->getASList()) {
        if (!mParams.mResetASName_s.isEmpty())
            as_list->startAnimationMaybe(-1.0f, -1.0f, mParams.mResetASName_s.cstr(), 0, 0, true);
    }
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_10000);
    sub_710054AAD8();
    _3c = true;
    _40 = mActor->getMtx().getTranslation();
    changeChild("爆発", nullptr);
}

}  // namespace uking::ai
