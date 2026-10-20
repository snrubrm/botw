#include "KingSystem/ActorSystem/Awareness/actAwarenessDefs.h"
#include <container/seadSafeArray.h>
#include <utility/aglParameter.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessMiscUtils.h"

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
        if (calcAwarenessHash(sAwarenessTerrorTypes(i)) == hash)
            return 1 << i;
    }

    // XXX: wouldn't returning 0 be a better idea?
    return 0xffffffff;
}

u32 getAwarenessSensorFlags(u32 hash) {
    for (u32 i = 0; i < u32(sAwarenessSensorTypes.size()); ++i) {
        if (calcAwarenessHash(sAwarenessSensorTypes(i)) == hash)
            return 1 << i;
    }
    return 0xffffffff;
}

}  // namespace ksys::act

void Unk_7102517ab0::m4() {
    if (!_f8.hasProc())
        return;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.setStartAndEnd(_108, _114);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    query.setGroundHit(ksys::phys::GroundHit::LineOfSight);

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_f8, &accessor);
    query.setGroupHandler(accessor.x(0));

    if (_18.mLink.hasProc()) {
        ksys::act::ActorLinkConstDataAccess target;
        ksys::act::acquireActor(&_18.mLink, &target);
        query.addIgnoredGroup(target.x(0));
    }

    _120 = !query.worldRayCast(ksys::phys::ContactLayerType::Entity);
}
