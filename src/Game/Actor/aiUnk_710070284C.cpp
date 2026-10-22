#include "Game/Actor/aiUnk_710070284C.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

int sub_710070284C(ksys::act::Actor* actor) {
    static const int sTable[] = {3, 3, 2, 1, 1, 1, 0, 0, 0};
    auto* life = actor->getLife();
    const s32 value = life ? *life : 1;
    if (value >= 0 && value <= 8)
        return sTable[value];
    return 0;
}

bool sub_7100702894(ksys::act::Actor* actor) {
    auto* life = actor->getLife();
    if (!life)
        return true;
    return *life == 1;
}

bool sub_71007028CC(ksys::act::Actor* actor) {
    auto* life = actor->getLife();
    return life && *life < 1;
}

bool sub_7100703BC8(ksys::act::Actor* actor) {
    auto* life = actor->getLife();
    const s32 value = life ? *life : 1;
    switch (value) {
    case 1:
    case 2:
    case 5:
        return true;
    default:
        return false;
    }
}

void sub_710070427C(ksys::act::Actor* actor) {
    sub_71007A3900(
        actor->findPhysicsBodyByName(ksys::act::getStr_Tgt().cstr(), "WeakPointLast"));

    ksys::phys::InstanceSet* physics = actor->getPhysics();
    if (!physics)
        return;
    ksys::phys::RigidBody* neck =
        actor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(), "Neck");
    if (!neck)
        return;
    physics->sub_7100FBAF18(neck);
}

ksys::phys::RigidBody* sub_710070431C(ksys::act::Actor* actor) {
    return actor->findPhysicsBodyByName(ksys::act::getStr_Tgt().cstr(), "WeakPoint_EyeLid");
}
