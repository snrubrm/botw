#include "Game/AI/aiUnk_710070284C.h"
#include "KingSystem/ActorSystem/actActor.h"

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
