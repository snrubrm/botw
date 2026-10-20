#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

// Placeholder names (vtables 0x71023e2708 / 0x71023e26d8 / 0x71023e2750 / 0x71023e2780; lane4 s23): the request
// objects that AI code passes to the awareness sensors (`AwarenessInstance::_260[i]`, Unk_71024dce08::m4 / m5) to
// query them: DistanceLostCheck (type 1 / 4: `_260[0]`, 2: `_260[1]`, 3: `_260[3]`), InterestNeckControl::m8,
// ViewChaseSound, PreyNormal, RemainsFireDroneNormal. All four have a trivial constructor (inlined) and their
// vtables (RTTI functions + dtors) are emitted with DistanceLostCheck::enter_ (0x7100362bd0 - 0x7100363064).

// RTTI root of the requests (vtable 0x71023e2708; size 0x10).
class Unk_71023e2708 {
    SEAD_RTTI_BASE(Unk_71023e2708)
public:
    // `{ ; }` like upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229): the base D1 (0x7100362dc8) stores
    // its vtable pointer (and is inlined into the derived destructors).
    virtual ~Unk_71023e2708() { ; }

    // 0x08: the derived requests start here: `_8` / `_c` are declared in each of them (the hearing
    // sensor copies Unk_71023e2750's 0x8-0x20 as one block).
};

// Sight parameters of the sight sensor and its request (0x18 bytes).
struct SightParams {
    f32 radius = 0;
    f32 angle;
    f32 height_max = 0;
    f32 height_min = 0;
    f32 height_near_max = 0;
    f32 height_near_min = 0;
};
KSYS_CHECK_SIZE_NX150(SightParams, 0x18);

// Far sight parameters of the sight sensor and its request (0x14 bytes).
struct SightFarParams {
    f32 ignore_grass_radius = 0;
    f32 ray_check_range_max = -1.0f;
    bool far_use = false;
    f32 radius_far = 0;
    f32 angle_far = 0;
};
KSYS_CHECK_SIZE_NX150(SightFarParams, 0x14);

// Request of the sensor `_260[0]` (vtable 0x71023e26d8; 0x50 bytes). The sensor's m5 copies its sight parameters
// out (InterestNeckControl::m8 reads sight.angle), m6 copies them in (AwarenessInstance::sub_7100D7E74C sets
// sight.angle) and caches the angle cosines.
class Unk_71023e26d8 : public Unk_71023e2708 {
    SEAD_RTTI_OVERRIDE(Unk_71023e26d8, Unk_71023e2708)
public:
    // The original has a separate out-of-line D1 per request type that only stores the base vtable (the base
    // destructor inlined): written as `{ ; }` like upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229).
    ~Unk_71023e26d8() override { ; }

    // The sight, sight alert and far sight parameters (names from AwarenessInstance::SetupArg). The sensor's m5 / m6
    // load every field before storing any, as from a whole Params copy.
    // sight.angle has no initializer (the original request construction only stores radius:
    // HiddenOctarockSearchTarget / HiddenOctarockFindPlayer; the angle is always set explicitly before use).
    struct Params {
        /* 0x00 */ SightParams sight;
        /* 0x18 */ SightParams alert{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
        /* 0x30 */ SightFarParams far;
    };
    /* 0x08 */ Params params;
};
KSYS_CHECK_SIZE_NX150(Unk_71023e26d8, 0x50);

// Request of the sensor `_260[1]` (vtable 0x71023e2750; 0x20 bytes).
class Unk_71023e2750 : public Unk_71023e2708 {
    SEAD_RTTI_OVERRIDE(Unk_71023e2750, Unk_71023e2708)
public:
    // The original has a separate out-of-line D1 per request type that only stores the base vtable (the base
    // destructor inlined): written as `{ ; }` like upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229).
    ~Unk_71023e2750() override { ; }

    // The hearing sensor (Unk_71024dcd68) copies `params` as one block (m4 0x7100d7f3c8: its
    // 0x58-0x6c; m5 / m6 also copy _8 to / from its _54).
    struct Params {
        f32 _0;
        f32 _4 = 0;
        f32 _8 = 0;
        f32 warnRatio = 0;    // AwnHearingParamChange
        f32 noticeRatio = 0;  // AwnHearingParamChange
    };

    /* 0x08 */ f32 _8 = 0;  // range: read by DistanceLostCheck / WaitNearTargetAwarenessRange
    /* 0x0c */ Params params;
};
KSYS_CHECK_SIZE_NX150(Unk_71023e2750, 0x20);

// Request of the sensor `_260[3]` (vtable 0x71023e2780; 0x10 bytes, nothing but the base).
class Unk_71023e2780 : public Unk_71023e2708 {
    SEAD_RTTI_OVERRIDE(Unk_71023e2780, Unk_71023e2708)
public:
    ~Unk_71023e2780() override { ; }

    /* 0x08 */ f32 _8 = 0;
    /* 0x0c */ f32 _c;
};
KSYS_CHECK_SIZE_NX150(Unk_71023e2780, 0x10);

