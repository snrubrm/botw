#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <gsys/gsysModelAccessKey.h>
#include <container/seadBuffer.h>
#include <limits>
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include <prim/seadScopedLock.h>
#include <thread/seadAtomic.h>
#include <container/seadSafeArray.h>
#include <container/seadObjList.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/System/physCharacterControllerParam.h"
#include "KingSystem/Utils/Types.h"
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Object/hkReferencedObject.h>

class hkaiStreamingCollection;

namespace sead {
class Heap;
}

namespace gsys {
class Model;
}

namespace ksys::phys {

class HavokAI;
struct NavMeshObjMaybe;
class Unk_7102372790;
class NavMeshCharacterQuery;
class NavMeshFaceCallback;
class NavMeshCharacter;

// Placeholder value names: the path state _294 of a NavMeshCharacter (0 after inlineReset; AI actions finish
// on 2 / 3 and keep moving on 1).
SEAD_ENUM(NavMeshPathState, State0, State1, State2, State3)

// Placeholder: the object at NavMeshCharacter::_58 (a face material filter; when it is null the per-type cost
// table of NavMeshCharacter::sub_7100F74FD8 decides). Only slot 4 is known.
class NavMeshCharacterUnk58 {
public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    // Whether a face with the sub material `material` is usable (callers pass 0 and nullptr).
    virtual bool m4(NavMeshCharacter* nav, s32 material, s32 a, void* b);
};
class Unk_7100f7e9f0Event;

// Placeholder name (ctor 0x7100f7e9f0, dtor 0x7100f7eb14; 0x18 bytes): result returned by value
// from NavMeshCharacter::sub_7100F76078.
class Unk_7100f7e9f0 {
public:
    Unk_7100f7e9f0();
    // 0x7100f87760 passes hkaiWorld +0x20, the packed face key and its event.
    Unk_7100f7e9f0(hkaiStreamingCollection* collection, s32 key, Unk_7100f7e9f0Event* event);
    Unk_7100f7e9f0& operator=(const Unk_7100f7e9f0& other);
    ~Unk_7100f7e9f0();

    bool sub_7100F7EB40() const;
    // Complete 0x7100f7eb60 and callers 0x71005e11ac/0x71002c071c establish world-position output.
    bool sub_7100F7EB60(sead::Vector3f* position_out) const;
    // 0x7100f7ed6c returns the packed face's area and optionally writes its world normal.
    f32 sub_7100F7ED6C(sead::Vector3f* normal_out) const;
    // 0x7100f7eee4 (declared only): compared with 5 by PriestBossMove::m35.
    s32 sub_7100F7EEE4() const;

