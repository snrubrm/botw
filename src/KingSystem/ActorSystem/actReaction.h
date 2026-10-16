#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {
class Actor;

// Partial declaration. Reaction::createInstance (0x7100ec0138) stores the
// singleton at 0x71026064c0; its 0x180-byte allocation and members remain unrecovered.
class Reaction {
public:
    // Placeholder: the object at _a8 (class unknown). 0x7100ec66fc sets its _110 to 2; the actor
    // argument is unused. Called by OctarockOptionRoot::calc_ when the player touches the rock.
    struct Unk1 {
        void sub_7100EC66FC(Actor* actor);
        // Constant getters (0.7f / 7 / 5); placeholder names.
        f32 sub_7100EC877C() const;
        s32 sub_7100EC87A4() const;
        s8 sub_7100EC89BC() const;

        u8 _0[0x110];
        /* 0x110 */ s32 _110;
    };

    static Reaction* instance() { return sInstance; }
    static Reaction* sInstance;
    // Surface raycast/XLink update called by GolemRootBase::calc_; declaration only.
    void sub_7100EC29D0(Actor* actor);

    // EC04D0 stores an Actor cast from the released handle; EC0D20 deletes the same actor.
    // EC04D0 releases the first handle and dynamically casts it to Actor here.
    u8 _0[0x28];
    Actor* _28;
    Actor* _30;
    Actor* _38;
    u8 _40[0xa8 - 0x40];
    Unk1* _a8;
};
}  // namespace ksys::act
