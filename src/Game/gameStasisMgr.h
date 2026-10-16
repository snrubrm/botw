#pragma once

#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <thread/seadCriticalSection.h>
#include <xlink2/xlink2HandleELink.h>
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/gameUnk_710243c330.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/ActorMessageTransceiver.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace uking {

// StasisMgr's secondary interface at +0x10, stored in ActorSystem at +0xc8.
// The placeholder name refers to its secondary vtable; the interface has five slots and no
// virtual destructor. The StasisMgr constructor installs this interface in ActorSystem.
class Unk_710243c7c8 {
public:
    virtual s32 m0(ksys::act::Actor* actor, void* request) = 0;
    // void: StasisMgr's override (0x71006812d8) returns whatever the transceiver call left.
    virtual void sendMessage(ksys::act::Actor* actor, ksys::MessageType type,
                             bool on_processing_thread) = 0;
    virtual s32 m2(const sead::Matrix34f& mtx) = 0;
    virtual s32 m3(const sead::Matrix34f& mtx, s32 index) = 0;
    virtual void* m4(ksys::act::Actor* actor) = 0;
};

// Name from the CSV (StasisMgr::createInstance 0x710067f3a8, ctor 0x710067f430). vtable 0x710243c748
// (primary: D2 0x710067f564, D0 0x710067f848, handleMessage, then the Unk_710243c7c8 overrides and
// handleAck); the ctor installs the Unk_710243c7c8 base in ActorSystem::_c8.
class StasisMgr : public ksys::ActorMessageTransceiver::IHandler,
                  public Unk_710243c7c8,
                  public Unk_710243c330 {
    SEAD_SINGLETON_DISPOSER(StasisMgr)
    StasisMgr();
    ~StasisMgr() override;

public:
    // 0x7100681bac.
    int handleMessage(const ksys::Message* message) override { return 1; }
    // Primary slots 3-6 (0x7100680bb4, 0x71006818fc, 0x7100681a94, 0x71006809f0).
    s32 m0(ksys::act::Actor* actor, void* request) override;
    // Emits "BitaLocked_Trace" into a free effect slot and places it at `mtx`; returns the slot.
    s32 m2(const sead::Matrix34f& mtx) override;
    s32 m3(const sead::Matrix34f& mtx, s32 index) override;
    void* m4(ksys::act::Actor* actor) override;
    // 0x7100681bb4 (primary slot 7; the +8 vtable has its own empty copy 0x7100681bb8).
    void handleAck(const ksys::MessageAck& ack) override {}
    // 0x71006812d8 (primary slot 8).
    void sendMessage(ksys::act::Actor* actor, ksys::MessageType type,
                     bool on_processing_thread) override;

    // One stasis target (0x318 bytes). The array dtor 0x710067f5cc destroys the critical section,
    // then resets the link, from the last entry down.
    struct Entry {
        /* 0x000 */ ksys::act::BaseProcLink link;
        /* 0x010 */ act::DamageManagerUnk220 damage;
        // m0 kills _2a8 when the target is released.
        /* 0x2a8 */ xlink2::HandleELink _2a8;
        /* 0x2b8 */ xlink2::HandleELink _2b8;
        // m4 returns its address for the entry linked to the actor.
        /* 0x2c8 */ xlink2::HandleELink _2c8;
        /* 0x2d8 */ sead::CriticalSection mCS;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x318);

    /* 0x040 */ u8 _40 = 0;
    /* 0x041 */ bool _41 = false;
    /* 0x042 */ bool _42 = false;
    /* 0x043 */ u8 _43 = 0;
    /* 0x044 */ f32 _44 = 0;
    /* 0x048 */ f32 _48 = 0;
    /* 0x04c */ f32 _4c = 0;
    /* 0x050 */ f32 _50;
    /* 0x054 */ f32 _54 = 1.0f;
    /* 0x058 */ f32 _58 = 1.0f;
    /* 0x060 */ sead::SafeArray<Entry, 16> mEntries{};
    // "BitaLocked_Trace" effects (m2 / m3).
    /* 0x31e0 */ sead::SafeArray<xlink2::HandleELink, 16> mEffects{};
    /* 0x32e0 */ ksys::act::BaseProcLink _32e0;
    /* 0x32f0 */ ksys::ActorMessageTransceiver mTransceiver{*this};
    // Actors registered by m0 for messages 0x3000005 / 0x3000006.
    /* 0x3348 */ sead::FixedPtrArray<ksys::act::Actor, 64> _3348;
    /* 0x3558 */ sead::FixedPtrArray<ksys::act::Actor, 64> _3558;
};
KSYS_CHECK_SIZE_NX150(StasisMgr, 0x3768);

}  // namespace uking