    /* 0x00 */ hkaiStreamingCollection* _0;
    /* 0x08 */ s32 _8;
    /* 0x10 */ Unk_7100f7e9f0Event* _10;
};
KSYS_CHECK_SIZE_NX150(Unk_7100f7e9f0, 0x18);

// Placeholder: object at NavMeshCharacterUnk8::_a0 (the initial values of the speed limits).
struct NavMeshCharacterUnk8A0 {
    /* 0x00 */ u8 _0[0xc];
    /* 0x0c */ f32 _c;
    /* 0x10 */ f32 _10;
    /* 0x14 */ u8 _14[0x24 - 0x14];
    /* 0x24 */ f32 _24;
    /* 0x28 */ u8 _28[0x64 - 0x28];
    // Per-type values (NavMeshCharacter::sub_7100F7E624).
    /* 0x64 */ f32 _64;
    /* 0x68 */ f32 _68;
    /* 0x6c */ u8 _6c[0x70 - 0x6c];
    /* 0x70 */ f32 _70;
    /* 0x74 */ f32 _74;
};

// Placeholder: the 0xe0-byte object at NavMeshCharacter::_8 (only the accessed fields are modelled).
struct NavMeshCharacterUnk8 : public hkReferencedObject {
    /* 0x010 */ u8 _0[0x10];
    // 0x7100f87334 / 0x7100f87464 use this as the position when the caller passes a null `pos` (16 bytes copied).
    /* 0x20 */ hkVector4f _20;
    /* 0x30 */ u8 _30[0x6c - 0x30];
    /* 0x6c */ f32 _6c;
    /* 0x70 */ u8 _70[0x98 - 0x70];
    /* 0x98 */ u32 _98;
    /* 0x9c */ u8 _9c[0xa0 - 0x9c];
    /* 0xa0 */ NavMeshCharacterUnk8A0* _a0;
};

// 0x7101ec27f4 (placeholder name, read-only data; 1000000.0f): the replacement for an infinite value in
// NavMeshCharacter::inlineSetField2C0.
extern const f32 sUnk_7101ec27f4;

// 0x710260ddd8 (placeholder name): counter of the request ids stored in NavMeshCharacter::_290 (read through the GOT).
extern sead::Atomic<u32> sUnk_710260ddd8;

// Placeholder: object at NavMeshCharacter::_10 + 0x78 (move parameters).
struct NavMeshCharacterMoveParam {
    /* 0x00 */ u8 _0[0x18];
    /* 0x18 */ f32 _18;
    /* 0x1c */ f32 _1c;
};

// Placeholder: object at NavMeshCharacter::_10 (only the accessed fields are modelled).
struct NavMeshCharacterUnk10 : public hkReferencedObject {
    /* 0x010 */ u8 _0[0x68];
    /* 0x078 */ NavMeshCharacterMoveParam* _78;
    /* 0x080 */ u8 _80[0x16c - 0x80];
    /* 0x16c */ u32 _16c;
    /* 0x170 */ sead::BitFlag16 _170;
};

// Name from the CSV (phys::NavMeshCharacter::*, ctor 0x7100f752ac). Returned by Actor vtable slot 45
// (InstanceSet::mNavMeshCharacter). Layout from the ctor and from the fields AI code accesses.
// The object also has vtable pointers at 0x38 and 0x48 (multiple inheritance, not modelled yet).
// TODO: incomplete.
class NavMeshCharacter {
public:
    NavMeshCharacter();
    virtual ~NavMeshCharacter();

    void finalize();
    // Placeholder type: the initialization packet built by 0x710128247C and 0x7100041784.
    // Its vectors and scalar settings are consumed by 0x7100F750BC / 0x7100F75680.
    // lane1 s91: layout from 0x710128247C (fills a stack copy) and Motorcycle::m164; names unknown.
    struct InitArg {
        sead::Vector3f _0;   // sead::Vector3f::zero in 0x710128247C
        sead::Vector3f _c;   // sead::Vector3f::ez
        f32 _18;             // 1.0
        f32 _1c;             // 1.75
        s32 _20;             // 16
        f32 _24;             // 3.0
        f32 _28;             // 3.0
        f32 _2c;             // 1e6 (a global constant)
        f32 _30;
        f32 _34;
        f32 _38;             // 1.0
        f32 _3c;             // 1.0
        f32 _40;             // 100.0
        f32 _44;             // 1.0
        f32 _48;             // 0.01
        s32 _4c;             // 0
        s32 _50;             // 4
        s32 _54;             // 0
        u8 _58;
        u8 _59;
    };
    static_assert(sizeof(InitArg) == 0x5c);
    // 0x7100f7e598 (placeholder name): sets the per-type parameters _38 / _3c / _40 / _48 of `arg` from a table and
    // the type-specific flags (_58 / _59 for Player, _54 = 10 for Horse and NPC / NPCGoron / NPCSwimmer).
    static void sub_7100F7E598(InitArg* arg, NavMeshCharacterType type);
    // 0x7100f7e624 (placeholder name): copies the same per-type table values into `obj`.
    static void sub_7100F7E624(NavMeshCharacterUnk8A0* obj, s32 type);
    void init(const InitArg& arg, sead::Heap* heap, HavokAI* havok_ai);
    // Actual implementation reached by the original init tail call (declared only).
    void sub_7100F75680(const InitArg& arg, sead::Heap* heap, HavokAI* havok_ai);

