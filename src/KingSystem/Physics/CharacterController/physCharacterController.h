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

class CollisionInfo;
class ContactPointInfo;
class RigidBody;
class SystemGroupHandler;

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
    // 0x7100f605c8: copies `value` to _ac / _bc / _cc.
    void sub_7100F605C8(const sead::Vector3f& value);

    bool sub_7100F636EC() const;
    void sub_7100F636B0(bool clear);
    // 0x7100f63700 (lane1 s21): clears (or sets) mFlags bit 0x40.
    void sub_7100F63700(bool clear);
    // 0x7100f63388 (not decompiled; AssassinBossRoot enter_/m42 pass (true / false, -1)).
    void sub_7100F63388(bool enable, s32 idx);
    bool sub_7100F63590() const;
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
    const sead::Vector3f& get70() const { return _70; }
    const sead::Vector3f& get7c() const { return _7c; }
    f32 get110() const { return _110; }

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

    RigidBody* mRigidBody;
    u8 _10[0x60 - 0x10];
    f32 _60;
    sead::Vector3f _64;
    sead::Vector3f _70;
    sead::Vector3f _7c;
    sead::Vector3f _88;  // zero in the ctor
    sead::Vector3f _94;  // zero in the ctor
    sead::Matrix34f _a0;  // ident in the ctor; PreyDead::enter_ reads its translation
    u8 _d0[0xfc - 0xd0];
    f32 _fc;
    f32 _100;
    u8 _104[0x110 - 0x104];
    f32 _110;
    u16 _114;  // flags
    u8 _116;  // bit 2: read by PlayerFall::enter_ (the flag word at 0x114 may be a u32)
    u8 _117;
    sead::BitFlag32 mFlags;
    f32 _11c;
    u8 _120[0x150 - 0x120];
    s32 _150;  // saved / restored by PlayerWaterFall (zeroed while it is active; gravity-like)
    u8 _154[0x210 - 0x154];
    f32 _210;
    u8 _214[0x220 - 0x214];
    f32 _220;
    s32 _224;  // index into _288 of the current body (_298)
    u8 _228[0x240 - 0x228];
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
