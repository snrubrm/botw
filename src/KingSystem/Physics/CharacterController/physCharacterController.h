#pragma once

#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class MotionType;
}

namespace ksys::phys {

class RigidBodyAccessor;

enum class Fixed : bool;
enum class PreserveVelocities : bool;

class CollisionInfo;
class ContactPointInfo;
class RigidBody;
class SystemGroupHandler;
class UserTag;

struct CharacterControllerUnk10;
struct CharacterControllerUnk20;
struct CharacterControllerShapes;
struct CharacterControllerUnk38;
struct CharacterControllerUnk40;
struct CharacterControllerUnk48 {
    // 0x7100f68f38 (declaration only): the address of the field at 0x5c.
    f32* sub_7100F68F38();

    /* 0x00 */ u8 _0[0x50];
    /* 0x50 */ u8 _50;
    /* 0x51 */ u8 _51[0x8c - 0x51];
    /* 0x8c */ u32 _8c;
    /* 0x90 */ u8 _90[0x94 - 0x90];
    /* 0x94 */ u32 _94;
};

struct CharacterControllerUnk50;

// TODO: incomplete (0x2a8 bytes; ctor 0x7100f5d8b8)
class CharacterController {
public:
    virtual ~CharacterController();

    void sub_7100F5EC30();
    void sub_7100F5EC44();
    void sub_7100F60604();
    // 0x7100f60ae0 (declared only): resets the controller's velocity / movement state (reads sead::Vector3f
    // statics and the Havok world gravity).
    void sub_7100F60AE0();
    void enableContactLayer(ContactLayer);
    void disableContactLayer(ContactLayer);
    void sub_7100F605F0();
    // 0x7100f63604: sets the collision info of every body of _288 (if _114 has 0x2000).
    void sub_7100F63604(CollisionInfo* info);
    // 0x7100f6367c: the collision info of the first body of _288 (null without 0x2000 / a body).
    CollisionInfo* sub_7100F6367C() const;
    // 0x7100f62bc0: setFixed on the main rigid body (unless it is already unfixed and `fixed` is false).
    void sub_7100F62BC0(bool fixed);

    act::MotionType sub_7100F5F0E4() const;
    // 0x7100f5f14c (declared only; lane1 s21; ~35 callers across lanes): a ground / contact test
    // (reads the controller's sub-objects at +0x10 / +0x20 / +0x28 / +0x40).
    bool sub_7100F5F14C() const;
    // 0x7100f5f264 (declared only; lane2 s20): reads byte 0x69 of the sub-object at +0x40.
    bool sub_7100F5F264() const;
    void sub_7100F5F458(act::MotionType type);
    // 0x7100f609e4 (unnamed in the CSV; declared only): setFixed on the main rigid body (and more).
    void sub_7100F609E4(Fixed fixed, PreserveVelocities preserve_velocities);
    // 0x7100f5f670 (unnamed in the CSV; declared only): applies the scheduled motion type change
    // (flags 0x3c0 of _114, calls sub_7100F5F458) and clears them.
    void sub_7100F5F670();
    // 0x7100f605c8: copies `value` to _ac / _bc / _cc.
    void sub_7100F605C8(const sead::Vector3f& value);

    bool sub_7100F636EC() const;
    void sub_7100F636B0(bool clear);
    // 0x7100f63700 (lane1 s21): clears (or sets) mFlags bit 0x40.
    void sub_7100F63700(bool clear);
    // 0x7100f63388 (not decompiled; AssassinBossRoot enter_/m42 pass (true / false, -1)).
    void sub_7100F63388(bool enable, s32 idx);
    bool sub_7100F63590() const;
    // 0x7100f6353c: the controller's velocity (the first three floats of the vector at _20 + 0x60).
    void sub_7100F6353C(sead::Vector3f* out) const;
    // 0x7100f635b4-0x7100f636a8: forwarders to the main rigid body.
    bool sub_7100F635B4() const;  // isAddingBodyToWorld
    void sub_7100F635BC(sead::Vector3f* velocity) const;  // getAngularVelocity
    void sub_7100F635D0(ContactPointInfo* info);  // setContactPointInfo
    ContactPointInfo* sub_7100F635D8() const;  // getContactPointInfo
    ContactPointInfo* sub_7100F635E4() const;  // getContactPointInfo (a second copy)
    void sub_7100F635F0(CollisionInfo* info);  // setCollisionInfo
    CollisionInfo* sub_7100F635F8() const;  // getCollisionInfo
    void sub_7100F636A8(f32 factor);  // setMagneMassScalingFactor
    void sub_7100F63554(bool clear);
    bool sub_7100F62D34() const;
    void sub_7100F62CA8(bool clear);

