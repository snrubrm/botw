#pragma once

#include <heap/seadHeap.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Event/evtEventFlow.h"

namespace ksys::evt {


class S7;

// Placeholder name: the RTTI base class of S5 (the object at EventFlowActorInfo + 0x200 is cast to S5 by S7).
class S5Base {
public:
    virtual ~S5Base() = default;
    SEAD_RTTI_BASE(S5Base)
};

// CSV evt::S5 (0x18 bytes; created by ManagerDelegate::makeS5 for the event system; the constructor marks the
// EventSystem). Vtable 0x710246cb10: destructors (inline), RTTI pair.
class S5 : public S5Base {
public:
    // 0x71008af504 (CSV evt::S5::ctor)
    S5();
    ~S5() override = default;
    SEAD_RTTI_OVERRIDE(S5, S5Base)

public:
    /* 0x08 */ S7* _8 = nullptr;  // the handle that currently owns the S5
    /* 0x10 */ u8 _10;
    /* 0x11 */ u8 _11;
    /* 0x12 */ u8 _12;
};
KSYS_CHECK_SIZE_NX150(S5, 0x18);

// CSV evt::S7: the implementation base of EventFlowHandle (vtable 0x710246ca90). `mFlow` is the event flow that owns
// the handle. Bit 0 of `_14` says that the EventSystem has counted the flow (EventSystem::__auto0 / __auto1 count
// the flows by their flags).
class S7 : public EventFlowHandle {
public:
    // 0x71008add3c (CSV evt::S7::ctor): `heap` is unused.
    S7(sead::Heap* heap, EventFlowBase* flow);
    SEAD_RTTI_OVERRIDE(S7, EventFlowHandle)
    // D1 0x71008add5c (CSV evt::S7::m2), D0 0x71008addf4 (CSV evt::S7::m3)
    ~S7() override;

    void m6() override {}
    // 0x71008af664 (CSV evt::S7::m7): "not implemented"
    const char* m7() override { return "未実装"; }
    // 0x71008aeac4 (CSV evt::S7::closeFadeScreens): closes the fade screens; does not use `this`
    bool m11() override;

    // 0x71008addb0 (CSV unnamed; placeholder name): takes the flow out of the EventSystem's count
    void sub_71008ADDB0();

    // 0x71008ae2a8 (CSV evt::S7::openFadeDemoScreen) / 0x71008ae41c / 0x71008ae730 (placeholder names; none of them uses
    // `this`; defined in uiFadeScreens.cpp): open the fade demo screen / the fade screen
    void sub_71008AE2A8(bool a);
    void sub_71008AE41C(bool open_status, bool stop_at_max);
    void sub_71008AE730(bool stop_at_max);

    // 0x71008ae08c (CSV evt::S7::blockSkipForDemo102): the skip state `_10` (0: none, 1 / 4: skippable, ...): `a` says
    // that skipping is allowed, `b` selects state 4; Demo102_0 on the first launch (outside the E3 demo) blocks it
    void blockSkipForDemo102(bool a, bool b);

    // 0x71008ae1c4 (CSV evt::S7::setDemoIsPlayedFlag): for a "Demo..." event sets the game data flag IsPlayed_<event>
    void setDemoIsPlayedFlag();

    // 0x71008af278 (placeholder name): has the EventSystem count the flow (sets bit 0 of `_14`) unless it already does
    void sub_71008AF278();
    // 0x71008af2bc (placeholder name; does not use `this`): AutoDim::setEnabled
    void sub_71008AF2BC(bool enabled);
    // 0x71008af3b8 (placeholder name): the flow's S5
    S5* sub_71008AF3B8() const;
    // 0x71008af44c (placeholder name): releases the S5's current owner if it is this handle
    void sub_71008AF44C();

protected:
    /* 0x08 */ EventFlowBase* mFlow;
    /* 0x10 */ s32 _10 = 0;
    /* 0x14 */ u32 _14 = 0;
    /* 0x18 */ s32 _18 = 0;
};

// CSV evt::S7Movie (0x1c8 bytes): the handle of movie flows.
class S7Movie : public S7 {
public:
    // 0x71008b8edc (CSV evt::S7Movie::ctor)
    S7Movie(sead::Heap* heap, EventFlowBase* flow);
    SEAD_RTTI_OVERRIDE(S7Movie, S7)
    // D1 0x71008b8fc0 (CSV evt::S7Movie::m2), D0 0x71008b8fd4 (CSV evt::S7Movie::m3)
    ~S7Movie() override;

    void m4() override;
    bool m5() override;
    const char* m7() override;
    void m8(void* a1, void* a2) override {}
    void m9() override {}
    bool isPlaying() override;

    // 0x71008b9f10 (placeholder name): whether the event is one of the demos Demo143_0 (water / fire / electric
    // beast cleared), Demo143_3 (fire / electric) or Demo143_1 (electric) whose condition holds
    bool sub_71008B9F10();
    // 0x71008b9e04 (CSV evt::S7::x; it is in the S7Movie TU): starts / stops the movie flag of the S5 according to
    // sub_71008B9F10(); `a` marks the S5's `_11` while it is started
    void x(bool a);

private:
    /* 0x1c */ u32 _1c = 0;
    /* 0x20 */ s32 _20;
    /* 0x28 */ sead::FixedSafeString<0x180> _28;
    /* 0x1c0 */ bool _1c0 = false;
};
KSYS_CHECK_SIZE_NX150(S7Movie, 0x1c8);

// CSV evt::S7EventFlow (0x3e0 bytes): the handle of flowchart / timeline flows. Not decompiled.
class S7EventFlow : public S7 {
public:
    // 0x71008af920 (CSV evt::S7EventFlow::ctor; not decompiled)
    S7EventFlow(sead::Heap* heap, EventFlowBase* flow);
    SEAD_RTTI_OVERRIDE(S7EventFlow, S7)
    ~S7EventFlow() override;

    void m4() override;
    bool m5() override;
    void m6() override;
    const char* m7() override;
    void m8(void* a1, void* a2) override;
    void m9() override;
    bool isPlaying() override;
    // 0x71008afcdc (CSV evt::S7EventFlow::calc)
    bool calc();
    // 0x71008afd40 (CSV evt::S7EventFlow::calc_; not decompiled)
    u32 calc_();

private:
    /* 0x1c */ s32 _1c;
    /* 0x20 */ s32 mState;  // 3: playing
    /* 0x24 */ s32 _24;
    /* 0x28 */ s32 _28;
    /* 0x2c */ s32 _2c;
    /* 0x30 */ u64 _30;
    /* 0x38 */ s32 _38;
    /* 0x3c */ s32 _3c;
    /* 0x40 */ bool _40;
    u8 _41[7];
    /* 0x48 */ s32 _48;
    u8 _4c[0x64 - 0x4c];
    /* 0x64 */ s32 _64;
    /* 0x68 */ s32 _68;
    u8 _6c[4];
    /* 0x70 */ sead::FixedSafeString<0x180> mStatus;
    u8 _208[0x218 - 0x208];
    /* 0x218 */ sead::FixedSafeString<0x80> _218;
    /* 0x2b0 */ sead::FixedSafeString<0x80> _2b0;
    /* 0x348 */ sead::FixedSafeString<0x80> _348;
};
KSYS_CHECK_SIZE_NX150(S7EventFlow, 0x3e0);

}  // namespace ksys::evt