    void sub_7100F75AB8();
    // 0x7100f75af0 (placeholder name): hands the query `_2e0` to HavokAI::sub_7100F83A9C.
    void sub_7100F75AF0();
    // 0x7100f760f0 / 0x7100f76168 / 0x7100f761c8 (placeholder names): forward to HavokAI (the `_18` of the character, or
    // the singleton) after the NaN checks of the arguments; the last two pass the radius `_2a8 * _2ac`.
    Unk_7100f7e9f0 sub_7100F760F0(sead::Vector3f* out, const sead::Vector3f& to, f32 value);
    bool sub_7100F76168(f32 value, bool flag, NavMeshFaceCallback* callback);
    bool sub_7100F761C8(const sead::Vector3f& pos, f32 value, bool flag, NavMeshFaceCallback* callback);
    // 0x7100f76260 (placeholder name): stores `pos` in _1b8 (unless it contains NaN), sets bit 0x2000 and clears 0x20000 of _220.
    void sub_7100F76260(const sead::Vector3f& pos);
    // 0x7100f76344 (placeholder name): sets / clears bit 1 of the flags `_10->_170`.
    void sub_7100F76344(bool on);
    void sub_7100F75F3C(u8 value);
    void sub_7100F75F8C(const sead::Vector3f& target);
    void sub_7100F7604C(f32 value);
    void sub_7100F7605C(f32 value);
    void sub_7100F7606C(u32 value);
    // 0x7100f76078: `out` is written by the query (lane1: an output parameter); `to` is checked for
    // NaN first (default result).
    Unk_7100f7e9f0 sub_7100F76078(sead::Vector3f* out, const sead::Vector3f& to, f32 a3);
    // 0x7100f76380: pose update; stores the position (_254) and the three directions (_260 / _26c /
    // _278) unless they contain NaN (the first and the last one are flattened to the XZ plane and normalized).
    void sub_7100F76380(const sead::Vector3f& pos, const sead::Vector3f& dir_a,
                        const sead::Vector3f& vec, const sead::Vector3f& dir_b);
    // 0x7100f765e8 / 0x7100f76694 (declaration only): position request and flattened direction.
    void sub_7100F765E8(const sead::Vector3f& pos);
    void sub_7100F76694(const sead::Vector3f& direction);
    void sub_7100F76314();
    void sub_7100F76778();
    void sub_7100F76790();
    void sub_7100F7D2C8();
    void sub_7100F7D308(s32 value);
    void sub_7100F7D350();
    // Declaration only.
    void sub_7100394884(sead::ObjList<sead::Vector3f>::iterator begin,
                        sead::ObjList<sead::Vector3f>::iterator end);
    // 0x710019960c (placeholder name; defined in the GuardianMoveToPosition TU of the original): the same point-list
    // setter over an array of Vector3f pointers.
    void sub_710019960C(sead::Vector3f* const* begin, sead::Vector3f* const* end);
    // 0x710038ae34: a separate original point-list setter used by EnemyEscapeMove.
    void sub_710038AE34(sead::ObjList<sead::Vector3f>::iterator begin,
                        sead::ObjList<sead::Vector3f>::iterator end);
    // 0x71003f76a0 (declaration only; defined in the GiantEscapeFromDamageWater TU of the original): the same
    // point-list setter over a range of an array of eight points (the end compares only the index).
    void sub_71003F76A0(sead::SafeArray<sead::Vector3f, 8>::iterator begin,
                        sead::SafeArray<sead::Vector3f, 8>::iterator end);
    // 0x7100f7d1b4 / 0x7100f7d1cc / 0x7100f7d298 (lane4 s29): the list of agent ids (`other->_8->_98`) at _a8 /
    // _d0 (HorseFollow: the rider's character): set the list to one entry, append an entry (returns its
    // index, -1 when full or when another thread appended first), replace the entry at `index` (ignored
    // when out of range).
    void sub_7100F7D1B4(const NavMeshCharacter* other);
    s32 sub_7100F7D1CC(const NavMeshCharacter* other);
    s32 sub_7100F7D234(const NavMeshObjMaybe* other);
    void sub_7100F7D298(s32 index, const NavMeshCharacter* other);

    // inline-only in the original; name is a guess (PriestBossWalkAttack::calc_ (x2) and Enemy::Unk_12d0 read
    // _294 under _1e0 and pass it through a stack slot, as a SEAD_ENUM value does).
    NavMeshPathState getPathState() {
        auto lock = sead::makeScopedLock(_1e0);
        return NavMeshPathState(_294);
    }