    void physicsXXXGetMtx_1(sead::Matrix34f* mtx) const;
    // 0x7100f635c4: the accessor of the controller's rigid body (declared only).
    RigidBodyAccessor* sub_7100F635C4() const;
    // 0x7100f626e8 (declared only): the transform of the active body combined with _a0.
    void sub_7100F626E8(sead::Matrix34f* mtx) const;
    // 0x7100f62ec0 (declared only): outputs the half height (?) of the controller's shape `index`; false
    // if it has none.
    bool sub_7100F62EC0(f32* out, int index) const;

    // set by sub_7100F5EEB8
    const sead::Vector3f& get64() const { return _64; }
    // lane3 s39 (FloatWait::calc_)
    const sead::Vector3f& get180() const { return _180; }
    u8 get18c() const { return _18c; }
    bool isBit4Of116() const { return _116 & 0x10; }
    const sead::Vector3f& get70() const { return _70; }
    const sead::Vector3f& get7c() const { return _7c; }
    f32 get110() const { return _110; }

    // lane4 s30: unnamed accessors (placeholder names; signatures from their bodies).
    f32 sub_7100F5EEE8() const;        // _130
    void sub_7100F5EEF0(f32 value);    // _134
    f32 sub_7100F5EEF8() const;        // _134
    f32 sub_7100F60390() const;        // _138
    f32 sub_7100F5EF88() const;        // the current shape's _14 (a second copy: 5EFB0), _18 (5EFD8 / 5F100), _1c (5F000)
    f32 sub_7100F5EFB0() const;
    f32 sub_7100F5EFD8() const;
    f32 sub_7100F5F000() const;
    f32 sub_7100F5F100() const;
    const sead::Vector3f& sub_7100F5F028() const;  // the current shape's _20
    f32 sub_7100F5F050() const;        // 0
    f32 sub_7100F5F058() const;        // 1
    u32 sub_7100F609D8() const;        // _40->_64
    f32 sub_7100F62F58() const;        // _218
    const sead::Vector3f& sub_7100F62B80() const;  // _120
    void sub_7100F62B88(const sead::Vector3f& value);
    void sub_7100F62BA4(f32 value);    // _50->_18
    void sub_7100F5E938(bool on);      // mFlags 0x8000
    // 0x7100f5e898: updates _114 bits 0x400 / 0x800 / 0x1000 from the current shape's _10 / _11 / _12.
    void sub_7100F5E898();
    // 0x7100f5e95c: multiplies _218 by the scale change and scales the main body (and _298).
    void sub_7100F5E95C(f32 scale);
    // 0x7100f5ecc4: removes every body of _288 and the main body from the world (false if one fails).
    bool sub_7100F5ECC4();
    // 0x7100f5ef30: sets the max linear velocity of the main body (and _10->_48) from `value`.
    void sub_7100F5EF30(f32 value);
    // 0x7100f60794: resetFrozenState() of the main body and _298.
    void sub_7100F60794();
    // 0x7100f60934 / 0x7100f62d3c: setEntityMotionFlag200 / 8 of the main body (and every body of _288 with 0x2000).
    void sub_7100F60934(bool on);
    void sub_7100F62D3C(bool on);
    // 0x7100f603f8: adds `delta` to _94 (and sets 0x20 of _114 when it is not zero).
    void sub_7100F603F8(const sead::Vector3f& delta);
    void sub_7100F631F4(bool on);      // mFlags 0x100

