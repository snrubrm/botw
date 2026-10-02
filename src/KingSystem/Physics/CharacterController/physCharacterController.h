#pragma once

#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class MotionType;
}

namespace ksys::phys {

class CollisionInfo;
class ContactPointInfo;
class RigidBody;

// TODO: incomplete (0x2a8 bytes; ctor 0x7100f5d8b8)
class CharacterController {
public:
    virtual ~CharacterController();

    void sub_7100F5EC30();
    void sub_7100F5EC44();
    void sub_7100F60604();
    void enableContactLayer(ContactLayer);
    void disableContactLayer(ContactLayer);
    void sub_7100F605F0();
    // 0x7100f62bc0: setFixed on the main rigid body (unless it is already unfixed and `fixed` is false).
    void sub_7100F62BC0(bool fixed);

    act::MotionType sub_7100F5F0E4() const;
    void sub_7100F5F458(act::MotionType type);

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

    // set by sub_7100F5EEB8
    const sead::Vector3f& get64() const { return _64; }
    const sead::Vector3f& get70() const { return _70; }
    const sead::Vector3f& get7c() const { return _7c; }
    f32 get110() const { return _110; }

    // Unnamed accessors/setters (placeholder names; signatures from their bodies and callers)
    void sub_7100F5E7F0(float value);
    void sub_7100F5EDBC(const sead::Vector3f& value);
    void sub_7100F5EDD8(float value);
    void sub_7100F5EDE0(float value);
    void sub_7100F5EDE8(const sead::Vector3f& value);
    // 0x7100f5ee1c: sets _70 and its normalised copy _7c (unless flag 4 of _114 is set).
    void sub_7100F5EE1C(const sead::Vector3f& value);
    void sub_7100F5EEB8(float value);
    // 0x7100f5eee0: sets _220.
    void sub_7100F5EEE0(float value);
    float sub_7100F5EF00() const;
    void sub_7100F5EF08(bool on);
    bool sub_7100F5F234(sead::Vector3f* out) const;
    void sub_7100F5F598(sead::Vector3f* velocity) const;
    void sub_7100F5F6E0(sead::Vector3f* position) const;
    void sub_7100F5F6FC(const sead::Vector3f& velocity);
    void sub_7100F5FB24(const sead::Vector3f& angular_velocity);
    void sub_7100F60500(const sead::Matrix34f& mtx);
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

    RigidBody* mRigidBody;
    u8 _10[0x64 - 0x10];
    sead::Vector3f _64;
    sead::Vector3f _70;
    sead::Vector3f _7c;
    sead::Vector3f _88;  // zero in the ctor
    sead::Vector3f _94;  // zero in the ctor
    sead::Matrix34f _a0;  // ident in the ctor; PreyDead::enter_ reads its translation
    u8 _d0[0x110 - 0xd0];
    f32 _110;
    u16 _114;  // flags
    u8 _116[0x118 - 0x116];
    sead::BitFlag32 mFlags;
    u8 _11c[0x224 - 0x11c];
    s32 _224;  // index into _288 of the current body (_298)
    u8 _228[0x288 - 0x228];
    sead::Buffer<RigidBody*> _288;
    RigidBody* _298;
};

}  // namespace ksys::phys
