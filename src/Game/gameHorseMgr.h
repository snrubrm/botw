#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <container/seadSafeArray.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/GameData/gdtFlagHandle.h"

namespace ksys::act {
class Actor;
class ActorConstDataAccess;
}

namespace uking {

namespace act {
// 0x7100e6eaac (declaration only; CreateObjectsOfOwnedHorse::calc_): a check of the horse actor.
bool sub_7100E6EAAC(const ksys::act::ActorConstDataAccess& accessor);
}  // namespace act

// Placeholder declaration (name from the CSV: HorseMgr::createInstance 0x7100e81fb0, ctor
// 0x7100e821e4, postCalc 0x7100e8789c, createHorse, ...; instance pointer at 0x7102603c90; namespace
// is a guess). The manager of the owned horse; only what the AI actions use is declared.
// TODO: incomplete.
class HorseMgr {
    SEAD_SINGLETON_DISPOSER(HorseMgr)
    HorseMgr();
    ~HorseMgr();

public:
    // Placeholder (bits of _228; callers convert through the stack like a SEAD_ENUM). _0: the game data
    // handles are initialised; _9 / _10: set by sub_7100E8612C (a horse was found / none).
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10)

    // Placeholder SEAD_ENUM (the HorseUnit RiddenAnimalType: 1 default, 3-9 seen; the queries convert it through the
    // stack and the original keeps it in an 8-aligned slot, which a plain s32 does not reproduce).
    SEAD_ENUM(RiddenAnimalType, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9)

    // Inline-only in the original (names are guesses): a by-value Flag parameter reproduces the shared stack slot of
    // the temporaries and the ldr/str round trip; `(1 << flag) | bits` (mask first) gives the original's operand order
    // for the orr (sub_7100E86D44 matches), isOnBit still has the `and` operands swapped.
    bool isFlagOn(Flag flag) const { return _228.isOnBit(flag); }
    void setFlagOn(Flag flag) { _228.setDirect((1 << flag) | _228.getDirect()); }

    // One horse record of the game data (the Horse_* flags are arrays of 5: the owned horses; the DeadHorse_*
    // flags the dead ones). Names of the fields are guesses from the flag names the readers use
    // (sub_7100E854EC reads Horse_*, sub_7100E89B20 reads DeadHorse_*); the cleared defaults are the
    // original's stack initialiser (x_3, sub_7100E8883C, sub_7100E8612C build it the same way).
    struct HorseData {
        /* 0x00 */ const char* actorName = sead::SafeString::cEmptyString.cstr();
        /* 0x08 */ const char* userName = sead::SafeString::cEmptyString.cstr();
        /* 0x10 */ const char* reinsName = sead::SafeString::cEmptyString.cstr();
        /* 0x18 */ const char* saddleName = sead::SafeString::cEmptyString.cstr();
        /* 0x20 */ const char* maneName = sead::SafeString::cEmptyString.cstr();
        /* 0x28 */ const char* amiiboUidHash = sead::SafeString::cEmptyString.cstr();
        /* 0x30 */ f32 familiarity = -1.0f;
        /* 0x34 */ s32 collarType = -1;
        /* 0x38 */ s32 footType = -1;
        /* 0x3c */ s32 rideTimeSec = 0;
        /* 0x40 */ s32 deadCause = -1;
        /* 0x44 */ bool familiarityChecked = false;
    };
    static_assert(sizeof(HorseData) == 0x48);

    // 0x7100e854ec (declaration only): reads horse `index` (the Horse_* flags) into `data`.
    bool sub_7100E854EC(HorseData* data, s32 index);
    // 0x7100e8533c (CSV HorseMgr::x; declaration only): writes `data` to the Horse_* flags of horse `index`.
    void sub_7100E8533C(HorseData* data, s32 index);
    // 0x7100e89b20 (declaration only; no `this`): reads dead horse `index` (the DeadHorse_* flags) into `data`.
    static bool sub_7100E89B20(HorseData* data, s32 index);
    // 0x7100e88a08 (declaration only): writes `data` to the DeadHorse_* flags of dead horse `index`.
    void sub_7100E88A08(HorseData* data, s32 index);
    // 0x7100e86340 (declaration only): picks the horse to use out of the five records `data` (writes its index).
    bool sub_7100E86340(HorseData* data, s32* index);

    // 0x7100e828d8 (CSV x_3; lane4 s45, name is a guess): removes the invalid horse records from the game
    // data (moving the valid ones up, fixing the selected index) and returns the number of valid ones
    // (5 if the game data is not initialised yet).
    s32 getNumRegisteredHorses();
    // 0x7100e8883c (name is a guess): the same for the dead horses (no selected index, no lock).
    s32 getNumDeadHorsesRegistered();
    // 0x7100e87668 (name is a guess): the Horse_IsFamiliarityChecked flag of the selected horse.
    bool isSelectedHorseFamiliarityChecked();
    // 0x7100e8612c (name is a guess): finds the selected / owned horse and returns its RiddenAnimalType in
    // `type` (1 if there is none); returns the selected index (-1 if none).
    s32 sub_7100E8612C(RiddenAnimalType* type);

