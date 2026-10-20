#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/physDefines.h"

namespace uking::action {
class BalloonRopeBase;
}

namespace uking::ai {
class RopeRoot;
}

namespace ksys::phys {
class Constraint;
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
    // 0x7100ecaa68 (declared only).
    explicit RopeBase(const CreateArg& arg);
    // Rope's destructor (0x7100024a04) inlines this one; that needs the key function initMaybe (0x7100ecf66c) defined
    // so the vtable and the destructor stay in this TU.
    ~RopeBase() override;

    // Primary vtable24F0440 slot64 points toECF66C; Actor names this slot initMaybe.
    void initMaybe() override;
    void m43(bool on) override;
    bool shouldUnload(s32* a1) override;
    void updatePositionMaybe() override;
    void m63() override;
    void m74() override;
    void m76(VFR::ScopedDeltaSetter* setter) override;
    int getExtraHeapSize(const ActorHeapInitArgMaybe& arg) override;

    // 0x7100ecde98: cancels the constraints and removes the rigid bodies of the rope from the world.
    void sub_7100ECDE98();
    // 0x7100ecd620 (placeholder name): switches off and clears the constraint of segment `idx`; for an end segment
    // (0 or _928 - 1) also the matching active actor constraint and end attachment, else it keeps it in _850.
    void sub_7100ECD620(s32 idx);
    // Filled by sub_7100ED2C24 for one end constraint of the rope (0x7100ecdab8 does both ends).
    struct EndState {
        f32 _0 = 0;  // _950, or the attached body's mass times a constant
        bool _4 = false;
        bool _5 = false;
        bool _6 = false;
        bool _7 = false;
        bool _8 = false;
    };
    // 0x7100ecdab8 (placeholder name): computes both end states and applies them (sub_7100ED2D4C); with _95b,
    // sets damping 0.25 / max velocity 15 on the bodies and PSI priority on the constraints.
    void sub_7100ECDAB8();
    // 0x7100ed2c24 / 0x7100ed2d4c (placeholder names; 0x7100ed2d4c, 1600 B, declaration only).
    void sub_7100ED2C24(phys::Constraint* constraint, EndState* state);
    void sub_7100ED2D4C(EndState* first, EndState* last);
    // 0x7100ece61c (lane1 s41, declaration only; placeholder name): the point of the rope at `length` from its start.
    sead::Vector3f sub_7100ECE61C(f32 length);
    // 0x7100ece0cc / 0x7100ece140 (declared only; placeholder names; BalloonRopeBase::m35): enable the contact
    // layer / set every contact on each rigid body of the rope.
    void sub_7100ECE0CC(phys::ContactLayer layer);
    void sub_7100ECE140();
    // 0x7100ece1ac / 228 / 29c / 318 / 394 (placeholder names): set the mass / local inertia / linear damping /
    // angular damping / gravity factor of every rope body.
    void sub_7100ECE1AC(f32 mass);
    void sub_7100ECE228(const sead::Vector3f& inertia);
    void sub_7100ECE29C(f32 value);
    void sub_7100ECE318(f32 value);
    void sub_7100ECE394(f32 value);
    // 0x7100ece76c (placeholder name): the rope length, (_930 + 1) segments of _938.
    f32 sub_7100ECE76C() const;
    // 0x7100ece410 (placeholder name): the position along the rope of `pos`: the index of the closest rigid body
    // of the first list times the segment length (`_938`) plus a term from the angle to that body's y axis.
    f32 sub_7100ECE410(const sead::Vector3f& pos) const;
    // 0x7100ed68b4 (placeholder name): the segment index of `pos` (via sub_7100ECE410), clamped to 0 / _930.
    s32 sub_7100ED68B4(const sead::Vector3f& pos) const;
    // 0x7100ed6910 (placeholder name; does not use `this`): acquires into `accessor` the actor owning the
    // second body of `constraint` (through its PhysicsUserTag); false (and `accessor` cleared) otherwise.
    bool sub_7100ED6910(ActorLinkConstDataAccess* accessor, const phys::Constraint* constraint) const;
    // 0x7100ed6878 (placeholder name): the rigid body `index` of the first list (null when index is negative or past _930).
    phys::RigidBody* sub_7100ED6878(s32 index) const;

    // FIXME: figure out return types, parameters and names
    virtual void m148() {}
    virtual void m149() {}
    virtual void m150();

    friend class acc::RopeBase;
    friend class uking::ai::RopeRoot;
    friend class uking::action::BalloonRopeBase;

protected:
    // TODO
    // Constraints between consecutive rope bodies (0x7100ecd620 releases entry `idx`, keeping a copy in _850).
    sead::Buffer<phys::Constraint*> _840;
    sead::Buffer<phys::Constraint*> _850;
    sead::Buffer<phys::RigidBody*> _860;
    sead::Buffer<phys::RigidBody*> _870;
    sead::Buffer<phys::RigidBody*> _880;
    sead::Buffer<phys::RigidBody*> _890;
    u8 _8a0[0x8b0 - 0x8a0];
    // The constraints attaching the rope ends (0x7100ecd620 switches them off with their segment).
    phys::Constraint* _8b0;
    phys::Constraint* _8b8;
    BaseProcLink _8c0[2];
    u8 _8e0[0x8f0 - 0x8e0];
    struct ConstraintFrames {
        sead::Matrix34f first;
        sead::Matrix34f second;
    };
    // Native scale update reads each pair at a 0x60-byte stride.
    sead::Buffer<ConstraintFrames> _8f0;
    u8 _900[0x928 - 0x900];
    s32 _928;  // number of constraint entries (the last index is an end segment)
    s32 _92c;
    s32 _930;
    u8 _934[4];
    f32 _938;  // length of one rope segment (lane1 s41)
    f32 _93c;  // scale of the (1 - dot) term in sub_7100ECE410
    f32 _940;  // sub_7100ED68B4 multiplies the rope position by this to get a segment index
    f32 _944;  // unscaled segment length
    u8 _948[4];
    f32 _94c;  // rope scale
    f32 _950;  // default end weight (sub_7100ED2C24)
    u8 _954;
    // 2026-10-07: ECAA68 clears this flag; ED4A80 sets it together with _956 after detachment.
    bool _955;
    u8 _956;
    u8 _957[0x95a - 0x957];
    bool _95a;
    bool _95b;  // 0x7100ecdab8: slows the bodies and switches the constraints to PSI priority
    u8 _95c[0x96c - 0x95c];
    // 2026-10-07: ED1B00/ED1D78/ED33F0 write states 1/2/3; ED5010 switches on the state.
    s32 _96c;
    // ED4E50 clears this flag and sets it when a rigid body is detached.
    bool _970;
    bool _971;
    u8 _972[0x974 - 0x972];
    s32 _974;
    u8 _978[0x988 - 0x978];
    bool _988;  // scale update enabled
    u8 _989;
    // BalloonRopeBase::enter_ clears this after attaching the rope (lane3 s70).
    bool _98a;
    u8 _98b[0x9d0 - 0x98b];
    BaseProcHandle _9d0;
    u8 _9e0[0xa00 - 0x9e0];
};
KSYS_CHECK_SIZE_NX150(RopeBase, 0xa00);

}  // namespace ksys::act

namespace ksys::act::acc {

// Accessor for RopeBase actors (CSV act::acc::x::requestCutOffHungPoint; lane4 s44; the other names are guesses; functions
// 0x7100ed8344-0x7100ed8580).
class RopeBase : public ActorLinkConstDataAccess {
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