    // Inline-only in the original (no out-of-line copy; inlined at ~45 call sites: enemy / animal /
    // horse AI actions and NavMeshCharacter's own TU); the name is a placeholder. Under _1e0: flags
    // _220 |= 0x10000, _220 &= ~0x201000, then clears the path state.
    void inlineReset() {
        auto lock = sead::makeScopedLock(_1e0);
        _220 |= 0x10000;
        _220 &= ~0x201000u;
        _294 = 0;
        _194.set(std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                 std::numeric_limits<f32>::quiet_NaN());
        _1a0.set(std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                 std::numeric_limits<f32>::quiet_NaN());
        _23c.set(0, 0, 0);
        _2cc = 0;
        _1db = 0;
    }

    // Inline-only in the original; name is a guess. Evidence: `nav ? nav->_2a8 * nav->_2ac : X` is repeated
    // in GuardHomePosNormal, NavMoveNearTarget, NavMoveTarget::m36/m37, HorseRideEnemyFindPlayer,
    // GiantNavMoveTarget and LynelNavMoveNoStop (no out-of-line copy).
    f32 getRadiusMaybe() const { return _2a8 * _2ac; }

    // 0x7100f74fd8 (declared only; placeholder name): the cost of the face sub material `material` for the
    // character type `type` (a table at 0x7101ec22ec plus special cases).
    static f32 sub_7100F74FD8(s32 type, s32 material);
    // 0x7100f74f94 (placeholder name): _1d8 of `character`, 0 without one.
    static u8 sub_7100F74F94(const NavMeshCharacter* character);
    // 0x7100f74fa0 (placeholder name): true for type 0, or when `material` is 10 and `type` is not.
    static bool sub_7100F74FA0(s32 type, s32 material);

    // Inline-only in the original; name is a guess. GiantNavMoveTarget::m34 0x71003f7904 and its face callback
    // 0x71003f9260, and the face callbacks of HorseMoveToSafePos (0x71001a27b8) and HorseSwimAction
    // (0x7100e58340) repeat it: asks the filter at _58, or else accepts any finite material cost.
    bool isMaterialUsableMaybe(s32 material) {
        if (_58)
            return _58->m4(this, material, 0, nullptr);
        if (sead::Mathf::abs(sub_7100F74FD8(_1d8, material)) > std::numeric_limits<f32>::max())
            return false;
        return true;
    }

    // Inline-only in the original (lane1 s21; name is a placeholder): sets the three vectors at
    // 0x194 / 0x1a0 / 0x1ac to NaN under _1e0 (seen after inlineReset() in AnimalRoamCheckWater,
    // HorseMoveToTargetAction::enter_ and others).
    void inlineClearTargets() {
        auto lock = sead::makeScopedLock(_1e0);
        _194.set(std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                 std::numeric_limits<f32>::quiet_NaN());
        _1a0.set(std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                 std::numeric_limits<f32>::quiet_NaN());
        _1ac.set(std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                 std::numeric_limits<f32>::quiet_NaN());
    }

    // Inline-only in the original (lane5 s1 / lane4 s45; names are guesses): the setters used by the NavMeshMoveBase
    // family (NavMeshMoveBase enter_ / leave_, also EnemyRushAttack, KokkoMove, HorseFollowBase and
    // AnimalMoveStraightTimed use them). Both store a value under `_1e0` and set a bit of the flags `_220`.
    // `_2bc` (bit 0x400) is only changed for a valid value (checks in the original order: |v| <= FLT_MAX,
    // v >= 0, not NaN). `_2c0` (bit 0x800) is only changed if `value` is not below the initial limit
    // `_8->_a0->_c`; a value above FLT_MAX is replaced by 1000000.0 (sUnk_7101ec27f4); the replacement is
    // computed before the lock is taken.
    // NON_MATCHING note for users: the original sets the bit with ONE ldxr/stxr loop computing
    // `(old & ~bit) | bit` (a custom read-modify-write); sead::Atomic only has fetchOr (a plain `orr` in the
    // loop, one `and` less), so callers differ by that instruction. FLT_MAX is also loaded once into a
    // callee-saved register in the original but rematerialised here, and the original branches separately
    // per range check where we get fcmp+ccmp.
    void inlineSetField2BC(f32 value) {
        if (sead::Mathf::abs(value) > std::numeric_limits<f32>::max() || value < 0.0f ||
            sead::Mathf::isNan(value))
            return;
        auto lock = sead::makeScopedLock(_1e0);
        _2bc = value;
        _220 |= 0x400;
    }

