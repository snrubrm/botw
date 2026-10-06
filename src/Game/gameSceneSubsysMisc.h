#pragma once

#include <basis/seadTypes.h>
#include <container/seadObjList.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
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
}

// Placeholder declarations: only the small out-of-line members that are decompiled so far (the real classes are
// polymorphic singletons; names from the CSV, no namespace; layouts incomplete).

// GameSceneSubsys4: the path request manager (CSV createInstance 0x710066a204, ctor 0x710066a598). Only the members
// the AI code calls are declared (declaration only; the name follows the CSV).
class GameSceneSubsys4 {
public:
    // The instance pointer (0x71025c5d48, GOT 0x2586ab0; the singleton machinery is not declared yet).
    static GameSceneSubsys4* instance() { return sInstance; }
    static GameSceneSubsys4* sInstance;

    // 0x710066b8c0 (declaration only): drops the path requests of `actor` (called by EnemyHide's destructor and
    // before a new request).
    void sub_710066B8C0(ksys::act::BaseProc* actor);
    // 0x710066b73c (declaration only): path request towards `target` (returns 1 when a path was found).
    s32 sub_710066B73C(ksys::act::Actor* actor, sead::Vector3f* target);
    // 0x710066b1bc (declaration only): path request using the points in `points`; the result is written to `out`.
    s32 sub_710066B1BC(f32 time, ksys::act::Actor* actor, ksys::phys::NavMeshCharacter* nav,
                       sead::ObjList<sead::Vector3f>* points, sead::ObjList<sead::Vector3f>* out);
};

// GameSceneSubsys5: CSV createInstance 0x71009052fc, init 0x7100905468, postCalc 0x71009054bc.
class GameSceneSubsys5 {
public:
    // The instance pointer (0x71025d1770, GOT 0x25793f8; the singleton machinery is not declared yet).
    static GameSceneSubsys5* instance() { return sInstance; }
    static GameSceneSubsys5* sInstance;

    // 0x7100905468
    void init();
    // 0x71009059d4: _d8[_148]
    bool sub_71009059D4() const;
    // 0x7100905b34: declaration only, query the selected bank flag.
    bool sub_7100905B34() const;
    // 0x71009059ec: acquires the actor of the link at +0xa8 into `accessor` (if given).
    void sub_71009059EC(ksys::act::ActorConstDataAccess* accessor);
    // 0x7100905c70: _fc[_144] = true
    void sub_7100905C70();
    // 0x7100905c8c: declaration only, current selected bank force-off flag.
    void sub_7100905C8C();
    // 0x7100905d28 / 0x7100905de0: bool setters
    void sub_7100905D28(bool value);
    void sub_7100905DE0(bool value);

    u8 _0[0x8c];
    f32 _8c;
    f32 _90;
    u8 _94[0x9c - 0x94];
    u32 _9c;
    u8 _a0[0xa8 - 0xa0];
    ksys::act::BaseProcLink _a8;
    u8 _b8[0xc8 - 0xb8];
    ksys::act::BaseProcLink _c8;
    sead::SafeArray<bool, 2> _d8;
    u8 _da[0xdc - 0xda];
    u8 _dc[0xfc - 0xdc];
    sead::SafeArray<bool, 2> _fc;
    u8 _fe[0x144 - 0xfe];
    s32 _144;
    s32 _148;
    u8 _14c[0x150 - 0x14c];
    u8 _150[0x318 - 0x150];
    ksys::act::Unk_71006e45c4* _318;
    u8 _320[0x328 - 0x320];
    bool _328;
    u8 _329[0x32f - 0x329];
    bool _32f;
    u8 _330;
    bool _331;
};

