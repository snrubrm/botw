#include "Game/AI/Behavior/behaviorPlayerHoldNoise.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::behavior {

PlayerHoldNoise::PlayerHoldNoise(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void PlayerHoldNoise::m8() {}

void PlayerHoldNoise::m7() {
    f32 noise = *mNoiseValue_s;
    if (auto* player = sead::DynamicCast<ksys::act::PlayerBase>(mActor))
        noise *= player->m319();
    sub_71005D8D4C(mActor, noise, 1, false);
}

void PlayerHoldNoise::m9() {
    sub_71005D8D4C(mActor, 0, 1, false);
}

void PlayerHoldNoise::loadParams() {
    getStaticParam(&mNoiseValue_s, "NoiseValue");
}

}  // namespace uking::behavior
