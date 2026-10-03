#pragma once

#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {

class Actor;
class WeaponBase;
struct Unk117;

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
    virtual void equipWeapon();
    virtual void m2();
    virtual void m3();

    WeaponBase* getEquippedWeapon(int idx) const;
    void resetBaseProcLinkForActor(BaseProc* proc);
    void sleep(BaseProc::SleepWakeReason reason);
    void wakeUp(BaseProc::SleepWakeReason reason);
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
