#pragma once

#include <aal/aalArbiter.h>
#include <aal/aalHandle.h>
#include <prim/seadDelegate.h>
#include <container/seadObjList.h>
#include <container/seadSafeArray.h>
#include <thread/seadCriticalSection.h>
#include <xlink2/xlink2IEventCallbackSLink.h>
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::snd {

// Vtable 0x710251aef0 (no RTTI; 0x1c8 bytes). Ducks with one ducker of the DuckingMgr while the sounds added to it
// play: calc() takes the loudest new sound and starts the ducker with a volume computed from the ducker's
// AttenuationParam. Twelve of them sit in Unk_710251af10.
class Unk_710251aef0 {
public:
    struct Item {
        Item() {}

        aal::Handle handle;
        // Set once the sound has been counted by calc().
        bool done = false;
        f32 value = 0.0f;
    };

    virtual ~Unk_710251aef0();

    // 0x71012c1fa0: adds the sound `handle` (`value` is its volume for AttenuationParam::_2).
    void add(const aal::Handle& handle, f32 value);
    // 0x71012c2054: drops the sounds that stopped and updates the ducker.
    void calc();

    /* 0x008 */ sead::FixedObjList<Item, 8> mItems;
    /* 0x178 */ DuckingMgr::Ducker* mDucker = nullptr;
    /* 0x180 */ sead::CriticalSection mCS;
    // Set while there are sounds to look at (calc() runs only while it is set).
    /* 0x1c0 */ bool mActive = false;
};
KSYS_CHECK_SIZE_NX150(Unk_710251aef0, 0x1c8);

// Vtable 0x710251af10 (no RTTI; SoundMgr::_88, constructed by 0x71011fab7c): one Unk_710251aef0 for each of the
// duckers cExplosion .. cEnemyImpact.
class Unk_710251af10 {
public:
    Unk_710251af10();
    virtual ~Unk_710251af10() = default;

    // 0x71012c2554: updates the active entries.
    void calc();

    /* 0x8 */ sead::SafeArray<Unk_710251aef0, 12> mEntries;
};
KSYS_CHECK_SIZE_NX150(Unk_710251af10, 0x1568);

// The second base of Unk_710251afc8 (only a virtual destructor; its vtable in that group is 0x710251aff8).
// Unk_710251b730 and Unk_710251b7a0 have the same second base.
class Unk_710251aff8 {
public:
    virtual ~Unk_710251aff8() = default;
};

// Vtable 0x710251afc8 (no RTTI; 0x88 bytes): the emitter allocate callback that Unk_710251af30 gives the
// aal::Arbiter. Keeps a list of the emitters that the arbiter creates on its own heap.
class Unk_710251afc8 : public aal::Arbiter::IEmitterAllocateCallback, public Unk_710251aff8 {
public:
    struct Item {
        aal::Emitter* emitter = nullptr;
        // aal::Arbiter::get_8() when the emitter was created.
        s32 _8 = 0;
    };

    Unk_710251afc8();
    ~Unk_710251afc8() override;
    // 0x71012c2ef4 (declared only: it reads the private emitter heap of aal::Arbiter).
    void onAllocEmitter(sead::Heap* heap, aal::Emitter* emitter, const sead::SafeString& name) override;
    void onFreeEmitter(aal::Emitter* emitter) override;

    // 0x71012c2e88: allocates the list of 400 emitters.
    void init(sead::Heap* heap);

    /* 0x10 */ u32 _10 = 0;
    /* 0x18 */ sead::ObjList<Item> mEmitters;
    /* 0x48 */ sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(Unk_710251afc8, 0x88);

// The second base of Unk_710251af30 (vtable 0x710251af58 in its group: two empty virtuals, no destructor).
class Unk_710251af58 {
public:
    virtual void m0() {}
    virtual void m1() {}
};

// The primary base of Unk_710251b730 and Unk_710251b7a0: six virtuals (slots 0 and 5 have the same bodies in
// both), then the destructor. Not modelled further.
class Unk_710251b730Base {
public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual ~Unk_710251b730Base();
};

// Vtable 0x710251b730 (0x10 bytes; SoundMgr::_70->_18): an xlink2 SLink event callback for the sound events of
// actors (expression sounds, voice groups, interior sounds and loop re-emits).
// lib/xlink2 declares replaceAssetInfo before soundPlayed; in the original vtable soundPlayed is slot 4. Until
// that is fixed, the constructor and the destructors (0x71012ceb94 .. 0x71012cebb8, which emit the vtable) stay
// declared only.
class Unk_710251b730 : public xlink2::IEventCallbackSLink, public Unk_710251aff8 {
public:
    Unk_710251b730();
    ~Unk_710251b730() override;

    // 0x71012cebc4: forwards the event to ExpressionSoundCtrl for player actors and XLinks with _cc bit 6.
    void eventActivated(const EventArg& arg) override;
    // 0x71012cec40: 1 when the XLink allows it and the asset's group name contains "Voice".
    u32 soundPrePlay(const EventArg& arg) override;
    // 0x71012cecc8 (declared only: it uses EventArg::pHandle as an aal::Handle, lib/xlink2 types it as
    // HandleSLink).
    void eventCalced(const EventArg& arg) override;
    // 0x71012ced14: asks looping assets with custom param 3 to re-emit (XLink _cc bit 7).
    void soundPlayed(const EventArg& arg) override;

    // 0x71012cebc0 (empty in the release build).
    void sub_71012CEBC0(sead::Heap* heap);
};
KSYS_CHECK_SIZE_NX150(Unk_710251b730, 0x10);

// Vtable 0x710251b7a0 (0x358 bytes; constructor 0x71012cedec, declared only). Slot 3 (0x71012cf2c8) adds sounds to
// the attenuation entries of SoundMgr::_88. Slots 0 .. 5 are not modelled.
class Unk_710251b7a0 : public Unk_710251b730Base, public Unk_710251aff8 {
public:
    Unk_710251b7a0();
    ~Unk_710251b7a0() override;

    // 0x71012cee90 (empty in the release build).
    void sub_71012CEE90(sead::Heap* heap);
    // 0x71012cee94
    void sub_71012CEE94();

    u8 _10[0x358 - 0x10];
};
KSYS_CHECK_SIZE_NX150(Unk_710251b7a0, 0x358);

// Vtable 0x710251af30 (no RTTI; 0x50 bytes): SoundMgr::_70, created by 0x71011fab7c. Owns Unk_710251b7a0,
// Unk_710251b730 and the emitter allocate callback of the arbiter.
// The primary base is a guess: a base with only a virtual destructor, as in the other classes of this group.
class Unk_710251af30 : public Unk_710251aff8, public Unk_710251af58 {
public:
    // 0x71012c2870 (declared only: the argument type of the delegate at +0x28 is unknown).
    Unk_710251af30();
    ~Unk_710251af30() override;
    virtual void m2() {}

    // 0x71012c29c8
    void init(sead::Heap* heap);
    // 0x71012c2a10: `callback_heap` is null when the arbiter callback is not needed.
    void init2(sead::Heap* heap, sead::Heap* callback_heap);

    /* 0x10 */ Unk_710251b7a0* _10;
    /* 0x18 */ Unk_710251b730* _18;
    /* 0x20 */ Unk_710251afc8* _20;
    // A sead::Delegate1<Unk_710251af30, T> (vtable 0x710251af78; invoke 0x71012c2ac4); T is unknown.
    /* 0x28 */ u8 _28[0x20];
    /* 0x48 */ u32 _48;
};
KSYS_CHECK_SIZE_NX150(Unk_710251af30, 0x50);

}  // namespace ksys::snd
