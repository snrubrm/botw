#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjList.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>
#include <xlink2/xlink2HandleELink.h>
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

// GameSceneSubsys4: the path request manager (CSV createInstance 0x710066a204, ctor 0x710066a598). Only the members
// the AI code calls are declared (declaration only; the name follows the CSV).
class GameSceneSubsys4 {
    SEAD_SINGLETON_DISPOSER(GameSceneSubsys4)
    // 0x710066a598 / 0x710066a28c (declaration only)
    GameSceneSubsys4();
    virtual ~GameSceneSubsys4();

public:
    // User virtuals (vptr + 0x10 / 0x18 / 0x20; 0x66a958 / 0x66aaec are not decompiled, the third is an empty function that
    // the stages' postCalc call).
    virtual void m4();
    virtual void m5();
    virtual void m6() {}

    // 0x710066b8c0 (declaration only): drops the path requests of `actor` (called by EnemyHide's destructor and
    // before a new request).
    void sub_710066B8C0(ksys::act::BaseProc* actor);
    // 0x710066b73c (declaration only): path request towards `target` (returns 1 when a path was found).
    s32 sub_710066B73C(ksys::act::Actor* actor, sead::Vector3f* target);
    // 0x710066b1bc (declaration only): path request using the points in `points`; the result is written to `out`.
    s32 sub_710066B1BC(f32 time, ksys::act::Actor* actor, ksys::phys::NavMeshCharacter* nav,
                       sead::ObjList<sead::Vector3f>* points, sead::ObjList<sead::Vector3f>* out);

private:
    u8 _28[0x16d0 - 0x28];
};
KSYS_CHECK_SIZE_NX150(GameSceneSubsys4, 0x16d0);

// GameSceneSubsys5: CSV createInstance 0x71009052fc, init 0x7100905468, postCalc 0x71009054bc.
class GameSceneSubsys5 {
public:
    // The instance pointer (0x71025d1770, GOT 0x25793f8; the singleton machinery is not declared yet).
    static GameSceneSubsys5* instance() { return sInstance; }
    static GameSceneSubsys5* sInstance;

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
    void sub_7100905CEC(s32* out) const;  // out = {_124, _128}
    void sub_7100905D04(const s32* value);
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

    u8 _0[0x20];
    Box _20;
    xlink2::HandleELink _48;
    bool _58;
    u8 _59[0x8c - 0x59];
    f32 _8c;
    f32 _90;
    u8 _94[0x9c - 0x94];
    u32 _9c;
    u8 _a0[0xa8 - 0xa0];
    ksys::act::BaseProcLink _a8;
    ksys::act::BaseProcLink _b8;
    ksys::act::BaseProcLink _c8;
    sead::SafeArray<bool, 2> _d8;
    u8 _da[0xdc - 0xda];
    sead::SafeArray<sead::Vector3f, 2> _dc;
    sead::SafeArray<f32, 2> _f4;
    sead::SafeArray<bool, 2> _fc;
    sead::SafeArray<bool, 2> _fe;
    sead::Vector3f _100;
    sead::Vector3f _10c;
    u8 _118[0x124 - 0x118];
    s32 _124;
    s32 _128;
    u8 _12c[0x130 - 0x12c];
    f32 _130;
    f32 _134;
    f32 _138;
    f32 _13c;
    s32 _140;
    s32 _144;
    s32 _148;
    u8 _14c[0x150 - 0x14c];
    u8 _150[0x318 - 0x150];
    ksys::act::Unk_71006e45c4* _318;
    ksys::phys::RigidBody* _320;
    bool _328;
    bool _329;
    u8 _32a[0x32f - 0x32a];
    bool _32f;
    u8 _330;
    bool _331;
};

