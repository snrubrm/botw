#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
enum class MotionType;
}

namespace ksys::phys {

class RigidBody;

// TODO: incomplete (0x2a8 bytes; ctor 0x7100f5d8b8)
class CharacterController {
public:
    virtual ~CharacterController();

    void sub_7100F5EC30();
    void sub_7100F60604();
    void enableContactLayer(ContactLayer);
    void disableContactLayer(ContactLayer);
    void sub_7100F605F0();

    act::MotionType sub_7100F5F0E4() const;
    void sub_7100F5F458(act::MotionType type);

    bool sub_7100F636EC() const;
    void sub_7100F636B0(bool clear);
    bool sub_7100F63590() const;
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
    void sub_7100F5EEB8(float value);
    float sub_7100F5EF00() const;
    void sub_7100F5EF08(bool on);
    bool sub_7100F5F234(sead::Vector3f* out) const;
    void sub_7100F5F598(sead::Vector3f* velocity) const;
    void sub_7100F5F6E0(sead::Vector3f* position) const;
    void sub_7100F5F6FC(const sead::Vector3f& velocity);
    void sub_7100F5FB24(const sead::Vector3f& angular_velocity);
    RigidBody* sub_7100F61A34() const;
    void sub_7100F62B70(float value);

    RigidBody* mRigidBody;
    u8 _10[0x64 - 0x10];
    sead::Vector3f _64;
    sead::Vector3f _70;
    sead::Vector3f _7c;
    u8 _88[0x110 - 0x88];
    f32 _110;
    u8 _114[0x118 - 0x114];
    sead::BitFlag32 mFlags;
    u8 _11c[0x298 - 0x11c];
    RigidBody* _298;
};

}  // namespace ksys::phys
