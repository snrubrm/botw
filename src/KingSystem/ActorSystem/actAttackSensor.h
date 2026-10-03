#pragma once

#include <basis/seadTypes.h>
#include <container/seadTList.h>
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class Actor;
struct Struct8Base;

// Placeholder name: abstract base of the objects kept in AttackSensor2::_20 (an object with a vtable
// with one virtual and the TListNode base at +8 whose data points back to the object; SetThroughArrow and
// SetThroughCloseWeapon embed one each and register it with ActorAtk::sub_710079E344). The virtual
// takes seven arguments of which the known implementations only look at the last one (the flags at
// +0x18 of the attack info: bit 3 for arrows, bits 0-2 for close weapons).
class AttackSensor2Listener : public sead::TListNode<AttackSensor2Listener*> {
public:
    AttackSensor2Listener() : TListNode(this) {}

    virtual bool m0(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6,
                    const Struct8Base* info) = 0;
};
KSYS_CHECK_SIZE_NX150(AttackSensor2Listener, 0x28);

// CSV name (act::AttackSensor): the user tag of an actor's attack sensor bodies (ActorAtk::_40,
// getActorAttackSensor). ctor 0x710079f2dc (ActorAtk TU), vtable 0x7102459f68 (overrides the RTTI
// functions and D0 only; D1 is PhysicsUserTag's), RTTI static 0x71025ca8f0, size 0x50.
// TODO: field meanings unknown; activateAttackSensor stores its arguments in _18 - _48.
class AttackSensor : public PhysicsUserTag {
    SEAD_RTTI_OVERRIDE(AttackSensor, PhysicsUserTag)
public:
    explicit AttackSensor(Actor* actor);

    // 0x710079f338 (CSV name, ~60 callers).
    void activateAttackSensor(u32 a1, u32 a2, u32 a3, u32 a4, f32 a5, u32 a6, u32 a7, u32 a8,
                              bool a11, u32 a9, u32 a10);

    /* 0x18 */ u32 _18 = 0;
    /* 0x1c */ u32 _1c = 0;
    /* 0x20 */ s32 _20 = -1;
    /* 0x24 */ u32 _24 = 0;
    /* 0x28 */ u32 _28 = 0;
    /* 0x2c */ f32 _2c = 0;
    /* 0x30 */ u32 _30 = 0;
    /* 0x34 */ u32 _34 = 1;
    /* 0x38 */ s32 _38 = -1;
    /* 0x3c */ u32 _3c = 1;
    /* 0x40 */ s32 _40 = -1;
    /* 0x44 */ s32 _44 = 0;  // incremented by sub_71007A2B64 (each activation)
    /* 0x48 */ bool _48 = false;
    /* 0x49 */ bool _49 = false;
    /* 0x4a */ bool _4a = false;
};
KSYS_CHECK_SIZE_NX150(AttackSensor, 0x50);

// CSV name (act::AttackSensor2): user tag of the actor's "Tgt" bodies (ActorAtk::_70). ctor
// 0x71007a21d4 (first function of the actActorSensorUtil TU), vtable 0x710245a050, size 0x40.
class AttackSensor2 : public PhysicsUserTag {
    SEAD_RTTI_OVERRIDE(AttackSensor2, PhysicsUserTag)
public:
    explicit AttackSensor2(Actor* actor);
    ~AttackSensor2() override;

    /* 0x18 */ u32 _18 = 0x1f01f;  // flags; 0x800 if the actor has a Chemical
    /* 0x1c */ u16 _1c = 0xffff;
    /* 0x20 */ sead::TList<AttackSensor2Listener*> _20;
    /* 0x38 */ bool _38 = false;
};
KSYS_CHECK_SIZE_NX150(AttackSensor2, 0x40);

}  // namespace ksys::act
