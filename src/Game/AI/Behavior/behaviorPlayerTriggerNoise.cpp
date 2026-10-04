#include "Game/AI/Behavior/behaviorPlayerTriggerNoise.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::behavior {

PlayerTriggerNoise::PlayerTriggerNoise(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void PlayerTriggerNoise::m7() {
    if (_30) {
        _30 = false;
        return;
    }
    sub_71005D8D4C(mActor, 0, 1, false);
}

void PlayerTriggerNoise::m8() {
    f32 noise = *mNoiseValue_s;
    if (auto* player = sead::DynamicCast<ksys::act::PlayerBase>(mActor))
        noise *= player->m319();
    sub_71005D8D4C(mActor, noise, 1, false);
    _30 = true;
}

void PlayerTriggerNoise::m9() {}

void PlayerTriggerNoise::loadParams() {
    getStaticParam(&mNoiseValue_s, "NoiseValue");
}

}  // namespace uking::behavior
