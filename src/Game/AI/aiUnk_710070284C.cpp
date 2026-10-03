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
