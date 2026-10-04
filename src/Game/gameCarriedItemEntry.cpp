#include "Game/gameActorContextStuff.h"
#include "Game/gameSceneSubsys12.h"

#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"
#include "KingSystem/System/VFR.h"

// NON_MATCHING: scalar initializer stores are scheduled/coalesced differently.
Unk_710243be90::Unk_710243be90() : _98() {}

// NON_MATCHING: scalar scale operations and matrix temporaries are scheduled differently.
void Unk_710243be90::sub_7100661A58(ksys::act::Actor* actor) {
    auto* scene = GameSceneSubsys12::instance();
    if (!scene || !_118)
        return;

    if (!(_28 & 0x40) && _118->sub_710065E834()) {
        _28 |= 0x40;
        if (_28 & 8)
            xlinkSearchAndEmit(actor, "Cooking", 2, &_98);
    } else if ((_28 & 0x40) && !_118->sub_710065E834()) {
        _28 &= ~0x40;
        if (_98.sub_7101241B6C())
            _98.fadeXLink();
    }

    if (_118->_68 & 1) {
        f32 scale = actor->getScale().x;
        sead::Mathf::chase(&scale, _94, ksys::VFR::instance()->getDeltaFrame() * 0.05f);
        if (actor->getScale().x != scale)
            actor->setScale({scale, scale, scale});
    } else if (!(_28 & 4)) {
        const f32 scale = _118->sub_710065F1F0(_b8 * _c0) * _b8;
        if (actor->getScale().x != scale) {
            actor->setScale({scale, scale, scale});
            _c4 = scale;
        }
    }

    if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_200)) {
        if (scene->sub_7100664F30()) {
            const f32 opacity = scene->sub_7100664ACC(actor);
            if (_bc != opacity) {
                Unk_710260af28::instance()->sub_7100F1E8A4(actor->getModel(), opacity);
                _bc = opacity;
            }
        } else if ((_50->getNumContactPoints().load() && !_50->begin().isEnd()) ||
                   ((_28 & 0x200) && (_118->_68 & 1) && !scene->_a78.isBitOn(3))) {
            actor->setScale(sead::Vector3f::ones * _94);
            scene->sub_7100664A64(&_30, false);
            _118->sub_710065F544(actor);
            sub_7100661058(actor);
            if (!(_28 & 1)) {
                _48->removeFromWorld();
                _40->erase();
                _28 |= 1;
            }
        }
    }

    if (!(_118->_68 & 1)) {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        sead::Matrix34f matrix;
        matrix = player.getActorMtx();
        sead::Vector3f position = sead::Vector3f::zero;
        if (_48)
            _48->getPosition(&position);
        matrix.m[1][3] = position.y;
        if (auto* controller = actor->getCharacterController())
            controller->sub_7100F60500(matrix);
        else if (_58)
            _58->setTransform(matrix);
    } else {
        const s32 delay = scene->sub_710066551C();
        _120 += 1.0f;
        if (f32(delay) < _120) {
            if (_58)
                _58->setContactLayer(ksys::phys::ContactLayer::EntitySmallObject);
            if (_48)
                _48->setContactLayer(ksys::phys::ContactLayer::EntitySmallObject);
        }
    }
}

Unk_710243be90::~Unk_710243be90() {
    if (_50) {
        if (_48)
            _48->setContactPointInfo(nullptr);
        ksys::phys::ContactPointInfo::free(_50);
        _50 = nullptr;
    }
    if (_40) {
        delete _40;
        _40 = nullptr;
    }
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
}

