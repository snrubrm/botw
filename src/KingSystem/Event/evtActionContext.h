#pragma once

#include <basis/seadTypes.h>

namespace evfl {
struct ActionArg;
}

namespace ksys::act {
class BaseProcLink;
}

namespace ksys::evt {

// Per-action context of the event system (CSV evt::ActionContext; ctor 0x7100da7b1c). `mStatus` is a small
// state (0 = idle ... 8). Only the members used so far are declared.
class ActionContext {
public:
    // 0x7100da546c / 0x7100da5478 / 0x7100da5484 (CSV setStatus2 / setStatus1 / setStatus1_0; the last two are
    // identical)
    // (the argument is passed by ActionBase::m4/m5/m6 and ignored; evfl::ActionArg is a guess)
    void setStatus2(const evfl::ActionArg& arg);
    void setStatus1(const evfl::ActionArg& arg);
    void setStatus1_0(const evfl::ActionArg& arg);
    // 0x7100da56b8
    void reset();
    // 0x7100da5490 / 0x7100da54e0 / 0x7100da56c4 (CSV statusStuff / statusStuff_0 / statusStuff_1)
    // (the bool is passed by the callers -- 0 in ActionBase::m4 / play, 1 in x / Action::x_0 -- and ignored)
    bool statusStuff(bool);
    bool statusStuff_0();
    void statusStuff_1();
    // 0x7100da5678 (CSV x_0)
    void x_0();
    // 0x7100da5708 (CSV statusStuff_2)
    void statusStuff_2();
    // 0x7100da5680 (CSV x_1)
    void x_1();
    // 0x7100da5360 (CSV x_3): declaration only (called with the actor's BaseProcLink)
    void x_3(act::BaseProcLink* link);
    // 0x7100da53e4 (CSV unnamed; placeholder name): like x_3 with status 1 / message 0x800008
    void sub_7100DA53E4(act::BaseProcLink* link);

    /* 0x0 */ s32 mStatus;
    u8 _4[0x4c - 4];
    /* 0x4c */ s32 mStatus2;
    u8 _50[0xa50 - 0x50];
    /* 0xa50 */ s32 _a50;
    u8 _a54[0xaf4 - 0xa54];
    /* 0xaf4 */ u16 _af4;
};

}  // namespace ksys::evt
