#include "Game/Actor/actSwarm.h"
#include <basis/seadNew.h>
#include <math/seadMatrixCalcCommon.h>
#include "Game/gameStasisMgr.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actDebug.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::act {

bool Swarm::sub_71002D47D8(s32 idx) const {
    const auto& body = _14f8[idx];
    if (!body._18)
        return false;
    if (auto* info = body._18->getCollisionInfo())
        return info->getCollidingBodies().size() != 0;
    return false;
}

bool Swarm::BodyInfo::sub_71002D56B4(Actor* actor, sead::Heap* heap,
                                      ksys::phys::InstanceSet* instance,
                                      ksys::phys::RigidBodyFromShape* shape) {
    _20 = actor;
    _18 = sead::DynamicCast<ksys::phys::SphereRigidBody>(instance->sub_7100FC0580(shape, heap));
    if (!_18)
        return false;
    _18->setSystemGroupHandler(instance->get188(int(_18->getLayerType())));
    _18->setContactAll();
    _18->setFlag1000000();
    _28 = ksys::phys::CollisionInfo::make(heap, actor->getName());
    _18->setCollisionInfo(_28);
    if (auto* info = _18->getCollisionInfo()) {
        info->disableLayer(ksys::phys::ContactLayer::EntityPlayer);
        info->disableLayer(ksys::phys::ContactLayer::EntityNPC);
        info->disableLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
        info->disableLayer(ksys::phys::ContactLayer::EntityRope);
        info->enableLayer(ksys::phys::ContactLayer::EntityObject);
        info->enableLayer(ksys::phys::ContactLayer::EntityGround);
        info->enableLayer(ksys::phys::ContactLayer::EntityWater);
        info->enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
        info->enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
        info->enableLayer(ksys::phys::ContactLayer::EntityTree);
    }
    return true;
}

bool Swarm::BodyInfo::sub_71002D481C() const {
    if (!_18)
        return false;
    if (auto* info = _18->getCollisionInfo())
        return info->getCollidingBodies().size() != 0;
    return false;
}

f32 Swarm::BodyInfo::sub_71002D5F30() const {
    if (_18)
        return _18->getRadius();
    return 0.0f;
}

void Swarm::BodyInfo::sub_71002D5F44(const sead::Vector3f& position) {
    _c = position;
    _0 = position;
    if (!_18)
        return;
    if (!_18->getCollisionInfo())
        _18->setCollisionInfo(_28);
    _18->addToWorld();
    sead::Vector3f world_position;
    world_position.setMul(_20->getMtx(), position);
    _18->setPosition(world_position, ksys::phys::PropagateToLinkedMotions{true});
}

void Swarm::BodyInfo::sub_71002D71C8(bool paused) {
    if (paused) {
        if (_18) {
            _18->setLinearVelocity(sead::Vector3f::zero);
            _18->setAngularVelocity(sead::Vector3f::zero);
        }
    } else if (_18) {
        sead::Vector3f world_position;
        world_position.setMul(_20->getMtx(), _c);
        _18->changePosition(world_position, ksys::phys::KeepAngularVelocity{false});
    }
}

void Swarm::Unit::sub_71002DAA58(f32 opacity) {
    if (_78)
        Unk_710260af28::instance()->sub_7100F1DCA8(_78, opacity, false);
}

// NON_MATCHING: the per-unit opacity helper is inlined into this loop.
void Swarm::m61(f32 rate) {
    for (s32 i = 0; i < _14c8.size(); ++i) {
        if (auto* unit = _14c8[i])
            unit->sub_71002DAA58(rate);
    }
}


Swarm::Swarm(const CreateArg& arg) : Enemy(arg) {}

Unk_71025ae680* Swarm::m178(sead::Heap* heap) {
    return new (heap) Unk_710244ff68(this);
}

// NON_MATCHING: bool conversion: the original returns the count unconverted (s32 return does not
// compile as an override of Actor's bool m39())
bool Swarm::m39() {
    return _14c8.getSize();
}

void Swarm::m74() {
    sub_710011CCBD0();
    if ((mActorFlags2.getDirect() & 0x21) != 0)
        return;
    auto* debug = ksys::act::ActorDebug::instance();
    if (debug && (debug->mFlags.getDirect() & 0x4000) != 0)
        return;
    for (s32 i = 0; i < _14c8.size(); ++i) {
        Unit* unit = _14c8[i];
        if ((unit->_b8 & 3) == 0 && unit->_78)
            unit->_78->requestDraw();
    }
}

