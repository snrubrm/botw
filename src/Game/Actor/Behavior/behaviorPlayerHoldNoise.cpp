#include "Game/Actor/Behavior/behaviorPlayerHoldNoise.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/Player/actPlayerBase.h"

namespace uking::behavior {

PlayerHoldNoise::PlayerHoldNoise(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void PlayerHoldNoise::enter() {}

void PlayerHoldNoise::calc() {
    f32 noise = *mNoiseValue_s;
    if (auto* player = sead::DynamicCast<uking::act::PlayerBase>(mActor))
        noise *= player->m319();
    sub_71005D8D4C(mActor, noise, 1, false);
}

void PlayerHoldNoise::leave() {
    sub_71005D8D4C(mActor, 0, 1, false);
}

void PlayerHoldNoise::loadParams() {
    getStaticParam(&mNoiseValue_s, "NoiseValue");
}

}  // namespace uking::behavior
