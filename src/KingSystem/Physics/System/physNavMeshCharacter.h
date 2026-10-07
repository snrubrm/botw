#pragma once

#include <basis/seadTypes.h>
#include <limits>
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadScopedLock.h>
#include <thread/seadAtomic.h>
#include <container/seadSafeArray.h>
#include <container/seadObjList.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class HavokAI;
class Unk_7102372790;
class Unk_7100f7e9f0Event;

// Placeholder name (ctor 0x7100f7e9f0, dtor 0x7100f7eb14; 0x18 bytes): result returned by value
// from NavMeshCharacter::sub_7100F76078.
class Unk_7100f7e9f0 {
public:
    Unk_7100f7e9f0();
    ~Unk_7100f7e9f0();

    bool sub_7100F7EB40() const;
    // 0x7100f7eee4 (declared only): compared with 5 by PriestBossMove::m35.
    s32 sub_7100F7EEE4() const;

    /* 0x00 */ void* _0;
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
};

// Placeholder: the 0xe0-byte object at NavMeshCharacter::_8 (only the accessed fields are modelled).
struct NavMeshCharacterUnk8 {
    /* 0x00 */ u8 _0[0x6c];
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
struct NavMeshCharacterUnk10 {
    /* 0x000 */ u8 _0[0x78];
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
    void init();

    void sub_7100F75AB8();
    // 0x7100f75af0 (placeholder name): hands the query `_2e0` to HavokAI::sub_7100F83A9C.
    void sub_7100F75AF0();
    // 0x7100f760f0 / 0x7100f76168 / 0x7100f761c8 (placeholder names): forward to HavokAI (the `_18` of the character, or
    // the singleton) after the NaN checks of the arguments; the last two pass the radius `_2a8 * _2ac`.
    Unk_7100f7e9f0 sub_7100F760F0(sead::Vector3f* out, const sead::Vector3f& to);
    bool sub_7100F76168(f32 value, bool flag, void* out);
    bool sub_7100F761C8(const sead::Vector3f& pos, f32 value, bool flag, void* out);
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
    // 0x710038ae34 (declaration only): the same function emitted in EnemyEscapeMove's translation unit.
    void sub_710038AE34(sead::ObjList<sead::Vector3f>::iterator begin,
                        sead::ObjList<sead::Vector3f>::iterator end);
    // 0x7100f7d1b4 / 0x7100f7d1cc / 0x7100f7d298 (lane4 s29): the list of agent ids (`other->_8->_98`) at _a8 /
    // _d0 (HorseFollow: the rider's character): set the list to one entry, append an entry (returns its
    // index, -1 when full or when another thread appended first), replace the entry at `index` (ignored
    // when out of range).
    void sub_7100F7D1B4(const NavMeshCharacter* other);
    s32 sub_7100F7D1CC(const NavMeshCharacter* other);
    void sub_7100F7D298(s32 index, const NavMeshCharacter* other);

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
    // in AssassinNormal, NavMoveNearTarget, NavMoveTarget::m36/m37, HorseRideEnemyFindPlayer,
    // GiantNavMoveTarget and LynelNavMoveNoStop (no out-of-line copy).
    f32 getRadiusMaybe() const { return _2a8 * _2ac; }

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

    // Inline-only in the original (lane5 s1 / lane4 s45; names are guesses): the setters used by the NavMeshAction
    // family (NavMeshAction enter_ / leave_, also EnemyRushAttack, KokkoMove, AnimalFollowBase and
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
    /* 0x020 */ u8 _20[0x58 - 0x20];
    /* 0x058 */ void* _58 = nullptr;
    /* 0x060 */ void* _60 = nullptr;
    /* 0x068 */ sead::CriticalSection _68;
    /* 0x0a8 */ sead::SafeArray<u32, 10> _a8;  // BaseProc ids (up to 10 entries, count in _d0)
    /* 0x0d0 */ sead::Atomic<s32> _d0 = 0;
    /* 0x0d4 */ sead::Vector3f _d4;
    /* 0x0e0 */ u8 _e0[0x194 - 0xe0];
    /* 0x194 */ sead::Vector3f _194;
    /* 0x1a0 */ sead::Vector3f _1a0;
    /* 0x1ac */ sead::Vector3f _1ac;
    /* 0x1b8 */ sead::Vector3f _1b8;
    /* 0x1c4 */ u32 _1c4;
    /* 0x1c8 */ u32 _1c8 = 0;
    /* 0x1d0 */ u64 _1d0 = 0;
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
    /* 0x298 */ u8 _298[0x2a4 - 0x298];
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
    /* 0x2e0 */ Unk_7102372790* _2e0;  // navmesh query (released through HavokAI::sub_7100F83A94)
};

}  // namespace ksys::phys
