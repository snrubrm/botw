#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjList.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>
#include <mc/seadJobQueue.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/gameGraphics.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
class BaseProc;
class Unk_71006e45c4;
}  // namespace ksys::act

namespace ksys::phys {
class NavMeshCharacter;
class RigidBody;
}

// Placeholder declarations: only the small out-of-line members that are decompiled so far (the real classes are
// polymorphic singletons; names from the CSV, no namespace; layouts incomplete).

// Path node read by Unk_710243c208::m2 (0x710066a28c): a segment from `_48` to `_54`; the rest is not recovered.
struct Unk_PathNode {
    u8 _0[0x48];
    sead::Vector3f _48;
    sead::Vector3f _54;
};

// Vtable GOT 0x258e9f8 (symbol 0x710243c208), the object at GameSceneSubsys4 + 0x16b0 (set up by 0x710066a598).
class Unk_710243c208 {
public:
    virtual ~Unk_710243c208() = default;
    // 0x710066a28c: true when the path node is farther than 3 from `mPos` or `mPos` lies before its start.
    virtual bool m2(const Unk_PathNode* node);

    sead::Vector3f mPos = sead::Vector3f::zero;
};
KSYS_CHECK_SIZE_NX150(Unk_710243c208, 0x18);

// GameSceneSubsys4: the path request manager (CSV createInstance 0x710066a204, ctor 0x710066a598). Only the members
// the AI code calls are declared (declaration only; the name follows the CSV).
class GameSceneSubsys4 {
    SEAD_SINGLETON_DISPOSER(GameSceneSubsys4)
    // 0x710066a598
    GameSceneSubsys4();
    virtual ~GameSceneSubsys4();

public:
    // User virtuals (vptr + 0x10 / 0x18 / 0x20; the third is an empty function that the stages' postCalc call).
    // m4 and m5 (0x710066a958 / 0x710066aaec) both release every request list.
    virtual void m4();
    virtual void m5();
    virtual void m6() {}

    // 0x710066b8c0: drops the path requests of `actor` (called by EnemyHide's destructor and
    // before a new request).
    void sub_710066B8C0(ksys::act::BaseProc* actor);
    // 0x710066b73c (declaration only): path request towards `target` (returns 1 when a path was found).
    s32 sub_710066B73C(ksys::act::Actor* actor, sead::Vector3f* target);
    // 0x710066b1bc (declaration only): path request using the points in `points`; the result is written to `out`.
    s32 sub_710066B1BC(f32 time, ksys::act::Actor* actor, ksys::phys::NavMeshCharacter* nav,
                       sead::ObjList<sead::Vector3f>* points, sead::ObjList<sead::Vector3f>* out);

    // A request of an actor to reach `mPos` (BaseProcLink at 0, Vector3f at 0x10; the list node follows at 0x20).
    struct Request {
        ksys::act::BaseProcLink mLink;
        sead::Vector3f mPos;
    };
    // Two points (the element type of the 0x1218 list; the list node follows at 0x18).
    struct PointPair {
        sead::Vector3f mFirst;
        sead::Vector3f mSecond;
    };

private:
    // Lists at 0x28 / 0x358 / 0x1008 / 0x1218 / 0x14a0 (capacities from the constructor: 16 / 100 / 15 / 15 / 15).
    sead::FixedObjList<Request, 16> mRequests;
    sead::FixedObjList<sead::Vector3f, 100> mPoints;
    sead::FixedObjList<sead::Vector3f, 15> mList1008;
    sead::FixedObjList<PointPair, 15> mList1218;
    sead::FixedObjList<sead::Vector3f, 15> mList14a0;
    Unk_710243c208 _16b0;
    sead::JobQueueLock mLock;
};
KSYS_CHECK_SIZE_NX150(GameSceneSubsys4, 0x16d0);

