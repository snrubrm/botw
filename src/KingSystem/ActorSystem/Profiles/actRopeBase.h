#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {
class RigidBody;
}  // namespace ksys::phys

namespace ksys::act {

namespace acc {
class RopeBase;
}

// TODO
class RopeBase : public Actor {
    SEAD_RTTI_OVERRIDE(RopeBase, Actor)
public:
    ~RopeBase() override;

    void m43(bool on) override;
    bool shouldUnload(s32* a1) override;
    void updatePositionMaybe() override;
    int getExtraHeapSize() override;

    // 0x7100ecde98 (declared only): cancels the constraints and removes the rigid bodies of the rope from the world.
    void sub_7100ECDE98();
    // 0x7100ece61c (lane1 s41, declaration only; placeholder name): the point of the rope at `length` from its start.
    sead::Vector3f sub_7100ECE61C(f32 length);

    // FIXME: figure out return types, parameters and names
    virtual void m148();
    virtual void m149();
    virtual void m150();

    friend class acc::RopeBase;

protected:
    // TODO
    u8 _840[0x860 - 0x840];
    sead::Buffer<phys::RigidBody*> _860;
    u8 _870[0x880 - 0x870];
    sead::Buffer<phys::RigidBody*> _880;
    u8 _890[0x8c0 - 0x890];
    BaseProcLink _8c0[2];
    u8 _8e0[0x92c - 0x8e0];
    s32 _92c;
    s32 _930;
    u8 _934[4];
    f32 _938;  // length of one rope segment (lane1 s41)
    u8 _93c[0x956 - 0x93c];
    u8 _956;
    u8 _957[0x95a - 0x957];
    bool _95a;
    u8 _95b[0x971 - 0x95b];
    bool _971;
    u8 _972[0x974 - 0x972];
    s32 _974;
    u8 _978[0x9d0 - 0x978];
    BaseProcHandle _9d0;
    u8 _9e0[0xa00 - 0x9e0];
};

}  // namespace ksys::act

namespace ksys::act::acc {

// Accessor for RopeBase actors (CSV act::acc::x::requestCutOffHungPoint; lane4 s44; the other names are guesses; functions
// 0x7100ed8344-0x7100ed8580).
class RopeBase : public ActorConstDataAccess {
public:
    // 0x7100ed8344: `_956` is set.
    bool sub_7100ED8344() const;
    // 0x7100ed8580 (debugLog "requestCutOff(HungPoint)" twice): `_971 = true; _974 = on ? _930 + 1 : 0`.
    void requestCutOffHungPoint(int on) const;
    // 0x7100ed8440 (lane1 s41, placeholder name): the point of the rope at the fraction `ratio` (0 - 1) of its length
    // (zero without a rope).
    sead::Vector3f sub_7100ED8440(f32 ratio) const;

protected:
    ksys::act::RopeBase* getRopeBase() const;
};

}  // namespace ksys::act::acc
