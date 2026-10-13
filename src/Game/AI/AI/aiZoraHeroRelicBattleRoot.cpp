#include "Game/AI/AI/aiZoraHeroRelicBattleRoot.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

ZoraHeroRelicBattleRoot::ZoraHeroRelicBattleRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ZoraHeroRelicBattleRoot::~ZoraHeroRelicBattleRoot() = default;

bool ZoraHeroRelicBattleRoot::init_(sead::Heap* heap) {
    _48._8.sub_7100743814(mActor);
    return true;
}

void ZoraHeroRelicBattleRoot::enter_(ksys::act::ai::InlineParamPack*) {
    _40 = false;
    _42 = ksys::gdt::getFlag_Water_Relic_BreakWeakPoint1();
    _43 = ksys::gdt::getFlag_Water_Relic_BreakWeakPoint2();
    _44 = ksys::gdt::getFlag_Water_Relic_BreakWeakPoint3();
    _45 = ksys::gdt::getFlag_Water_Relic_BreakWeakPoint4();
    if (auto** unit = static_cast<Unk_71025afb58**>(mZoraHeroShowMsgUnit_a)) {
        if (!*unit)
            *unit = &_48;
    }
    _48._8._13c = _42 + _43 + _44 + _45;
    auto* actor = mActor;
    if (auto* awareness = actor->getAwareness())
        awareness->enable();
    _41 = false;
    if (actor->getConnectedCalcChild())
        sub_7100614738();
    else
        sub_7100614930();
}

void ZoraHeroRelicBattleRoot::calc_() {
    sub_7100614C18();
    if (!mActor->get1a0() &&
        (!mActor->getMapObject() ||
         !mActor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
        _48._8.sub_7100743A40();
    }
    auto* actor = mActor;
    bool ride = false;
    if (isCurrentChild("騎乗待ち")) {
        auto* child = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcChild());
        if (_41 && child) {
            _41 = false;
            ride = true;
        } else if (child && ksys::act::isPlayerProfile(child)) {
            ride = true;
        }
    } else {
        isCurrentChild("騎乗中");
    }
    if (ride) {
        sub_7100614738();
        return;
    }
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        sub_7100614930();
    else
        child->isChangeable();
}

void ZoraHeroRelicBattleRoot::sub_7100614C18() {
    ksys::act::acc::PlayerBase player;
    if (player.getPlayerFromPlayerInfo()) {
        if (player.x_25()) {
            _40 = false;
            return;
        }
        if (player.x_12()) {
            if (!_40)
                _48._8.sub_7100744200(2, false);
            _40 = true;
        } else {
            _40 = false;
        }
    }
    if (!_42 && ksys::gdt::getFlag_Water_Relic_BreakWeakPoint1()) {
        _42 = true;
        _48._8.sub_7100744200(5, true);
    }
    if (!_43 && ksys::gdt::getFlag_Water_Relic_BreakWeakPoint2()) {
        _43 = true;
        _48._8.sub_7100744200(5, true);
    }
    if (!_44 && ksys::gdt::getFlag_Water_Relic_BreakWeakPoint3()) {
        _44 = true;
        _48._8.sub_7100744200(5, true);
    }
    if (!_45 && ksys::gdt::getFlag_Water_Relic_BreakWeakPoint4()) {
        _45 = true;
        _48._8.sub_7100744200(5, true);
    }
    _48._8._13c = _42 + _43 + _44 + _45;
    _48._8._140 = ksys::gdt::getFlag_Water_Relic_ChanceTime();
    _48._8._141 = mActor->getConnectedCalcChild() != nullptr;
}

void ZoraHeroRelicBattleRoot::sub_7100614738() {
    auto* actor = mActor;
    ksys::act::disableAllAttClients(actor);
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "Body")) {
        body->enableContactLayer(ksys::phys::ContactLayer::SensorAttackEnemy);
        body->enableContactLayer(ksys::phys::ContactLayer::SensorAttackPlayer);
        body->enableContactLayer(ksys::phys::ContactLayer::SensorAttackCommon);
    }
    if (auto* child = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcChild()))
        sub_7100738D28(actor, child);
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    actor->emitBasicSigOn();
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "HeadSensor"))
        body->addToWorld();
    ksys::gdt::setFlag_Water_Relic_firstPrinceRide(true);
    if (auto* set = mActor->getRigidBodyByName(sub_71007A24D0()->cstr())) {
        auto* body = set->findBodyByHavokName("Body");
        if (!body && set->getRigidBodies().size() > 0)
            body = set->getRigidBody(0);
        if (body)
            body->setFlag200();
    }
    changeChild("騎乗中", nullptr);
}

void ZoraHeroRelicBattleRoot::sub_7100614930() {
    auto* actor = mActor;
    ksys::act::enableAllAttClients(actor);
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "Body"))
        body->setContactNone();
    sub_7100738DDC(actor);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F60604();
    actor->emitBasicSigOff();
    if (auto* set = mActor->getRigidBodyByName(sub_71007A24D0()->cstr())) {
        auto* body = set->findBodyByHavokName("Body");
        if (!body && set->getRigidBodies().size() > 0)
            body = set->getRigidBody(0);
        if (body)
            body->resetFlag200();
    }
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "HeadSensor"))
        body->removeFromWorld();
    changeChild("騎乗待ち", nullptr);
}

void ZoraHeroRelicBattleRoot::leave_() {
    auto* actor = mActor;
    if (auto* awareness = actor->getAwareness())
        awareness->disable();

    auto** unit = static_cast<Unk_71025afb58**>(mZoraHeroShowMsgUnit_a);
    if (unit && *unit == &_48)
        *unit = nullptr;

    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "HeadSensor"))
        body->removeFromWorld();
}

bool ZoraHeroRelicBattleRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x180001a && isCurrentChild("騎乗待ち")) {
        _41 = true;
        _48._8.sub_7100744200(3, false);
        return true;
    }
    return false;
}

void ZoraHeroRelicBattleRoot::loadParams_() {
    getAITreeVariable(&mZoraHeroShowMsgUnit_a, "ZoraHeroShowMsgUnit");
}

}  // namespace uking::ai
