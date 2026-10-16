#include "Game/Actor/Behavior/behaviorPlayerMoveNoise.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/Player/actPlayerBase.h"

namespace uking::behavior {

PlayerMoveNoise::PlayerMoveNoise(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void PlayerMoveNoise::enter() {}

// NON_MATCHING: velocity loads, float operand registers and final call arguments are scheduled differently.
void PlayerMoveNoise::calc() {
    const auto& velocity = mActor->getVelocity();
    f32 speed_squared = velocity.x * velocity.x;
    if (*mIsVec3_s)
        speed_squared += velocity.y * velocity.y;
    speed_squared = velocity.z * velocity.z + speed_squared;
    f32 noise = sead::Mathf::sqrt(speed_squared) / *mMaxSpeed_s * *mNoiseValue_s;
    if (auto* player = sead::DynamicCast<uking::act::PlayerBase>(mActor))
        noise *= player->m319() / player->m320();
    sub_71005D8D4C(mActor, sead::Mathf::clampMax(noise, *mMaxNoise_s), 1, false);
}

void PlayerMoveNoise::leave() {
    sub_71005D8D4C(mActor, 0, 1, false);
}

void PlayerMoveNoise::loadParams() {
    getStaticParam(&mNoiseValue_s, "NoiseValue");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mMaxNoise_s, "MaxNoise");
    getStaticParam(&mIsVec3_s, "IsVec3");
}

}  // namespace uking::behavior
