#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Utils/Types.h"

namespace uking {

// Placeholder name (vtable 0x71024739d0; functions 0x710090d628-0x710090dbc8): a world ray cast
// (phys::RayCastBodyQuery) that also keeps its start and end points. Used on the stack by Player
// code and by the two free functions below.
// Members are public: the free functions in its TU access the query directly.
class Unk_71024739d0 {
public:
    explicit Unk_71024739d0(ksys::phys::GroundHit ground_hit);
    virtual ~Unk_71024739d0();
    virtual bool worldRayCast();

    void setStart(const sead::Vector3f& start);
    void setEnd(const sead::Vector3f& end);
    void getHitPosition(sead::Vector3f* position) const;
    void getHitNormal(sead::Vector3f* normal) const;
    bool hasHit() const { return mQuery.hasHit(); }

    // Contact layer presets.
    void sub_710090D73C();
    void sub_710090D784();
    void sub_710090D790();
    void sub_710090D808();
    void sub_710090D850();
    void sub_710090D8A4();

    ksys::phys::RayCastBodyQuery mQuery;
    sead::Vector3f mStart;
    sead::Vector3f mEnd;
};
KSYS_CHECK_SIZE_NX150(Unk_71024739d0, 0x108);

// Free functions of the next translation unit (gameUnk_710090d904.cpp; they call the members
// above out of line).

// 0x710090d904: casts down from `pos + dir * distance` (raised by 0.3) and back towards `pos`;
// true if no ground was hit or the hit normal is steeper than 50 degrees (|normal.y| < cos 50).
bool sub_710090D904(const sead::Vector3f& pos, const sead::Vector3f& dir, f32 distance, f32 height);

// 0x710090db04: casts a ray from `start` to `end`; on a hit, optionally returns the hit position,
// normal and material.
bool sub_710090DB04(const sead::Vector3f& start, const sead::Vector3f& end,
                    sead::Vector3f* hit_position, sead::Vector3f* hit_normal,
                    ksys::phys::MaterialMask* material_mask);

}  // namespace uking
