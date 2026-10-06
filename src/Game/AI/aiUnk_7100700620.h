#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;
}

// Placeholder name (0x7100700620, no name known): an 8-byte state struct embedded in
// WaterUpDownMoveBase (+0x7c) and WaterUpDownAnmDrivenMove. Its constructor is out of line.
struct Unk_7100700620 {
    Unk_7100700620();
    ~Unk_7100700620();

    // 0x7100700634 (12 B): copies a float of the actor (Actor::_6f4) to _0.
    void sub_7100700634(ksys::act::Actor* actor);

    // 0x7100700640 (416 B, declared only): updates _0 from the actor and its AS event (type 0x3b).
    bool sub_7100700640(ksys::act::Actor* actor);

    f32 _0 = -1.0f;
    f32 _4 = 0.5f;
};