// Magnesis body state, constructed at 0x7100905034 and embedded in GameSceneSubsys5 +0x150.
// The saved body properties are restored by Unk_71006e45c4::sub_71006E4DF0.
class Unk_7100905034 {
public:
    Unk_7100905034();
    struct BodyState {
        f32 gravity;
        f32 friction;
        f32 restitution;
        u32 flags = 0;
    };
    sead::SafeArray<BodyState, 16> mBodyStates;
    Unk_71024505e8 _100;
    xlink2::HandleELink _138;
    xlink2::HandleELink _148;
    xlink2::HandleELink _158;
    xlink2::HandleSLink _168;
    sead::Vector3f _178 = sead::Vector3f::zero;
    s32 _184 = 0;
    s32 _188 = 0;
    sead::Vector3f _18c = sead::Vector3f::zero;
    u8 _198[0x1bc - 0x198];
    f32 _1bc = 0;
    f32 _1c0 = 1;
};
KSYS_CHECK_SIZE_NX150(Unk_7100905034, 0x1c8);

// 0x71009059fc: query used by the magnesis actor component to accept metal rigid bodies.
bool sub_71009059FC(const ksys::phys::RigidBody* body);

// GameSceneSubsys5: CSV createInstance 0x71009052fc, init 0x7100905468, postCalc 0x71009054bc.
class GameSceneSubsys5 {
    SEAD_SINGLETON_DISPOSER(GameSceneSubsys5)
    GameSceneSubsys5();
    ~GameSceneSubsys5();

public:

    // 0x7100905468
    void init();
    // 0x71009054bc (CSV GameSceneSubsys5::postCalc; declared only).
    void postCalc();
    // 0x71009059d4: _d8[_148]
    bool sub_71009059D4() const;
    // 0x7100905b34: _fc[_148]
    bool sub_7100905B34() const;
    // 0x7100905bec (placeholder name): true unless the selected `_d8` flag and `_32f` are set and `_138 > 3.5`.
    bool sub_7100905BEC() const;
    // 0x7100905b4c (placeholder name): `_331` and `pos` is within `_f4[_148]` of the selected position.
    bool sub_7100905B4C(const sead::Vector3f& pos) const;
    // 0x7100905d44 (placeholder name): the actor's id is `_140`.
    bool sub_7100905D44(ksys::act::Actor* actor) const;
    // 0x7100905ca8 (placeholder name): sets the selected position and its radius.
    void sub_7100905CA8(const sead::Vector3f& pos, f32 radius);
    // 0x7100905f30 (placeholder name): emits the "MagneConnect" ELink on the Reaction singleton's actor `_30` unless `_48` is still active.
    void sub_7100905F30();
    // 0x71009059ec: acquires the actor of the link at +0xa8 into `accessor` (if given).
    void sub_71009059EC(ksys::act::ActorConstDataAccess* accessor);
    // 0x7100905c70: _fc[_144] = true
    void sub_7100905C70();
    // 0x7100905c8c: _fe[_144] = true
    void sub_7100905C8C();
    // Small accessors (placeholder names after the offsets they use; addresses in the comments).
    void sub_7100905B1C();  // _331 = true
    void sub_7100905B28();  // _331 = false, _58 = false
    // 0x710090547c / 0x710090549c (the CSV __auto0 / __auto3; identical bodies): clears _331, _d8, _dc, _f4 and _fc / _fe.
    void sub_710090547C();
    void sub_710090549C();
    // 0x7100905dec / 0x7100905df8 / 0x7100905e00 / 0x7100905e10: `_b8.acquire(proc, false)`, `_b8.reset()`, acquires the actor
    // of `_b8` into `accessor` (if given), `_138 = value`.
    void sub_7100905DEC(ksys::act::BaseProc* proc);
    void sub_7100905DF8();
    void sub_7100905E00(ksys::act::ActorConstDataAccess* accessor);
    void sub_7100905E10(f32 value);
    // 0x7100905f08 / 0x7100905f10 / 0x7100905f18 / 0x7100905f28: `_13c = value`, `_c8.hasProc()`, `_10c`, `_329`.
    void sub_7100905F08(f32 value);
    bool sub_7100905F10() const;
    sead::Vector3f sub_7100905F18() const;
    bool sub_7100905F28() const;
    // 0x7100905e18 (placeholder name): the direction from the magnesis position of the player to the selected position
    // `_dc[_148]`, normalised ((0, 0, 1) without a player).
    sead::Vector3f sub_7100905E18() const;
    bool sub_7100905C30() const;  // _32f
    const sead::Vector3f& sub_7100905C38() const;  // _dc[_148]
    void sub_7100905C54();  // _d8[_144] = true
    void sub_7100905CEC(f32* out) const;  // out = {_124, _128}
    void sub_7100905D04(const f32* value);
    f32 sub_7100905D18() const;  // _130
    void sub_7100905D20(f32 value);
    f32 sub_7100905D34() const;  // _134
    void sub_7100905D3C(f32 value);
    sead::Vector3f sub_7100905D58() const;  // _100
    void sub_7100905D68(const sead::Vector3f& value);
    // 0x7100906044 (placeholder name): fades the ELink effect `_48` out.
    void sub_7100906044();
    // 0x710090611c (placeholder name): ray cast (the link parameter is unused, like in the next function) against `_320` from `start` to `start + dir * length`; writes the hit
    // position to `out` (if given).
    bool sub_710090611C(f32 length, ksys::act::BaseProcLink* unused, const sead::Vector3f& start,
                        const sead::Vector3f& dir, sead::Vector3f* out);
    // 0x7100906218 (placeholder name): magnesis ray cast from `start` along `dir * length`; always fails while `link`
    // has a proc, `out` receives the hit position (not null-checked).
    bool sub_7100906218(ksys::act::BaseProcLink* link, const sead::Vector3f& start, const sead::Vector3f& dir,
                        f32 length, sead::Vector3f* out);
    // 0x7100905d28 / 0x7100905de0: bool setters
    void sub_7100905D28(bool value);
    void sub_7100905DE0(bool value);

