#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <container/seadPtrArray.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/gameUnk_710243c330.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

// Placeholder name (ctor 0x7100903948 / dtor 0x7100903b38): 16 actor links with an id.
class Unk_7100903948 {
public:
    Unk_7100903948();
    ~Unk_7100903948();
    struct Slot {
        s32 id = -1;
        ksys::act::BaseProcLink link;
    };
    Slot slots[16];
};
KSYS_CHECK_SIZE_NX150(Unk_7100903948, 0x180);

// A named actor link (placeholder name; layout from the constructor 0x7100903620: the destructor resets `link`).
struct Unk_GameSceneSubsys14Entry {
    sead::FixedSafeString<256> name;
    s64 id = -1;
    ksys::act::BaseProcLink link;
};
KSYS_CHECK_SIZE_NX150(Unk_GameSceneSubsys14Entry, 0x130);

// Vtable 0x7102473580 (GOT 0x2593a58; D1 0x7100903c24, D0 0x7100904f74, m2 0x710090325c = message handler, m3 is
// an empty function). Message listener embedded at GameSceneSubsys14 + 0x1c8.
class Unk_7102473580 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;

    u32 _34;
    bool _38 = true;
    Unk_GameSceneSubsys14Entry _40;
};
KSYS_CHECK_SIZE_NX150(Unk_7102473580, 0x170);

// Vtable 0x71024735b0 (GOT 0x2593a60; D1 0x7100903bd0, D0 0x7100904fd4, m2 0x7100903408). Message listener embedded at
// GameSceneSubsys14 + 0x340.
class Unk_71024735b0 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;

    u32 _34;
    bool _38 = true;
    u32 _3c;
    s32 _40 = -1;
    ksys::act::BaseProcLink _48;
    s32 _58 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71024735b0, 0x60);

// Name from the CSV (GameSceneSubsys14::createInstance 0x7100903598, ctor 0x7100903620, init,
// initCurrentLocation, postCalc, x_N, ...; instance pointer at 0x71025d1760). A polymorphic sead
// singleton. The transceiver receives area-location messages from the AI code;
// the recovered actor-link slots and fixed arrays support slot removal and pruning.
// TODO: incomplete (layout and namespace unknown; the CSV name has no namespace).
// Bases (from the vtable groups at +0, +8 and +0x10, same as IceBlockMgr): the Rx and Tx handlers of the
// transceiver at +0x170 (m2 = handleMessage) and the interface Unk_710243c330. The SEAD_SINGLETON_DISPOSER macro (and
// its 0x20-byte disposer buffer) sits at +0x18 in the original, from createInstance's stores.
class GameSceneSubsys14 : public ksys::ActorMessageTransceiver::IHandler, public uking::Unk_710243c330 {
    SEAD_SINGLETON_DISPOSER(GameSceneSubsys14)
    GameSceneSubsys14();
    ~GameSceneSubsys14() override;

public:
    // 0x7100904834 (CSV GameSceneSubsys14::m2; declared only).
    int handleMessage(const ksys::Message& message) override;

    void init();
    // Original location setup at 0x7100903d00; body remains declared only.
    void initCurrentLocation();
    // 0x7100903fbc (CSV GameSceneSubsys14::postCalc; declared only).
    void postCalc();
    void sub_7100904DD4(const Unk_7100903948::Slot& slot);
    bool sub_7100904704();
    // 0x7100904ed4-0x7100904f68: out-of-line flag getters (`__auto*` in the CSV; bit meanings unknown).
    bool sub_7100904ED4() const;
    bool sub_7100904EE0() const;
    bool sub_7100904EF8() const;
    bool sub_7100904F04() const;
    bool sub_7100904F10() const;
    bool sub_7100904F1C() const;
    bool sub_7100904F28() const;
    bool sub_7100904F34() const;
    bool sub_7100904F40() const;
    bool sub_7100904F4C() const;
    bool sub_7100904F68() const;

    Unk_GameSceneSubsys14Entry _38;
    u32 _168 = 0;
    u32 _16c = 0;
    ksys::ActorMessageTransceiver mTransceiver{*this};
    Unk_7102473580 _1c8;
    u32 _338 = 0;
    Unk_71024735b0 _340;
    Unk_GameSceneSubsys14Entry mEntries[10];
    sead::FixedPtrArray<Unk_GameSceneSubsys14Entry, 10> _f80;
    sead::FixedPtrArray<Unk_GameSceneSubsys14Entry, 10> _fe0;
    Unk_7100903948 _1040;
    // Constructor 0x7100903620 sets 16-entry buffers at +0x11d0 and +0x1260.
    sead::FixedPtrArray<Unk_7100903948::Slot, 16> mActiveSlots;
    sead::FixedPtrArray<Unk_7100903948::Slot, 16> mFreeSlots;
    bool _12e0 = false;
    bool mSlotsChanged = false;
};
