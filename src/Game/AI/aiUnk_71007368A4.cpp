#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actTag.h"

bool sub_71007368A4(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (accessor.hasTag(ksys::act::tags::TypeKokko))
        return true;
    return accessor.getName() == "Kokko_Simple";
}

bool sub_710073697C(ksys::act::BaseProcLink* link, const sead::SafeString& name) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.sub_71006DE298(name);
}

bool sub_71007369D0(ksys::act::BaseProcLink* link, const sead::SafeString& name) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.sub_71006DE338(name);
}

sead::Vector3f sub_7100736A24(ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    return accessor.getPreviousPos();
}

bool sub_7100736B68(int value) {
    return value == 21 || sub_7100736B94(value);
}

bool sub_7100736B94(int value) {
    switch (value) {
    case 20:
    case 22:
    case 23:
    case 27:
    case 30:
    case 31:
        return true;
    default:
        return false;
    }
}

bool sub_7100736BBC(int value) {
    return value == 6 || value == 7 || value == 8;
}

bool sub_7100736BD8(int value) {
    return value == 25 || value == 26;
}

bool sub_7100736D98(ksys::act::Actor* actor) {
    auto* dmg = actor->getDamageMgr();
    if (!dmg)
        return false;
    return dmg->getField54() == 2 || dmg->getField54() == 1 || dmg->getField54() == 5;
}
