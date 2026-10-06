#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace ksys::act {
class Actor;
}

namespace ksys::map {
class Rail;
}

// Unnamed rail follower embedded in uking::ai::RailMove (vtable 0x71024f15c0, size 0x60; CSV names
// "Rail::ctor", "Rail::x", "Rail::x_0"). Its functions live at 0x7100eeb800-0x7100eefc00, together
// with the free helpers below. Placeholder names (sub_<addr>).
class Unk_71024f15c0 {
public:
    // A position on the rail (copied as a whole: _30 = _8).
    struct Data {
        sead::Vector3f pos{0, 0, 0};
        sead::Vector3f rot{0, 0, 0};
        f32 progress = 0;
        ksys::map::Rail* rail = nullptr;

        const sead::Vector3f& sub_7100EEB370() const;
        // 0x7100eeb374 (declared only; lane4 s45): `rail` if it is a route (Rail::x_20), else null.
        ksys::map::Rail* sub_7100EEB374() const;
    };

    Unk_71024f15c0();
    virtual ~Unk_71024f15c0() = default;
    virtual void m2();
    virtual bool m3();
    virtual void m4(f32 distance, void* a2, f32* a3);

    void sub_7100EEBAE0(ksys::map::Rail* rail, f32 progress);
    bool sub_7100EEBB74() const;
    bool sub_7100EEBE88() const;
    void sub_7100EEBDB8(const Unk_71024f15c0* other);
    // Inline only (no out-of-line copy in the executable); placeholder name.
    void x(f32 distance) { m4(distance, nullptr, nullptr); }
    void sub_7100EEBE9C(s32 direction);

    Data _8;
    Data _30;
    s8 _58 = 1;
};

// The actor's idx-th linked rail (prints "レールがリンクされていません" if the actor has none).
ksys::map::Rail* sub_7100EEF264(ksys::act::Actor* actor, s32 idx);
// The actor's idx-th linked rail, or null (no debug message).
ksys::map::Rail* sub_7100EEF034(ksys::act::Actor* actor, s32 idx);
// Progress of the point on `rail` nearest to `pos` (not decompiled).
f32 sub_7100EEF7AC(const ksys::map::Rail* rail, const sead::Vector3f& pos, bool a3, f32 a4, f32 a5);
// The "WaitASKeyName" parameter of the rail's idx-th point (empty string if missing).
const char* sub_7100EEF358(const ksys::map::Rail* rail, s32 idx);
// The "WaitFrame" parameter of the rail's idx-th point (0 if missing).
f32 sub_7100EEF078(const ksys::map::Rail* rail, s32 idx);
// The "MoveSpeed" parameter of the rail's idx-th point (0 if missing).
f32 sub_7100EEF60C(const ksys::map::Rail* rail, s32 idx);
