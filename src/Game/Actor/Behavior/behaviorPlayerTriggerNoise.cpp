#include "Game/Actor/Behavior/behaviorPlayerTriggerNoise.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/Player/actPlayerBase.h"

namespace uking::behavior {

PlayerTriggerNoise::PlayerTriggerNoise(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void PlayerTriggerNoise::calc() {
    if (_30) {
        _30 = false;
        return;
    }
    sub_71005D8D4C(mActor, 0, 1, false);
}

void PlayerTriggerNoise::enter() {
    f32 noise = *mNoiseValue_s;
    if (auto* player = sead::DynamicCast<uking::act::PlayerBase>(mActor))
        noise *= player->m319();
    sub_71005D8D4C(mActor, noise, 1, false);
    _30 = true;
}

void PlayerTriggerNoise::leave() {}

void PlayerTriggerNoise::loadParams() {
    getStaticParam(&mNoiseValue_s, "NoiseValue");
}

}  // namespace uking::behavior
