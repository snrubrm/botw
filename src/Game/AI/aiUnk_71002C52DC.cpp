#include "Game/AI/aiUnk_71002C52DC.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"

bool sub_71002C52DC(ksys::act::Actor* actor, f32 ratio) {
    const s32* life = actor->getLife();
    const f32 current_life = life ? f32(*life) : 1.0f;
    const s32 max_life = actor->getMaxLife();
    const f32 threshold = f32(max_life - getNumberOfClearedRemains() * 1000);
    return threshold * ratio >= current_life;
}