    // Unnamed accessors/setters (placeholder names; signatures from their bodies and callers)
    void sub_7100F5E7F0(float value);
    // 0x7100f62dd0 (not decompiled): RigidBody::setColImpulseScale on the main body and the extra bodies.
    void sub_7100F62DD0(f32 scale);
    // 0x7100f62e5c: the main rigid body's collision impulse scale.
    f32 sub_7100F62E5C() const;
    // 0x7100f5edb4 (unnamed in the CSV): mRigidBody->setSystemGroupHandler(handler).
    void sub_7100F5EDB4(SystemGroupHandler* handler);
    void sub_7100F5EDBC(const sead::Vector3f& value);
    void sub_7100F5EDD8(float value);
    void sub_7100F5EDE0(float value);
    void sub_7100F5EDE8(const sead::Vector3f& value);
    // 0x7100f5ee1c: sets _70 and its normalised copy _7c (unless flag 4 of _114 is set).
    void sub_7100F5EE1C(const sead::Vector3f& value);
    void sub_7100F5EEB8(float value);
    // 0x7100f5eee0: sets _220.
    void sub_7100F5EEE0(float value);
    // 0x7100f5f774 (declared only; called with (velocity, true, false) by sub_7100F5F6FC).
    void sub_7100F5F774(const sead::Vector3f& velocity, bool a2, bool a3);
    float sub_7100F5EF00() const;
    void sub_7100F5EF08(bool on);
    bool sub_7100F5F234(sead::Vector3f* out) const;
    void sub_7100F5F598(sead::Vector3f* velocity) const;
    void sub_7100F5F6E0(sead::Vector3f* position) const;
    void sub_7100F5F6FC(const sead::Vector3f& velocity);
    void sub_7100F5FB24(const sead::Vector3f& angular_velocity);
    // 0x7100f5fbc8 (declared only): RigidBody::computeVelocities of the controller's body (or of _298 when
    // flag 0x11a bit 0 is set): the linear and angular velocity that bring it to `target`.
    void sub_7100F5FBC8(sead::Vector3f* linear_velocity, sead::Vector3f* angular_velocity,
                        const sead::Matrix34f& target);
    void sub_7100F60500(const sead::Matrix34f& mtx);
    // 0x7100f5eecc (declared only)
    void sub_7100F5EECC(f32 value);
    // 0x7100f5e954: mRigidBody->isAddedToWorld().
    bool sub_7100F5E954() const;
    RigidBody* sub_7100F61A34() const;
    void sub_7100F62B70(float value);
    float sub_7100F60370() const;
    void sub_7100F60398(const sead::Vector3f& impulse);
    // 0x7100f5f270: switches to body `idx` of _288 (keeping the transform) when flag 0x10000 is
    // set, then sub_7100F5F344(idx, switched_or_unchanged).
    bool sub_7100F5F270(int idx);
    // 0x7100f5f938: validates `mtx`, then sets the velocities that move the body to it.
    void sub_7100F5F938(const sead::Matrix34f& mtx);
    // 0x7100f5fc8c: sets the angular velocity that rotates the body to `mtx`.
    void sub_7100F5FC8C(const sead::Matrix34f& mtx);
    // 0x7100f5fdf0: sets the angular velocity that turns the body towards `dir`.
    void sub_7100F5FDF0(const sead::Vector3f& dir);
    // 0x7100f60e98 (declared only; RailMoveBase::calc_).
    void sub_7100F60E98();
    bool sub_7100F5F344(int idx, bool force);
    bool sub_7100F62E74(f32* out, int idx) const;
    bool sub_7100F62EFC(sead::Vector3f* out, int idx) const;
    // 0x7100f5e764: RigidBody::clearEntityMotionFlag10 on the main body and (if _114 has 0x2000) on
    // every body of _288.
    void sub_7100F5E764(bool clear);
    // 0x7100f62bb0: sub_7100F5F270(1) (declaration only).
    void sub_7100F62BB0();
    // 0x7100f62bb8: sub_7100F5F270(0).
    void sub_7100F62BB8();

