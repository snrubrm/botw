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
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace ksys::act {
class Actor;
}

namespace ksys::map {
struct ObjectLinkArray;
}

namespace uking::act {
class PlayerBase;
}

namespace uking {

// StasisMgr's secondary interface at +0x10, stored in ActorSystem at +0xc8.
// The placeholder name refers to its secondary vtable; the interface has five slots and no
// virtual destructor. The StasisMgr constructor installs this interface in ActorSystem.
class Unk_710243c7c8 {
public:
    // Handles the stasis messages 0x3000003 - 0x3000006 for `actor` (0 if not handled).
    virtual s32 m0(ksys::act::Actor* actor, const ksys::Message* message) = 0;
    // void: StasisMgr's override (0x71006812d8) returns whatever the transceiver call left.
    virtual void sendMessage(ksys::act::Actor* actor, ksys::MessageType type,
                             bool on_processing_thread) = 0;
    virtual s32 m2(const sead::Matrix34f& mtx) = 0;
    virtual s32 m3(const sead::Matrix34f& mtx, s32 index) = 0;
    virtual xlink2::HandleELink* m4(ksys::act::Actor* actor) = 0;
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
    s32 m0(ksys::act::Actor* actor, const ksys::Message* message) override;
    // Emits "BitaLocked_Trace" into a free effect slot and places it at `mtx`; returns the slot.
    s32 m2(const sead::Matrix34f& mtx) override;
    s32 m3(const sead::Matrix34f& mtx, s32 index) override;
    xlink2::HandleELink* m4(ksys::act::Actor* actor) override;
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
        // m0 kills the ELink event when the target is released; 0x710067ffbc tests both handles with
        // Unk_71012419b4::sub_7101241B6C (0x7101241b6c called on entry + 0x2a8).
        /* 0x2a8 */ Unk_71012419b4 _2a8;
        // m4 returns its address for the entry linked to the actor.
        /* 0x2c8 */ xlink2::HandleELink _2c8;
        /* 0x2d8 */ sead::CriticalSection mCS;
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x318);

    // 0x710067f9a8 (CSV StasisMgr::__auto0; placeholder name): clears the state, the entries (link,
    // effect, damage records) and the effects.
    void sub_710067F9A8();
    // 0x710067fb80 (CSV name): kills the effects of targets whose map object is being revived, updates
    // the others' effects, counts the stasis timer _48 down (unless the active event flow has
    // byte3FlagIsSet) and sends the countdown messages (0x300000a / 0x300000b, 0x3000004 at zero).
    void updateStasisCountdownStuff();
    // 0x710067ffbc (placeholder name; does not use `this`: the caller leaves x0 unset): places the
    // target's effects at the actor (scale from DamageManagerUnk220::sub_71006D9B30) and fades the
    // first one out while the actor has flag 18.
    void sub_710067FFBC(Entry* entry);
    // 0x7100680368 (placeholder name): releases every target (message 0x3000004), kills their
    // effects and resets the countdown state from the player's stop timer reload time.
    void sub_7100680368(bool on_processing_thread);
    // 0x7100680660 (CSV StasisMgr::__auto1; placeholder name): per-frame update: the countdown, then (while
    // the stasis rune is aimed, _40) links the RuneMgr target candidate in _32e0 (messages 0x3000005 /
    // 0x3000006) and stasises it on input; releases _32e0 otherwise.
    void sub_7100680660(act::PlayerBase* player);
    // 0x7100680920 (placeholder name): asks `actor` (or, while _42 is set and the actor is already
    // stasised, the actor in the first entry) to leave / enter stasis through messages 0x3000003 /
    // 0x3000004.
    void sub_7100680920(ksys::act::Actor* actor);
    // 0x7100680ac8 (placeholder name; does not use `this`): links `entry` to `proc`, clears its
    // damage records and kills its first effect.
    void sub_7100680AC8(Entry* entry, ksys::act::BaseProc* proc);
    // 0x7100681368 (placeholder name; m0 passes the target's map object links to self and constraint links):
    // sends `type` to the dynamic actors on the constraint links (Fixed .. RackAndPinion, except Pulley and
    // CogWheel) other than ropes; for types other than 0x3000005 / 0x3000006 only to actors whose
    // ActorFlag2 bit 6 differs from `flag`.
    void sub_7100681368(ksys::map::ObjectLinkArray* links, ksys::MessageType type, bool flag);
    // 0x71006815fc (CSV StasisMgr::__auto3; placeholder name; called by DamageManagerUnk220 0x71006d9c34 for a
    // new stasis hit): sets xlink property 4 of the reaction actor to the actor's stasis blow power ratio and
    // re-emits "BitaLocked_Vector" for the entry whose damage records are `damage`.
    void sub_71006815FC(ksys::act::Actor* actor, act::DamageManagerUnk220* damage);
    // 0x7100681570 (CSV StasisMgr::__auto2): _44 * _58, at least 0.
    f32 sub_7100681570() const;
    // 0x7100681588 (CSV StasisMgr::__auto5): the damage records of the entry linked to `actor`.
    act::DamageManagerUnk220* sub_7100681588(ksys::act::Actor* actor);

    // 0x7100681b90 / 0x7100681b98 / 0x7100681ba0 (placeholder names): constants read by the stasis damage
    // records (DamageManagerUnk220, 0x71006d9c34 / 0x71006da02c): 2.0, 1, 0.7.
    static f32 sub_7100681B90();
    static s32 sub_7100681B98();
    static f32 sub_7100681BA0();

    /* 0x040 */ u8 _40 = 0;
    /* 0x041 */ bool _41 = false;
    /* 0x042 */ bool _42 = false;
    /* 0x043 */ u8 _43 = 0;
    /* 0x044 */ f32 _44 = 0;
    /* 0x048 */ f32 _48 = 0;
    /* 0x04c */ f32 _4c = 0;
    /* 0x050 */ s32 _50;  // compared with the timer _48 truncated to an int
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