void Swarm::m114(bool update, bool) {
    if (auto* list = _14d8) {
        list->sub_710115C634(isSpecialJobTypesMaskOverride0());
        list->sub_710115C6F0();
        list->sub_710115C7A8(false);
        list->sub_710115C8D8(update, false);
    }
    if (auto* list = _14e0) {
        list->sub_710115C634(isSpecialJobTypesMaskOverride0());
        list->sub_710115C6F0();
        list->sub_710115C7A8(false);
        list->sub_710115C8D8(update, false);
    }
    if (auto* list = _14e8) {
        list->sub_710115C634(isSpecialJobTypesMaskOverride0());
        list->sub_710115C6F0();
        list->sub_710115C7A8(false);
        list->sub_710115C8D8(update, false);
    }
    if (auto* list = _14f0) {
        list->sub_710115C634(isSpecialJobTypesMaskOverride0());
        list->sub_710115C6F0();
        list->sub_710115C7A8(false);
        list->sub_710115C8D8(update, false);
    }
}

void Swarm::m63() {
    Enemy::m63();
    if (_14d8)
        _14d8->sub_710115A9C0();
    if (_14e0)
        _14e0->sub_710115A9C0();
    if (_14e8)
        _14e8->sub_710115A9C0();
    if (_14f0)
        _14f0->sub_710115A9C0();
    // NON_MATCHING: loop entry only: the original tests size <= 0 (cmp w8,#0; b.le); every natural
    // loop form (for/while/do-while, <=, hoisted bound, s64/u32 index) compiles to cmp w8,#1; b.lt
    // (probed with the project toolchain)
    for (s32 i = 0; i < _14c8.size(); ++i) {
        Unit* unit = _14c8[i];
        if (unit && unit->_78)
            unit->_78->x(true, 0);
    }
}

void* Swarm::m40(s32 idx) {
    Unit* unit = _14c8[idx];
    if (!unit)
        return nullptr;
    return unit->_78;
}

bool Swarm::startPreparingForPreDelete_() {
    bool ready = true;
    for (s32 i = 0; i < _14c8.size(); ++i) {
        if (auto* unit = _14c8[i])
            ready &= unit->m9();
    }
    if (!ready)
        return false;
    return Enemy::startPreparingForPreDelete_();
}

// NON_MATCHING: member types incomplete
Swarm::~Swarm() = default;

// NON_MATCHING: store schedule only: the original stores the units buffer pointer (_14d0) first, we merge it into
// the zeroing of _14d8 .. _14f0
ksys::act::BaseProc* Swarm::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Swarm(arg);
}

void Swarm::m68() {
    if (_14d8)
        _14d8->sub_710115CA28();
    if (_14e0)
        _14e0->sub_710115CA28();
    if (_14e8)
        _14e8->sub_710115CA28();
    if (_14f0)
        _14f0->sub_710115CA28();
    Actor::m68();
}

void Swarm::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    Enemy::m76(setter);
    if (mActorFlags2.isOn(ActorFlag2::_1) || mActorFlags2.isOn(ActorFlag2::_40) ||
        !mSpecialJobTypesMaskOverride.isOnBit(0))
        return;
    if (_14d8)
        _14d8->sub_710115C53C();
    if (_14e0)
        _14e0->sub_710115C53C();
    if (_14e8)
        _14e8->sub_710115C53C();
    if (_14f0)
        _14f0->sub_710115C53C();
}

void Swarm::setMtx(const sead::Matrix34f& mtx, bool a2, bool a3) {
    Actor::setMtx(mtx, a2, a3);
    sead::Matrix34CalcCommon<f32>::inverse(_15b8, mMtx);
}

bool Swarm::m81(const ksys::Message& message) {
    if (message.getType() == ksys::MessageType(0x3000003)) {
        Enemy::m81(message);
        _1614 = true;
        if (auto* sender = ksys::act::ActorSystem::instance()->getStasisMessageSender())
            sender->sendMessage(this, ksys::MessageType(0x3000004), true);
        return true;
    }

    const ksys::MessageType type = message.getType();
    const bool handled = Enemy::m81(message);
    if (type == ksys::MessageType(0x3000004)) {
        clearFlag(ActorFlag::_9);
        return true;
    }
    return handled;
}

void Swarm::sub_71002D47D4(const sead::SafeString& name) {}

void Swarm::sub_71002D484C(Unit* unit) {
    if (!unit || unit->_b0 != this || unit->_b8 & 1)
        return;
    --_1610;
    unit->_b8 |= 1;
}

}  // namespace uking::act
