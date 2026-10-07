#pragma once

#include <heap/seadHeap.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Event/evtEventFlow.h"

namespace ksys::evt {

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

private:
    /* 0x08 */ void* _8 = nullptr;
    /* 0x10 */ u16 _10;
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

private:
    u8 _1c[0x3e0 - 0x1c];
};
KSYS_CHECK_SIZE_NX150(S7EventFlow, 0x3e0);

}  // namespace ksys::evt
