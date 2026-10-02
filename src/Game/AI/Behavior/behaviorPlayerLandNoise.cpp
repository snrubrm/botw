#include "Game/AI/Behavior/behaviorPlayerLandNoise.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::behavior {

PlayerLandNoise::PlayerLandNoise(const InitArg& arg) : PlayerLandNoiseBase(arg) {}

PlayerLandNoise::~PlayerLandNoise() = default;

bool PlayerLandNoise::m6(sead::Heap* heap) {
    return PlayerLandNoiseBase::m6(heap);
}

void PlayerLandNoise::m7() {
    if (auto* player = sead::DynamicCast<ksys::act::PlayerBase>(mActor)) {
        if (player->m195())
            return;
    }
    PlayerLandNoiseBase::m7();
}

void PlayerLandNoise::m8() {
    PlayerLandNoiseBase::m8();
}

void PlayerLandNoise::m9() {
    PlayerLandNoiseBase::m9();
}

void PlayerLandNoise::loadParams() {
    PlayerLandNoiseBase::loadParams();
}

f32 PlayerLandNoise::m14() {
    f32 value = *mNoiseValue_s;
    if (auto* player = sead::DynamicCast<ksys::act::PlayerBase>(mActor))
        value *= player->m319();
    return value;
}

}  // namespace uking::behavior