    void inlineSetField2C0(f32 value) {
        if (_8->_a0->_c > value)
            return;
        const f32 clamped =
            sead::Mathf::abs(value) > std::numeric_limits<f32>::max() ? sUnk_7101ec27f4 : value;
        auto lock = sead::makeScopedLock(_1e0);
        _2c0 = clamped;
        _220 |= 0x800;
    }

    /* 0x008 */ NavMeshCharacterUnk8* _8 = nullptr;  // heap object (0xe0 bytes) created by init
    /* 0x010 */ NavMeshCharacterUnk10* _10 = nullptr;
    /* 0x018 */ HavokAI* _18 = nullptr;
    // HavokAI::sub_7100F82BCC exchanges this with ldxr/stxr (sead::Atomic): the HavokAI that should handle the next
    // request (compared against `ai | 1`).
    /* 0x020 */ sead::Atomic<HavokAI*> _20;
    /* 0x028 */ u8 _28[0x58 - 0x28];
    /* 0x058 */ NavMeshCharacterUnk58* _58 = nullptr;
    /* 0x060 */ void* _60 = nullptr;
    /* 0x068 */ sead::CriticalSection _68;
    /* 0x0a8 */ sead::SafeArray<u32, 10> _a8;  // BaseProc ids (up to 10 entries, count in _d0)
    /* 0x0d0 */ sead::Atomic<s32> _d0 = 0;
    /* 0x0d4 */ sead::Vector3f _d4[16];  // path points (the first one is the target of sub_7100F75F8C)
    /* 0x194 */ sead::Vector3f _194;
    /* 0x1a0 */ sead::Vector3f _1a0;
    /* 0x1ac */ sead::Vector3f _1ac;
    /* 0x1b8 */ sead::Vector3f _1b8;
    /* 0x1c4 */ u32 _1c4;
    /* 0x1c8 */ u32 _1c8 = 0;
    /* 0x1d0 */ u8* _1d0 = nullptr;
    /* 0x1d8 */ u8 _1d8 = 4;
    /* 0x1d9 */ u8 _1d9 = 4;
    /* 0x1da */ u8 _1da = 0;
    /* 0x1db */ u8 _1db = 0;
    /* 0x1e0 */ sead::CriticalSection _1e0;
    /* 0x220 */ sead::Atomic<u32> _220 = 0;  // flags
    /* 0x224 */ sead::Vector3f _224;
    /* 0x230 */ sead::Vector3f _230;
    /* 0x23c */ sead::Vector3f _23c;
    /* 0x248 */ sead::Vector3f _248;
    /* 0x254 */ sead::Vector3f _254;
    /* 0x260 */ sead::Vector3f _260;
    /* 0x26c */ sead::Vector3f _26c;
    /* 0x278 */ sead::Vector3f _278;
    /* 0x284 */ sead::Vector3f _284;
    /* 0x290 */ u32 _290 = 0;
    /* 0x294 */ u8 _294 = 0;
    /* 0x295 */ u8 _295;
    /* 0x296 */ u8 _296;  // read under _1e0 (AnimalRangeKeepMoveWithLOS)
    /* 0x297 */ u8 _297;
    /* 0x298 */ u8 _298[0x29c - 0x298];
    /* 0x29c */ f32 _29c;  // read under _1e0 when (_2a4 & 0xffff) != 0x17 (FlyMoveToTarget)
    /* 0x2a0 */ u8 _2a0[0x2a4 - 0x2a0];
    /* 0x2a4 */ sead::Atomic<u32> _2a4;
    /* 0x2a8 */ f32 _2a8;
    /* 0x2ac */ f32 _2ac;
    /* 0x2b0 */ f32 _2b0;
    /* 0x2b4 */ u8 _2b4[0x2bc - 0x2b4];
    /* 0x2bc */ f32 _2bc;
    /* 0x2c0 */ f32 _2c0;
    /* 0x2c4 */ u8 _2c4[0x2cc - 0x2c4];
    /* 0x2cc */ f32 _2cc;
    /* 0x2d0 */ f32 _2d0;
    /* 0x2d4 */ f32 _2d4;
    /* 0x2d8 */ u8 _2d8[0x2e0 - 0x2d8];
    /* 0x2e0 */ NavMeshCharacterQuery* _2e0;  // navmesh query (released through HavokAI::sub_7100F83A94)
};

// Placeholder (vtable 0x71024f67c8: only D1 0x7100f73bec / D0 0x7100f73c30; set up by 0x7100f72ca0 /
// 0x7100f73714): a chain of model bones (entries of 0xc0 bytes) with three extra bone keys. Defined next
// to NavMeshCharacter (its address neighbour); handed over from lane4.
class Unk_71024f67c8 {
public:
    struct Entry {
        u8 _0[0x10];
        gsys::BoneAccessKeyEx mBone;
        sead::Vector3f mScale;
        sead::Vector3f _54;
        sead::Matrix34f _60;
        sead::Matrix34f _90;
    };
    static_assert(sizeof(Entry) == 0xc0);