// NON_MATCHING: sphere parameter initializer stores and the final flags update are scheduled differently.
void Unk_710243be90::sub_710066074C(ActorContextStuff* context, s32 index, bool for_menu,
                                  ksys::phys::SystemGroupHandler* handler, sead::Heap* heap) {
    _118 = context;
    ksys::phys::SphereParam param;
    param.name = for_menu ? "InCarryBoxForMenu" : "InCarryBoxForGame";
    param.center_of_mass.set(0.0f, 0.0f, 0.0f);
    param.linear_damping = 1.0f;
    param.angular_damping = 1.0f;
    param.toi = false;
    param.contact_layer = ksys::phys::ContactLayer::EntitySmallObject;
    param.mass = 10.0f;
    param.inertia.set(0.4f, 0.4f, 0.4f);
    param.translate.set(0.0f, 0.0f, 0.0f);
    param.radius = 0.1f;
    param.common.material = ksys::phys::Material::Grass;
    param.common.floor_code = ksys::phys::FloorCode::None;
    param.common.wall_code = ksys::phys::WallCode::None;
    param.no_hit_ground = true;
    param.no_hit_water = true;
    param.system_group_handler = handler;
    _68 = index;
    _48 = ksys::phys::SphereRigidBody::make(&param, heap);
    _40 = new (heap, 8) sead::TListNode<ksys::phys::RigidBody*>(_48);
    _50 = ksys::phys::ContactPointInfo::make(heap, 1, "CarryBoxItem", 1, 0, 0);
    _48->setContactPointInfo(_50);
    if (for_menu)
        _28 |= 2;
    else
        _28 &= ~2;
}

void Unk_710243be90::sub_7100661988() {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_30, &accessor) && accessor.isStateCalc())
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void Unk_710243be90::sub_71006619DC() {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_30, &accessor) && accessor.isStateSleep())
        accessor.setProperties(0, accessor.getActorMtx(), nullptr, nullptr, nullptr, false, 3, -1);
}

void Unk_710243be90::sub_71006618AC() {
    _48->setGravityFactor(0.0f);
    _48->setContactAll();
    _48->removeFromWorld();
    _48->setLinearVelocity(sead::Vector3f::zero);
    _48->setAngularVelocity(sead::Vector3f::zero);
    _70 = sead::GlobalRandom::instance()->getF32Range(10.0f, 30.0f);
    _74 = sead::GlobalRandom::instance()->getF32Range(50.0f, 70.0f);
}

bool Unk_710243be90::sub_7100661538(ksys::act::BaseProc* proc) const {
    return _30.hasProcById(proc);
}

bool Unk_710243be90::sub_71006606E8() {
    _40->erase();
    return _48 && _48->removeFromWorldAndResetLinks() && !_30.hasProc();
}

void Unk_710243be90::sub_710066136C() {
    _48->setGravityFactor(0.0f);
    _48->setContactAll();
    _48->removeFromWorld();
    _28 |= 4;
}

void Unk_710243be90::sub_71006613B0(bool delete_actor) {
    if (_28 & 1)
        return;
    _48->removeFromWorld();
    _40->erase();
    if (delete_actor) {
        _28 |= 0x80;
        _48->removeFromWorld();
        _40->erase();
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_30, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        _28 |= 0x81;
    }
    _28 |= 1;
}

void Unk_710243be90::sub_7100661494(bool immediately) {
    _48->removeFromWorld();
    _40->erase();
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_30, &accessor)) {
        if (immediately)
            accessor.deleteEx(ksys::act::BaseProc::DeleteReason::_0);
        else
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    _28 |= 0x81;
}

bool Unk_710243be90::sub_7100661540(const ksys::act::BaseProcLink& link) const {
    return _30 == link;
}

bool Unk_710243be90::sub_7100661548(ksys::act::BaseProc* proc) {
    ksys::act::ActorConstDataAccess accessor;
    return ksys::act::acquireActor(&_30, &accessor) && accessor.getName() == proc->getName();
}

bool Unk_710243be90::sub_7100661650(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::ActorConstDataAccess other;
    return ksys::act::acquireActor(&_30, &accessor) && ksys::act::acquireActor(link, &other) &&
           accessor.getName() == other.getName();
}

bool Unk_710243be90::sub_710066178C(sead::BufferedSafeString* out) {
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&_30, &accessor))
        return false;
    out->copy(accessor.getName());
    return true;
}

void Unk_710243be90::sub_71006620CC(sead::Vector3f* position, sead::Quatf* rotation) const {
    if ((_118->_68 & 1) && _58)
        _58->getPositionAndRotation(position, rotation);
    else if (_48)
        _48->getPositionAndRotation(position, rotation);
}

void Unk_710243be90::sub_71006620F8(sead::Matrix34f* matrix) const {
    if ((_118->_68 & 1) && _58)
        _58->getTransform(matrix);
    else if (_48)
        _48->getTransform(matrix);
}
