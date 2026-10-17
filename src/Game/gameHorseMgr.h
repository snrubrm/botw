#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace ksys::phys {
class NavMeshQuery;
}

namespace ksys::act {
class Actor;
class BaseProc;
class ActorLinkConstDataAccess;
}

namespace uking {

namespace act {
class HorseBase;
// 0x7100e6eaac (declaration only; CreateObjectsOfOwnedHorse::calc_): a check of the horse actor.
bool sub_7100E6EAAC(const ksys::act::ActorLinkConstDataAccess& accessor);
}  // namespace act

// Placeholder declaration (name from the CSV: HorseMgr::createInstance 0x7100e81fb0, ctor
// 0x7100e821e4, postCalc 0x7100e8789c, createHorse, ...; instance pointer at 0x7102603c90; namespace
// is a guess). The manager of the owned horse; only what the AI actions use is declared.
// TODO: incomplete.
class HorseMgr;

// Placeholder (ctor 0x7100e8a080; HorseMgr::_270): a navmesh query with a linked actor and a matrix.
struct Unk_7100e8a080 {
    Unk_7100e8a080();
    // 0x7100e8a0c4 (placeholder name): destroys the query and resets the link.
    void sub_7100E8A0C4();
    // 0x7100e8a100 (placeholder name): unless busy (_4c, a query, or the timer _48 running), checks horseStuff and
    // then links `proc` and restarts the timer (66); false if horseStuff fails.
    bool sub_7100E8A100(HorseMgr* mgr, ksys::act::BaseProc* proc);
    // 0x7100e8a16c (CSV horseStuff; declaration only, 664 B; does not use `this`): game data checks on the owned horse
    // of `mgr` (IsGet_PlayerStole2, IsInHyruleCastleArea, IsPlayed_Demo14x flags).
    bool horseStuff(HorseMgr* mgr);

    /* 0x00 */ ksys::phys::NavMeshQuery* mQuery = nullptr;
    /* 0x08 */ ksys::act::BaseProcLink _8;
    /* 0x18 */ sead::Matrix34f _18 = sead::Matrix34f::ident;
    /* 0x48 */ f32 _48 = 0;
    /* 0x4c */ bool _4c = false;
};
KSYS_CHECK_SIZE_NX150(Unk_7100e8a080, 0x50);

class HorseMgr {
    SEAD_SINGLETON_DISPOSER(HorseMgr)
    HorseMgr();
    ~HorseMgr();

public:
    // 0x7100E8789C: updates the owned-horse state after stage calculation.
    void postCalc();

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
    // Counterpart of setFlagOn (0x7100e89a44 clears _4 this way).
    void setFlagOff(Flag flag) { _228.setDirect(~(1 << flag) & _228.getDirect()); }

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

    // 0x7100e83a08 (CSV x_8): the same as sub_7100E854EC on buffer 0 (the regular getters, no `_40000` check).
    bool x_8(HorseData* data, s32 index);
    // 0x7100e854ec: reads horse `index` (the Horse_* flags) into `data` from buffer 1.
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
    // 0x7100e887b8 (placeholder name; called by ai::Horse::calc_): sub_7100E857CC on the selected horse (under
    // _230) if `proc` is the owned horse.
    void sub_7100E887B8(ksys::act::BaseProc* proc, bool a2, bool a3, s32 a4);
    // 0x7100e8998c (CSV HorseMgr::__auto1; placeholder name): for `mode` 2, puts the owned horse and the horse in
    // _30 to sleep and sets _228 bit 4; 0x7100e89a44 (placeholder name) clears that bit.
    void sub_7100E8998C(s32 mode);
    void sub_7100E89A44();
    // 0x7100e89a70 (placeholder name): adds `seconds` to Horse_RideTimeSec of the selected horse (`selected`) or
    // of record 5.
    void sub_7100E89A70(s32 seconds, bool selected);
    // 0x7100e89864 / 0x7100e898f8 (CSV names): link `horse` in _40 / _50, deleting the horse linked there before.
    // The original also builds RiddenAnimalType values (horse->x() and 6 / 3) on the stack without using them.
    void x_0(act::HorseBase* horse);
    void x_2(act::HorseBase* horse);
    // 0x7100e89dac (placeholder name; does not use `this`): sets the bool flag `handle` to whether the actor in `link`
    // is a non-map-object actor that is in the calc state (or `flag`), or `flag` without an actor.
    void sub_7100E89DAC(ksys::act::BaseProcLink* link, bool flag, ksys::gdt::FlagHandle handle);
    // 0x7100e88e44 (descriptive name): the actor linked in _30 (the horse being registered), or null.
    ksys::act::Actor* getRegisteringHorseActor() const;
    // 0x7100e88edc (CSV name): whether one of the ten Horse_UsedAmiiboUidHash entries is `uid_hash`.
    bool isAmiiboUsed(const sead::SafeString& uid_hash);
    // 0x7100e84984 (CSV name; static): copies the Horse_Pos game data flag to Horse_Pos_For_Map.
    static void setHorsePosForMap();
    // 0x7100e824a0 (CSV name): sets flag _0 to `on`, initialises the game data handles (initHorseGameDataIters,
    // 0x7100e82500) and registers mReinitSlot. `heap` is unused.
    // 0x7100e8235c (CSV j_initHorseGameDataIters; name is a guess): the mReinitSlot callback.
    void onGameDataReinit(ksys::gdt::Manager::ReinitEvent* event);
    void initHorseGameDataItersAndStuff(sead::Heap* heap, bool on);
    void initHorseGameDataIters();
    // 0x7100e88720 (descriptive name): the owned horse (mOwnedHorse) as a HorseBase, or null.
    act::HorseBase* getOwnedHorseBase() const;
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
    // 0x7100e84a04 (lane3 s71; declared only): true if `actor` is the owned horse (link at +0x20);
    // otherwise sub_7100E84AE4(accessor of actor, name, flag), and on success 0x7100e84f0c and _d4 = -1.
    bool sub_7100E84A04(ksys::act::Actor* actor, const sead::SafeString& name, bool flag);
    void setRiddenHorseMaybe(ksys::act::Actor* actor);
    // 0x7100e85334 (CSV HorseMgr::__auto0): whether `link` is the owned horse's link.
    bool sub_7100E85334(const ksys::act::BaseProcLink& link) const;
    // 0x7100e8527c (declaration only; NPCRegisterHorse / NPCRegisterAndReceiveHorse): registers
    // the horse `link` under `name`.
    bool sub_7100E8527C(ksys::act::BaseProcLink* link, const sead::SafeString& name, bool a3);
    // 2026-10-07: the registration wrapper passes its acquired horse accessor here.
    bool sub_7100E84AE4(const ksys::act::ActorLinkConstDataAccess& accessor,
                        const sead::SafeString& name, bool flag);

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
    // 0x7100e85cac (declaration only; NPCDeliverHorse::oneShot_): creates horse `index` at `pos` (1152 B).
    void sub_7100E85CAC(sead::Heap* heap, s32 index, const sead::Vector3f& pos, ksys::act::Actor* actor,
                        bool flag);