    // The oriented bounding box of the magnetised object (layout from its writer, 0x71006e5440: world centre of mass,
    // half extents of the local AABB, rotation).
    struct Box {
        sead::Vector3f center;
        sead::Vector3f half_extents;
        sead::Quatf rotation;
    };
    // 0x7100905d84 / 0x7100905d8c
    Box* sub_7100905D84();
    void sub_7100905D8C(const Box& box);

    Box _20{{0, 0, 0}, {0, 0, 0}, {0, 0, 0, 0}};
    xlink2::HandleELink _48;
    Unk_7100f35df8 _58;
    ksys::act::BaseProcLink _a8;
    ksys::act::BaseProcLink _b8;
    ksys::act::BaseProcLink _c8;
    sead::SafeArray<bool, 2> _d8{};
    sead::SafeArray<sead::Vector3f, 2> _dc{{{0, 0, 0}, {0, 0, 0}}};
    sead::SafeArray<f32, 2> _f4{};
    sead::SafeArray<bool, 2> _fc{};
    sead::SafeArray<bool, 2> _fe{};
    sead::Vector3f _100 = sead::Vector3f::zero;
    sead::Vector3f _10c = sead::Vector3f::zero;
    sead::Vector3f _118{0, 0, 0};
    f32 _124 = 0;
    f32 _128 = 0;
    u32 _12c = 0;
    f32 _130 = 20;
    f32 _134 = 2;
    f32 _138 = 0;
    f32 _13c = 0;
    s32 _140 = -1;
    s32 _144 = 0;
    s32 _148 = 1;
    Unk_7100905034 _150;
    ksys::act::Unk_71006e45c4* _318 = nullptr;
    ksys::phys::RigidBody* _320 = nullptr;
    bool _328 = false;
    bool _329 = false;
    bool _32a = false;
    bool _32b = false;
    bool _32c = false;
    bool _32d = false;
    bool _32e = false;
    bool _32f = false;
    bool _330 = false;
    bool _331 = false;
};


KSYS_CHECK_SIZE_NX150(GameSceneSubsys5, 0x338);
