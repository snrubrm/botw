#include "KingSystem/ActorSystem/Awareness/actAwarenessDefs.h"
#include <container/seadSafeArray.h>
#include <utility/aglParameter.h>
#include "KingSystem/ActorSystem/Awareness/actAwareness.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::act {

sead::SafeArray<const char*, 13> sAwarenessTerrorTypes = sead::toArray({
    "TerrorPlayer",
    "TerrorNpc",
    "TerrorEnemy",
    "TerrorGuardian",
    "TerrorImpulse",
    "TerrorFire",
    "TerrorInsect",
    "TerrorHorse",
    "TerrorAnimal",
    "TerrorWolfLink",
    "TerrorIce",
    "TerrorElectric",
    "TerrorManMadeFire",
});

sead::SafeArray<const char*, 23> sAwarenessSensorTypes = sead::toArray({
    "Player",   "PlayerBomb", "Horse",    "Enemy", "Prey",     "Predator", "Domestic", "Assassin",
    "Giant",    "NPC",        "Material", "Food",  "Weapon",   "Spirit",   "Carry",    "Tree",
    "WolfLink", "Chemical",   "Bullet",   "Door",  "Captured", "Guardian", "All",
});

u32 getAwarenessTerrorFlags(u32 hash) {
    for (u32 i = 0; i < u32(sAwarenessTerrorTypes.size()); ++i) {
        if (Awareness::calcHash(sAwarenessTerrorTypes(i)) == hash)
            return 1 << i;
    }

    // XXX: wouldn't returning 0 be a better idea?
    return 0xffffffff;
}

u32 getAwarenessSensorFlags(u32 hash) {
    for (u32 i = 0; i < u32(sAwarenessSensorTypes.size()); ++i) {
        if (Awareness::calcHash(sAwarenessSensorTypes(i)) == hash)
            return 1 << i;
    }
    return 0xffffffff;
}

}  // namespace ksys::act

// NON_MATCHING: placeholder destructor; the original (0x7101265168) also destroys members or bases
// this class does not declare yet.
Unk_7102517ab0::~Unk_7102517ab0() = default;