    /* 0x20 */ ksys::act::BaseProcLink mOwnedHorse;
    /* 0x30 */ ksys::act::BaseProcLink _30;  // the horse being registered / received (NPCRegisterHorse)
    // Horse links replaced by x_0 / x_2 (the previous horse is deleted).
    /* 0x40 */ ksys::act::BaseProcLink _40;
    /* 0x50 */ ksys::act::BaseProcLink _50;
    /* 0x60 */ ksys::act::BaseProcLink _60;  // RideHorseForEventAction::calc_
    // 2026-10-07: ctor E821E4 constructs this link; registration E8527C assigns it.
    /* 0x70 */ ksys::act::BaseProcLink _70;
    /* 0x80 */ ksys::act::BaseProcHandle _80;  // the owned horse being created (WaitWhileCreatingOwnedHorse)
    u8 _90[0xb0 - 0x90];
    /* 0xb0 */ ksys::MesTransceiverId _b0;  // NPCHorseResurrect::oneShot_ messages the horse manager's receiver
    u8 _c8[0xd0 - 0xc8];
    /* 0x0d0 */ s32 _d0;  // the selected horse (-1: none)
    u8 _d4[0x180 - 0xd4];
    // Game data handles set by initHorseGameDataIters (0x7100e82500).
    /* 0x180 */ ksys::gdt::FlagHandle _180;  // Horse_Pos
    /* 0x184 */ ksys::gdt::FlagHandle _184;  // Horse_RotY
    /* 0x188 */ ksys::gdt::FlagHandle _188;  // Horse_Pos_For_Map
    /* 0x18c */ ksys::gdt::FlagHandle _18c;  // Last_Ridden_Horse_Pos
    /* 0x190 */ ksys::gdt::FlagHandle _190;  // Last_Ridden_Horse_RotY
    /* 0x194 */ ksys::gdt::FlagHandle _194;  // Horse_Extra_Charge_Num
    /* 0x198 */ ksys::gdt::FlagHandle _198;  // Last_Ridden_Horse_Extra_Charge_Num
    /* 0x19c */ ksys::gdt::FlagHandle _19c;  // Horse_Familiarity
    /* 0x1a0 */ ksys::gdt::FlagHandle _1a0;  // Horse_ActiveIndex
    /* 0x1a4 */ ksys::gdt::FlagHandle _1a4;  // Horse_ActorName
    /* 0x1a8 */ ksys::gdt::FlagHandle _1a8;  // Horse_Is_LastRidden_Owned
    /* 0x1ac */ ksys::gdt::FlagHandle _1ac;  // Horse_Large_Exists
    /* 0x1b0 */ ksys::gdt::FlagHandle _1b0;  // Horse_Zelda_Exists
    u8 _1b4[0x1b8 - 0x1b4];
    // Registered with gdt::Manager::addReinitCallback by initHorseGameDataItersAndStuff (the delegate target is
    // set by the constructor, not decompiled).
    /* 0x1b8 */ ksys::gdt::Manager::ReinitSignal::Slot mReinitSlot;
    u8 _1b8_end[0x228 - 0x1b8 - sizeof(ksys::gdt::Manager::ReinitSignal::Slot)];
    /* 0x228 */ sead::BitFlag16 _228;
    u8 _22a[0x230 - 0x22a];
    /* 0x230 */ sead::CriticalSection _230;
    // The size (0x2c0) is the allocation size of createInstance.
    /* 0x270 */ Unk_7100e8a080 _270;
};
KSYS_CHECK_SIZE_NX150(HorseMgr, 0x2c0);

// 0x7100e82130 / 0x7100e8216c / 0x7100e821a8 (unnamed in the CSV; placeholder names): the mane / reins /
// saddle model name of horse type `type` (1 - 10; 0 and 11+ give the empty string). The safe strings are
// initialised by 0x7100e89eec.
const sead::SafeString& getHorseManeName(HorseMgr::RiddenAnimalType type);
const sead::SafeString& getHorseReinsName(HorseMgr::RiddenAnimalType type);
const sead::SafeString& getHorseSaddleName(HorseMgr::RiddenAnimalType type);

}  // namespace uking

// 0x7100e86d84 (CSV name; declared only, class unknown): resurrects the horse with the given index; returns the new
// index, or a negative number on failure.
s32 resurrectHorseStuff(uking::HorseMgr* mgr, s32 index);
