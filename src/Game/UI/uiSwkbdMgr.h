#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace uking::ui {

// Placeholder declaration (names from the CSV: SwkbdMgr::createInstance 0x71009857f0 and show / x / x_0 /
// x_1 at 0x71009859c8-0x7100985ca8; instance pointer at 0x71025d7d00; the namespace is a guess, as for
// UiShopMgr next to it). The software keyboard manager; only what NPCNameHorse::calc_ uses is declared.
// TODO: incomplete.
class SwkbdMgr {
    u8 _0[0x10];
    SEAD_SINGLETON_DISPOSER(SwkbdMgr)
    SwkbdMgr();
    ~SwkbdMgr();

public:
    // 0x71009859c8 (declared only).
    void show(s32 type, bool clear_input);
    // 0x7100985c54 (declared only): the keyboard was confirmed.
    bool x() const;
    // 0x7100985ca8 (declared only): reads the entered text.
    void x_0();
    // 0x7100985c84: the state field compares equal to the cancel state (0x29f).
    bool x_1() const;
};

}  // namespace uking::ui
