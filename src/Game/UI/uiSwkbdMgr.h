#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace uking::ui {

// Placeholder declaration (names from the CSV: SwkbdMgr::createInstance 0x71009857f0 and show / x / x_0 /
// x_1 at 0x71009859c8-0x7100985ca8; instance pointer at 0x71025d7d00; the namespace is a guess, as for
// UiShopMgr next to it). The software keyboard manager; only what NPCNameHorse::calc_ uses is declared.
// Object size 0x80 (createInstance 0x71009857f0, destructor D1 / D0 0x71009858fc / 0x7100985900, disposer vtable
// 0x7102476d48, class vtable 0x7102476d68). createInstance (the constructor is inlined) is m: only the order of the
// inlined member stores differs (the original stores `_70` before the vtable pointer and `_68` / `_6c` after it).
// TODO: incomplete.
class SwkbdMgr {
    SEAD_SINGLETON_DISPOSER(SwkbdMgr)
    SwkbdMgr() = default;

public:
    virtual ~SwkbdMgr();

    // 0x71009859c8 (declared only).
    void show(s32 type, bool clear_input);
    // 0x7100985c54: the keyboard was confirmed (and some text was entered).
    bool x() const;
    // 0x7100985ca8: stores the entered text as the new name of the horse.
    void x_0();
    // 0x7100985c84: the state field compares equal to the cancel state (0x29f).
    bool x_1() const;
    const char16* sub_7100985C98() const;
    bool sub_7100985CA0() const;

    /* 0x28 */ char16 _28 = 0;  // the first character of the entered text (the buffer extends to 0x78)
    u8 _2a[0x58 - 0x2a];
    /* 0x58 */ u64 _58 = 0;
    /* 0x60 */ u64 _60 = 0;
    /* 0x68 */ s32 _68 = 0;
    /* 0x6c */ s32 _6c = 10;
    /* 0x70 */ s32 _70 = -1;
    /* 0x74 */ bool _74 = true;
    /* 0x75 */ bool _75 = true;
    u8 _76[2];
    /* 0x78 */ s32 _78;  // the result of the keyboard (0 = confirmed, low 22 bits: 0x29f = cancelled)
    u8 _7c[4];
};
KSYS_CHECK_SIZE_NX150(SwkbdMgr, 0x80);

}  // namespace uking::ui