    // 0x7100f5ed4c: sets the user tag of the main rigid body (and of every body of _288 if _114 has 0x2000).
    void sub_7100F5ED4C(UserTag* tag);
    // 0x7100f5eda8: the user tag of the main rigid body.
    UserTag* sub_7100F5EDA8() const;
    // 0x7100f5f134 / 0x7100f5f140: the vectors at `_38 + 0x1c` / `_38 + 0x28`.
    const sead::Vector3f& sub_7100F5F134() const;
    const sead::Vector3f& sub_7100F5F140() const;
    // 0x7100f609c0 / 0x7100f609cc: the vectors at `_40 + 0x54` / `_40 + 0x18`.
    const sead::Vector3f& sub_7100F609C0() const;
    const sead::Vector3f& sub_7100F609CC() const;
    // 0x7100f5fba8: RigidBody::computeLinearVelocity of the controller's body (or of _298 when flag 0x10000 is set).
    void sub_7100F5FBA8(sead::Vector3f* velocity, const sead::Vector3f& target) const;
    // 0x7100f5e714: changeNoCharStandingOnFlag(!clear) of the main rigid body.
    void sub_7100F5E714(bool clear);
    // 0x7100f60840: whether the main rigid body uses the system time factor.
    bool sub_7100F60840() const;
    // 0x7100f60850: RigidBody::clearFlag400000 on the main body and (if _114 has 0x2000) on every body of _288.
    void sub_7100F60850(bool clear);
    // 0x7100f5f5a0 (declared only; the InstanceSet calls it after updating the motion type flags).
    void sub_7100F5F5A0();
    // 0x7100f5e754: sets the byte at +0x50 of the sub-object at +0x48.
    void sub_7100F5E754(bool value);
    // 0x7100f5f060: copies `value` to _ec.
    void sub_7100F5F060(const sead::Vector3f& value);
    // 0x7100f5f128: bit 0 of _116.
    bool sub_7100F5F128() const;
    // 0x7100f60458: clears the u64 at +0x94 and the word at +0x9c.
    void sub_7100F60458();
    // 0x7100f6059c: resets the movement state (_144 = 1.0f; _148 / _15c / _160 / _168 / _210 = 0; clears
    // most bits of _116).
    void sub_7100F6059C();
    // 0x7100f60e80: stores `value` (as 0 / 1) in the sub-objects at +0x50 (+0x38) and +0x48 (+0x94).
    void sub_7100F60E80(bool value);
    // 0x7100f62b78: _11c.
    f32 sub_7100F62B78() const;
    // 0x7100f62c14: RigidBody::setMaxImpulse on the main body and (if _114 has 0x2000) on every body of _288.
    void sub_7100F62C14(f32 max_impulse);
    // 0x7100f62ca0 / 0x7100f62dc8 / 0x7100f62e64 / 0x7100f62e6c: forwarders to the main rigid body
    // (getMaxImpulse / isEntityMotionFlag10Off / setCenterOfMassInLocal / getCenterOfMassInLocal).
    f32 sub_7100F62CA0() const;
    bool sub_7100F62DC8() const;
    void sub_7100F62E64(const sead::Vector3f& center);
    void sub_7100F62E6C(sead::Vector3f* center) const;
    // 0x7100f631e0: forwards `value` to the object at +0x40.
    void sub_7100F631E0(bool value);
    // 0x7100f6321c: sets / clears bit 0x200 of mFlags and updates the controller's friction-like values.
    void sub_7100F6321C(bool value);
    // 0x7100f63370: the byte at +0x6c of the object at +0x40.
    bool sub_7100F63370() const;