    // Read by init 0x7100f73714 (placeholder names; bone names of the three keys and an optional one).
    struct InitArg {
        gsys::Model* model;
        sead::Vector3f _8;
        const char* bone_20;
        const char* bone_58;
        const char* bone_90;
        const char* bone_extra;
        f32 _38;
        f32 _3c;
        u8 _40;
        bool _41;
        f32 _44;
        f32 _48;
        f32 _4c;
    };

    virtual ~Unk_71024f67c8();

    // 0x7100f73640 (placeholder name): creates and initialises a chain.
    static Unk_71024f67c8* sub_7100F73640(const InitArg& arg, sead::Heap* heap);
    // 0x7100f73714 (declaration only; placeholder name): looks up the bones and builds the entries.
    bool sub_7100F73714(const InitArg& arg, sead::Heap* heap);

    // 0x7100f73c7c (placeholder name): reads every entry's local bone matrix and scale from the model
    // (after clearing the local matrices if `reset`), scales its translation by the previous entry's
    // scale (_54) and stores it in _60 and _90.
    void sub_7100F73C7C(bool reset);
    // 0x7100f73e50 (placeholder name): chains the local matrices: _90 = parent _90 * _60.
    void sub_7100F73E50();
    // 0x7100f73b7c (placeholder name): frees the entries and deletes this object.
    void sub_7100F73B7C();
    // 0x7100f74e20 (placeholder name): stores `value` clamped to [0, 1] in _108.
    void sub_7100F74E20(f32 value);
    // 0x7100f74e44 / 0x7100f74e68 / 0x7100f74e8c / 0x7100f74eb0 (placeholder names): _90 of the
    // entries _c8 / _cc / _d0 / _d4.
    sead::Matrix34f* sub_7100F74E44();
    sead::Matrix34f* sub_7100F74E68();
    sead::Matrix34f* sub_7100F74E8C();
    sead::Matrix34f* sub_7100F74EB0();
    // 0x7100f74ed4 (placeholder name): sets the local matrix of entry _d0 (translation divided by its
    // scale) and applies it to the model.
    void sub_7100F74ED4(const sead::Matrix34f& matrix);
    // 0x7100f74f44 (placeholder name): _60 of entry _d4.
    sead::Matrix34f* sub_7100F74F44();
    // 0x7100f74f68 (placeholder name): applies the local matrix of entry `index` to the model.
    void sub_7100F74F68(s32 index);

    gsys::Model* mModel = nullptr;
    sead::Vector3f _10;
    u8 _1c[0x20 - 0x1c];
    gsys::BoneAccessKeyEx _20;
    gsys::BoneAccessKeyEx _58;
    gsys::BoneAccessKeyEx _90;
    s32 _c8 = -1;
    s32 _cc = -1;
    s32 _d0 = -1;
    s32 _d4 = -1;
    s32 _d8 = -1;
    sead::Vector3f _dc = sead::Vector3f::zero;
    u8 _e8[0xf8 - 0xe8];
    sead::Buffer<Entry> mEntries;
    f32 _108 = 1.0f;
    f32 _10c = 1.0f;
    f32 _110 = 1.0f;
    f32 _114 = 0.0f;
    f32 _118 = sead::Mathf::pi();
    bool _11c = false;
    f32 _120 = 0.0f;
    f32 _124 = sead::Mathf::pi();
};
static_assert(sizeof(Unk_71024f67c8) == 0x128);

}  // namespace ksys::phys
