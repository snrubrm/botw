#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
}  // namespace ksys::act

// Placeholder name (0x7100d3d3a8, no name known): a 0x20-byte state struct embedded at the end of
// several action classes (Kick at 0x88, AirOctaFloat, ApplyMoveTrigger, EnemyChangeWeapon). Its
// constructor is out of line and called from their constructors.
struct Unk_7100d3d3a8 {
    Unk_7100d3d3a8();

    // Placeholder names (out of line, no names known; signatures from Kick::sub_71001C8A10).
    // 0x7100d3d3c4: if `_3` is 0: `_0 = a`, `_2 = c`, `_8 = *vec` and, when `b` is given, `_14 = *b`.
    void sub_7100D3D3C4(int a, const sead::Vector3f* vec, const sead::Vector3f* b, u8 c);
    // 0x7100d3d49c: `_4 = flag`, sends message 0x3000014 (payload = this) from `actor` to the accessor's actor, sets `_3`.
    void sub_7100D3D49C(ksys::act::Actor* actor, ksys::act::ActorConstDataAccess* accessor, bool flag);

    u16 _0 = 0;
    u8 _2 = 1;
    u8 _3 = 0;  // sub_7100D3D3C4 only stores while this is 0; sub_7100D3D49C sets it to 1
    u8 _4 = 0;
    sead::Vector3f _8{0.0f, 0.0f, 0.0f};
    sead::Vector3f _14{0.0f, 0.0f, 0.0f};
};

static_assert(sizeof(Unk_7100d3d3a8) == 0x20);
