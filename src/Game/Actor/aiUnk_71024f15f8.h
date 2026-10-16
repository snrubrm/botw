#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/aiUnk_71024f15c0.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {
class Rail;
class RailConnectablePoint;
class RailRoute;
}

// Unnamed object (vtable 0x71024f15f8, ctor 0x7100eebf70; its functions are in the same TU as
// Unk_71024f15c0's, 0x7100eeb800-0x7100eefc00). Embedded in HorseEscapeRouteRailAI (+0x50).
// Placeholder layout from the constructor.
class Unk_71024f15f8 {
public:
    Unk_71024f15f8();
    virtual ~Unk_71024f15f8() = default;
    // 0x7100eebfbc: resets both rail positions, the direction and the route name.
    virtual void m2();
    // 0x7100eec6a8: whether the current position is at an end of the rail without a junction.
    virtual bool m3();
    // 0x7100eec18c: advances the current position by `distance` (backwards to the end for a negative one), picking
    // the direction at junctions with sub_7100EEC2D0.
    virtual void m4(f32 distance, const sead::Vector3f* direction, u32* flags);
    // Slots 5 - 9 (0x7100eec014, 0x7100eec0a4, 0x7100eec134, 0x7100eebeb4, 0x7100eec698): start on the road
    // point of the route ids in _60 (PlacementMgr::roadStuff), on the one nearest to `pos`, or on `point`;
    // m9 tests a route against _60.
    virtual bool m5();
    virtual bool m6(const sead::Vector3f* pos);
    virtual bool m7(const sead::Vector3f* pos, const sead::Vector3f* direction);
    virtual bool m8(const ksys::map::RailConnectablePoint* point, const sead::Vector3f* direction);
    virtual bool m9(const ksys::map::RailRoute* route);
    // Inline only (like Unk_71024f15c0::x); placeholder name.
    void x(f32 distance) { m4(distance, nullptr, nullptr); }

    // 0x7100eebf24 (placeholder name): the route id of _8's rail when it is a rail route (Rail::x_20), else null.
    const char* sub_7100EEBF24() const;
    // 0x7100eec2d0 (placeholder name; declaration only, 968 B): the direction to follow from `data` (m4).
    s8 sub_7100EEC2D0(Unk_71024f15c0::Data* data, s32 direction, const sead::Vector3f* dir,
                      u32* flags);

    // Same layout as Unk_71024f15c0 (previous / current rail position), plus the route ids.
    Unk_71024f15c0::Data _8;
    Unk_71024f15c0::Data _30;
    s8 _58 = 1;
    sead::SafeString _60;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f15f8, 0x70);
