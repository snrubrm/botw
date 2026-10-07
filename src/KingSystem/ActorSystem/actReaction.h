#pragma once

namespace ksys::act {
class Actor;

// Partial declaration. Reaction::createInstance (0x7100ec0138) stores the
// singleton at 0x71026064c0; its 0x180-byte allocation and members remain unrecovered.
class Reaction {
public:
    static Reaction* instance() { return sInstance; }
    static Reaction* sInstance;
    // Surface raycast/XLink update called by GolemRootBase::calc_; declaration only.
    void sub_7100EC29D0(Actor* actor);
};
}  // namespace ksys::act
