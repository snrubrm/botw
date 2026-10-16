#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::map {
class Rail;
}

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
    // Inline only (like Unk_71024f15c0::x); placeholder name.
    void x(f32 distance) { m4(distance, nullptr, nullptr); }

    // 0x7100eebf24 (placeholder name): the route id of _28 when it is a rail route (Rail::x_20), else null.
    const char* sub_7100EEBF24() const;
    // 0x7100eebfbc (placeholder name): resets the positions, the rail, the counters and the name.
    void sub_7100EEBFBC();

    sead::Vector3f _8{0, 0, 0};
    sead::Vector3f _14{0, 0, 0};
    u32 _20 = 0;
    ksys::map::Rail* _28 = nullptr;
    sead::Vector3f _30{0, 0, 0};
    sead::Vector3f _3c{0, 0, 0};
    u32 _48 = 0;
    void* _50 = nullptr;
    bool _58 = true;
    sead::SafeString _60;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f15f8, 0x70);
