#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

// Unnamed object (vtable 0x71024f15f8, ctor 0x7100eebf70; its functions are in the same TU as
// Unk_71024f15c0's, 0x7100eeb800-0x7100eefc00). Embedded in HorseEscapeRouteRailAI (+0x50).
// Placeholder layout from the constructor.
class Unk_71024f15f8 {
public:
    Unk_71024f15f8();
    virtual ~Unk_71024f15f8() = default;
    virtual void m2();
    virtual bool m3();
    virtual void m4(f32 distance, const sead::Vector3f* direction, u32* flags);

    void* _8 = nullptr;
    void* _10 = nullptr;
    void* _18 = nullptr;
    u32 _20 = 0;
    void* _28 = nullptr;
    void* _30 = nullptr;
    void* _38 = nullptr;
    void* _40 = nullptr;
    u32 _48 = 0;
    void* _50 = nullptr;
    bool _58 = true;
    sead::SafeString _60;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f15f8, 0x70);
