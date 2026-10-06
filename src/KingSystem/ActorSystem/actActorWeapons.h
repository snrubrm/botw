#pragma once

#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {

class Actor;
class ActorConstDataAccess;
class WeaponBase;
struct Unk117;

// 0x7100efd700 (unnamed in the CSV): the Player / PauseMenuPlayer profiles, or an NPC / ClerkNPC profile
// whose GParam does not say that it is off the pod from weapons. False for a null actor.
bool sub_7100EFD700(Actor* actor);
// 0x7100efd8e4 (unnamed in the CSV): whether the actor has the PauseMenuPlayer profile.
bool sub_7100EFD8E4(Actor* actor);

// 0x7100efa810 (unnamed in the CSV): calls WeaponBase::m215 on the weapon actor of `accessor`.
void sub_7100EFA810(ActorConstDataAccess* accessor);

namespace acc {
class PlayerOrEnemy;
}

// TODO: incomplete. Embedded in PlayerOrEnemy (at 0xb90) and NPC; CSV name ActorWeapons.
class ActorWeapons {
public:
    explicit ActorWeapons(Actor* actor);
    ~ActorWeapons();

    // FIXME: figure out return types, parameters and names
    virtual void m0();
    // CSV ActorWeapons::equipWeapon (not decompiled): PlayerOrEnemy::m164 forwards its arguments here.
    virtual bool equipWeapon(s32 idx, Actor* weapon, bool a3, bool a4);
    // Called by Enemy::m177 before it records the weapon.
    virtual bool m2(s32 idx, Actor* weapon);
    virtual void m3();

    WeaponBase* getEquippedWeapon(int idx) const;
    void resetBaseProcLinkForActor(BaseProc* proc);
    void sleep(BaseProc::SleepWakeReason reason);
    void wakeUp(BaseProc::SleepWakeReason reason);
    // 0x7100efcc20 (declaration only): requests deletion of the six linked weapons with `reason`.
    void sub_7100EFCC20(BaseProc::DeleteReason reason);
    // 0x7100efcd98 (declaration only): forwards the owner to the six non-exempt linked weapons.
    void sub_7100EFCD98(Actor* owner);
    // 0x7100efc2bc (CSV ActorWeapons::dropWeapon): drops the weapon in slot `idx` (WeaponBase::m175) and
    // forgets it.
    bool dropWeapon(int idx, const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5);
    // 0x7100efd344 (CSV ActorWeapons::x): calls WeaponBase::m215 on every weapon actor.
    void x();
    // 0x7100efcf10 (declared only): called by PlayerOrEnemy::m51.
    void sub_7100EFCF10(bool on);
    // 0x7100efbfb8 (CSV ActorStruct3::resetWeaponBaseProcLink; declared only): resets the BaseProcLink of the weapon in
    // slot `idx`.
    bool resetWeaponBaseProcLink(s32 idx);
    // 0x7100efc3d4 (unnamed in the CSV; name is a guess): WeaponBase::m175 (the drop request) on every weapon that
    // is in the calc state, forgetting the weapon; always true.
    bool dropAllWeapons(const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5);
    // 0x7100efc4e0 (unnamed in the CSV; name is a guess): the same with WeaponBase::m176 (an extra target position).
    bool dropAllWeaponsToTarget(const sead::Vector3f& target, const sead::Vector3f& pos, bool a3, bool a4,
                                void* a5, bool a6);
    // 0x7100efc5f4 / 0x7100efc6ec (unnamed in the CSV; names are guesses): the drop request of the weapon in slot
    // `idx` (WeaponBase::m177 / m179); always true.
    bool dropWeaponM177(int idx, const sead::Vector3f& target, void* a2);
    bool dropWeaponM179(int idx);
    // 0x7100efd1f8 (unnamed in the CSV): whether any of the weapon actors reports true from Actor::m50
    // (through ActorConstDataAccess::sub_7100D0FEAC).
    bool sub_7100EFD1F8();
    // 0x7100efd458: forwards the request to every weapon actor (Actor::x_17).
    void sub_7100EFD458(Unk117* arg);

    // Accessed directly by AI helper functions (0x71005db5c0 - 0x71005db7e4)

    struct Unk1 {
        BaseProcLink link;
        bool _10 = false;
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x18);

    sead::SafeArray<Unk1, 6> mWeapons;
    Actor* mActor;
};
KSYS_CHECK_SIZE_NX150(ActorWeapons, 0xa0);

}  // namespace ksys::act
