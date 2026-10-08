#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace evfl {
struct ActionArg;
}

namespace ksys::act {
class Actor;
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
    // Takes the actor (ignored; the DemoRootAI d6300C helper passes it -- the mov x1 before the bl
    // proves the argument exists in the original).
    void statusStuff_1(act::Actor* actor);
    // 0x7100da5678 (CSV x_0)
    void x_0();
    // 0x7100da5708 (CSV statusStuff_2)
    void statusStuff_2();
    // 0x7100da5680 (CSV x_1)
    void x_1();
    // 0x7100da572c (CSV unnamed; the missing x_2): the same body as x_1
    void x_2();
    // 0x7100da5360 (CSV x_3): declaration only (called with the actor's BaseProcLink)
    void x_3(act::BaseProcLink* link);
    // 0x7100da53e4 (CSV unnamed; placeholder name): like x_3 with status 1 / message 0x800008
    void sub_7100DA53E4(act::BaseProcLink* link);
    // 0x7100da7b1c (CSV unnamed): construct the strings and the request nodes.
    ActionContext();
    // 0x7100da5528 (CSV unnamed): fill the context from a name, an action argument and a value.
    void init(const sead::SafeString& name, const evfl::ActionArg& arg, s32 a3);

    // One entry of the +0x50 request-node table (0x50 bytes). The ctor's rolled loop
    // constructs the link at +0x8 (x0 = elem + 0x58 - 0x50), stores -1 at +0x28 and
    // zeroes +0x30/+0x38, leaving +0x0 and +0x18..+0x28 untouched. The link call sits
    // inside the loop (not in an unrolled mem-init), so the node has a user-provided
    // inline ctor carrying the call plus the stores; that keeps the 32-element
    // mem-init construction rolled where a trivial node fully unrolls.
    struct Node {
        Node() {
            _28 = -1;
            _30 = 0;
            _38 = 0;
        }
        void* _0;
        act::BaseProcLink _8;
        u8 _18[0x10];
        s64 _28;
        u64 _30;
        u64 _38;
        u8 _40[0x10];
    };

    /* 0x0 */ s32 mStatus;
    u8 _4[0x8 - 0x4];
    /* 0x8 */ sead::FixedSafeString<0x20> _8;
    /* 0x40 */ s32 _40;
    /* 0x44 */ f32 _44;
    /* 0x48 */ s32 _48;
    /* 0x4c */ s32 mStatus2;
    /* 0x50 */ Node _50[32];
    /* 0xa50 */ s32 _a50 = 0;
    u8 _a54[0xa58 - 0xa54];
    // Next context in the DemoRootAI release chain (sub_7100D630AC walks and unlinks these).
    /* 0xa58 */ ActionContext* _a58;
    /* 0xa60 */ sead::FixedSafeString<0x30> _a60;
    /* 0xaa8 */ sead::FixedSafeString<0x30> _aa8;
    /* 0xaf0 */ s32 _af0;
    /* 0xaf4 */ u16 _af4 = 0;
};
static_assert(sizeof(ActionContext) == 0xaf8);

}  // namespace ksys::evt

