#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::phys {
class SphereRigidBody;
}

namespace ksys::act {

class Actor;
class Unk_71024dca28;

// CSV name act::DummyUserTag (RTTI functions 0x7100062054 / 0x7100062120, vtable 0x710235f098,
// RTTI static 0x71025afa18). The user tag of an AITerror's sensor body; carries the awareness
// entry the AI sees. Its dtor (0x7100062194) is inline (emitted in the users' TUs).
class DummyUserTag : public phys::UserTag {
    SEAD_RTTI_OVERRIDE(DummyUserTag, phys::UserTag)
public:
    explicit DummyUserTag(Actor* actor) : _8(actor), _18(actor) {}

    /* 0x08 */ Actor* _8;
    /* 0x10 */ sead::BitFlag8 _10;  // bit mask of the entry indices set by AITerror::x
    /* 0x18 */ Unk_71024dc858 _18;
};
KSYS_CHECK_SIZE_NX150(DummyUserTag, 0x70);

// CSV name AITerror (methods x / setRadius; the namespace is a guess: its TU 0x7100d78564- sits
// inside the awareness code). vtable 0x710235f078 = {D1 0x71000602d4, D0 0x7100062008}: the ctor
// and dtor are inline (users: HornUse, MotorcycleRiddenByPlayer, AnimalFollow,
// LumberjackFallenTree, BehaviorNoise, Behavior SpeedTerror / TerrorBehavior, Player).
// A sensor sphere (contact layer SensorTerror) whose user tag exposes an awareness entry; while
// active it is linked into the AITerror list of an Unk_71024dca28 (Actor::_548).
class AITerror {
public:
    explicit AITerror(Actor* actor) : _10(actor) {}
    virtual ~AITerror() { sub_7100D786EC(); }

    // 0x7100d78564: creates the sensor body ("ExtendEmitterSensor") with the actor's physics.
    bool sub_7100D78564(sead::Heap* heap);
    // 0x7100d786d8
    bool sub_7100D786D8();
    // 0x7100d786ec: unregisters from the owner and destroys the body.
    void sub_7100D786EC();
    // 0x7100d78740: sets entry value `idx` and adds `flags` to the entry flags (_3c for idx 2,
    // else the u16 _38).
    void x(const int& idx, u32 flags, f32 value);
    // 0x7100d787bc
    void setRadius(f32 radius);
    // 0x7100d78800
    f32 sub_7100D78800() const;
    // 0x7100d78814: adds the body to the world (at the actor's matrix, offset by _88 / _94 if
    // _b0) and links this after `prev` in `owner`'s list.
    bool sub_7100D78814(Unk_71024dca28* owner, AITerror* prev);
    // 0x7100d78960
    bool sub_7100D78960() const;
    // 0x7100d78970: unlinks from the owner's list and removes the body from the world.
    void sub_7100D78970();

    /* 0x08 */ phys::SphereRigidBody* _8 = nullptr;
    /* 0x10 */ DummyUserTag _10;
    /* 0x80 */ Unk_71024dca28* _80 = nullptr;
    /* 0x88 */ sead::Vector3f _88 = sead::Vector3f::zero;  // offset rotated by the actor matrix
    /* 0x94 */ sead::Vector3f _94 = sead::Vector3f::zero;  // offset added in world space
    /* 0xa0 */ AITerror* _a0 = nullptr;
    /* 0xa8 */ AITerror* _a8 = nullptr;
    /* 0xb0 */ sead::BitFlag8 _b0;  // bit 0: offset the body by _88 / _94
};
KSYS_CHECK_SIZE_NX150(AITerror, 0xb8);

}  // namespace ksys::act
