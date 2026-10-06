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
    void sub_7100D3D3C4(int a, const sead::Vector3f* vec, int b, bool c);
    bool sub_7100D3D49C(ksys::act::Actor* actor, ksys::act::ActorConstDataAccess* accessor, int a);

    u16 _0 = 0;
    u16 _2 = 1;
    u8 _4 = 0;
    void* _8 = nullptr;
    void* _10 = nullptr;
    void* _18 = nullptr;
};