    // Unnamed small accessors (lane4 s32; placeholder names, bodies in the comments).
    // 0x7100f5e850: `if (value > 0) _10->_88 = value`.
    void sub_7100F5E850(f32 value);
    // 0x7100f5ee08: `_10->_30` (xyz).
    sead::Vector3f sub_7100F5EE08() const;
    // 0x7100f5eed4: `_10->_70 = value`.
    void sub_7100F5EED4(f32 value);
    // 0x7100f60368 / 0x7100f60378: setMass on the main body (the second also stores _138 and divides by _130).
    void sub_7100F60368(f32 mass);
    void sub_7100F60378(f32 mass);
    // 0x7100f63178: sets the flag at `_38 + 0x34` and copies the two vectors to `_38 + 0x38` / `_38 + 0x44`.
    void sub_7100F63178(const sead::Vector3f& a, const sead::Vector3f& b);
    // 0x7100f631b8: stores `value` in `_40->_10` and forwards it to `_40->sub_7100F6693C`.
    void sub_7100F631B8(bool value);
    // 0x7100f631cc: `_40->_10 == 1`.
    bool sub_7100F631CC() const;
    // 0x7100f607cc (declared only; the original inlines RigidBody::setEntityMotionFlag100 for the main body and _298).
    void sub_7100F607CC(bool on);
    // 0x7100f62640: out = (0, sqrt(2 * |_70| * _110 * a), 0).
    void sub_7100F62640(f32 a, sead::Vector3f* out);
    // 0x7100f63210 / 0x7100f6337c: the bytes at +0x70 / +0x6e of the object at +0x40.
    u8 sub_7100F63210() const;
    u8 sub_7100F6337C() const;

    RigidBody* mRigidBody;
    CharacterControllerUnk10* _10;
    u8 _18[0x20 - 0x18];
    CharacterControllerUnk20* _20;
    u8 _28[0x30 - 0x28];
    CharacterControllerShapes* _30;
    CharacterControllerUnk38* _38;
    CharacterControllerUnk40* _40;
    CharacterControllerUnk48* _48;
    CharacterControllerUnk50* _50;
    u8 _58[0x60 - 0x58];
    f32 _60;
    sead::Vector3f _64;
    sead::Vector3f _70;
    sead::Vector3f _7c;
    sead::Vector3f _88;  // zero in the ctor
    sead::Vector3f _94;  // zero in the ctor
    sead::Matrix34f _a0;  // ident in the ctor; PreyDead::enter_ reads its translation
    u8 _d0[0xec - 0xd0];
    sead::Vector3f _ec;
    u8 _f8[0xfc - 0xf8];
    f32 _fc;
    f32 _100;
    f32 _104;
    u8 _108[0x110 - 0x108];
    f32 _110;
    u16 _114;  // flags
    u16 _116;  // bit 2: read by PlayerFall::enter_
    sead::BitFlag32 mFlags;
    f32 _11c;
    sead::Vector3f _120;
    u8 _12c[4];
    f32 _130;
    f32 _134;
    f32 _138;
    u8 _13c[0x144 - 0x13c];
    f32 _144;
    f32 _148;
    u8 _14c[0x150 - 0x14c];
    s32 _150;  // saved / restored by PlayerWaterFall (zeroed while it is active; gravity-like)
    u8 _154[0x15c - 0x154];
    f32 _15c;
    f32 _160;
    f32 _164;
    f32 _168;
    f32 _16c;
    u8 _170[0x180 - 0x170];
    sead::Vector3f _180;
    u8 _18c;
    u8 _18d[0x210 - 0x18d];
    f32 _210;
    f32 _214;
    f32 _218;
    u8 _21c[0x220 - 0x21c];
    f32 _220;
    s32 _224;  // index into _288 of the current body (_298)
    u8 _228[0x238 - 0x228];
    u64 _238;
    sead::Vector3f _240;
    u8 _24c[0x250 - 0x24c];
    // Callbacks called with the controller by sub_7100F60604 (_250) and sub_7100F60500 (_258) (vtable
    // slot 0 of the delegate).
    sead::IDelegate1<CharacterController*>* _250;
    sead::IDelegate1<CharacterController*>* _258;
    u8 _260[0x288 - 0x260];
    sead::Buffer<RigidBody*> _288;
    RigidBody* _298;
};

}  // namespace ksys::phys