    // 0x7100e88e18 (CSV HorseMgr::isLinkedToActor) / 0x7100e88bcc (CSV HorseMgr::setRiddenHorseMaybe; declared
    // only; RideableHorse::m42 / m43 pass null).
    bool isLinkedToActor(ksys::act::Actor* actor);
    // 0x7100e84ab8 (CSV HorseMgr::__auto2; declared only): whether the link at +0x20 (the owned horse) is `actor`.
    bool sub_7100E84AB8(ksys::act::Actor* actor);
    void setRiddenHorseMaybe(ksys::act::Actor* actor);
    // 0x7100e85334 (CSV HorseMgr::__auto0): whether `link` is the owned horse's link.
    bool sub_7100E85334(const ksys::act::BaseProcLink& link) const;
    // 0x7100e8527c (declaration only; NPCRegisterHorse / NPCRegisterAndReceiveHorse): registers
    // the horse `link` under `name`.
    bool sub_7100E8527C(ksys::act::BaseProcLink* link, const sead::SafeString& name, bool a3);

    // 0x7100e857cc (declaration only, placeholder signature): used by NPCReleaseHorse with
    // (Horse_SelectedIndex, true, false, -1).
    void sub_7100E857CC(s32 index, bool a2, bool a3, s32 a4);
    // 0x7100e86cf4 / 0x7100e86d44 (declaration only; WaitWhileCreatingOwnedHorse): whether the horse
    // is still being created / marks it done.
    bool sub_7100E86CF4();
    bool sub_7100E86D44();
    // 0x7100e87340 / 0x7100e87424 / 0x7100e87508 (declarations only; CreateObjectsOfOwnedHorse::enter_):
    // create the mane / reins / saddle actor with the given name.
    // Return whether the owned horse exists (they then make it ready: sub_7100E6E98C(on = true) + the name setter).
    bool sub_7100E87340(const sead::SafeString& name, sead::Heap* heap);
    bool sub_7100E87424(const sead::SafeString& name, sead::Heap* heap);
    bool sub_7100E87508(const sead::SafeString& name, sead::Heap* heap);
    // 0x7100e873bc / 0x7100e874a0 / 0x7100e87584: the same with sub_7100E6E98C(on = false) and no result.
    void sub_7100E873BC(const sead::SafeString& name, sead::Heap* heap);
    void sub_7100E874A0(const sead::SafeString& name, sead::Heap* heap);
    void sub_7100E87584(const sead::SafeString& name, sead::Heap* heap);
    // 0x7100e875ec (declaration only; CreateObjectsOfOwnedHorse::leave_).
    bool sub_7100E875EC();
    // 0x7100e87710 (declaration only; SetHorseFamiliarityPassedFlag): sets a flag if the owned horse exists.
    bool sub_7100E87710();
    // 0x7100e85bc0 (declaration only; NPCReceiveHorse).
    void sub_7100E85BC0();

    /* 0x20 */ ksys::act::BaseProcLink mOwnedHorse;
    /* 0x30 */ ksys::act::BaseProcLink _30;  // the horse being registered / received (NPCRegisterHorse)
    u8 _40[0x20];
    /* 0x60 */ ksys::act::BaseProcLink _60;  // RideHorseForEventAction::calc_
    u8 _70[0x80 - 0x70];
    /* 0x80 */ ksys::act::BaseProcHandle _80;  // the owned horse being created (WaitWhileCreatingOwnedHorse)
    u8 _90[0xd0 - 0x90];
    /* 0x0d0 */ s32 _d0;  // the selected horse (-1: none)
    u8 _d4[0x19c - 0xd4];
    /* 0x19c */ ksys::gdt::FlagHandle _19c;  // Horse_Familiarity
    /* 0x1a0 */ ksys::gdt::FlagHandle _1a0;  // Horse_ActiveIndex
    /* 0x1a4 */ ksys::gdt::FlagHandle _1a4;  // Horse_ActorName
    u8 _1a8[0x228 - 0x1a8];
    /* 0x228 */ sead::BitFlag16 _228;
    u8 _22a[0x230 - 0x22a];
    /* 0x230 */ sead::CriticalSection _230;
};

}  // namespace uking

// 0x7100e86d84 (CSV name; declared only, class unknown): resurrects the horse with the given index; returns the new
// index, or a negative number on failure.
s32 resurrectHorseStuff(uking::HorseMgr* mgr, s32 index);
