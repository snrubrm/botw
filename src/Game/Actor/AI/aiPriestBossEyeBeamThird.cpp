#include "Game/Actor/AI/aiPriestBossEyeBeamThird.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include <random/seadGlobalRandom.h>
#include <cmath>

namespace uking::ai {

PriestBossEyeBeamThird::PriestBossEyeBeamThird(const InitArg& arg) : PriestBossEyeBeam(arg) {}

PriestBossEyeBeamThird::~PriestBossEyeBeamThird() = default;

bool PriestBossEyeBeamThird::init_(sead::Heap* heap) {
    return PriestBossEyeBeam::init_(heap);
}

void PriestBossEyeBeamThird::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossEyeBeam::enter_(params);
}

void PriestBossEyeBeamThird::calc_() {
    PriestBossEyeBeam::calc_();
    if (isCurrentChild("照準") || isCurrentChild("チャージ"))
        sub_7100516FAC(*mDestinationPos_a, *mIsArrivedAtDestination_a);
    else if (isCurrentChild("発射"))
        *mDestinationPos_a = mActor->getMtx().getTranslation();
}

// NON_MATCHING: polar-vector arithmetic and branch/register scheduling differ.
void PriestBossEyeBeamThird::sub_7100516FAC(sead::Vector3f& pos, bool is_arrived) {
    const sead::Vector3f player = getPlayerPosition();
    const sead::Vector3f actor_position = mActor->getMtx().getTranslation();
    const f32 dx = player.x - actor_position.x;
    const f32 dz = player.z - actor_position.z;
    const f32 player_distance = sead::Mathf::sqrt(dx * dx + dz * dz);
    const f32 center_dx = actor_position.x - sUnk_71025c8cf8.x;
    const f32 center_dz = actor_position.z - sUnk_71025c8cf8.z;
    const f32 center_distance = sead::Mathf::sqrt(center_dx * center_dx + center_dz * center_dz);
    if (_d1) {
        if (is_arrived)
            _d1 = false;
        return;
    }
    if (center_distance > sUnk_7102450fa0 * 0.7f) {
        const f32 angle = sead::Mathf::deg2rad(sead::GlobalRandom::instance()->getF32Range(0.0f, 360.0f));
        const sead::Vector2f direction{cosf(angle), sinf(angle)};
        const f32 third_radius = sUnk_7102450fa0 / 3.0f;
        const f32 distance = sead::GlobalRandom::instance()->getF32Range(0.0f, third_radius + third_radius);
        pos = {sUnk_71025c8cf8.x + direction.y * distance, sUnk_71025c8cf8.y,
               sUnk_71025c8cf8.z + direction.x * distance};
        _d1 = true;
        return;
    }
    if (_d0) {
        if (is_arrived)
            _d0 = false;
        return;
    }
    if (player_distance <= 20.0f) {
        const f32 angle = atan2f(dz, dx) +
                          sead::Mathf::deg2rad(sead::GlobalRandom::instance()->getF32Range(-70.0f, 70.0f));
        const sead::Vector2f direction{cosf(angle), sinf(angle)};
        pos = {actor_position.x + direction.y * 50.0f, actor_position.y, actor_position.z + direction.x * 50.0f};
    } else if (player_distance > 50.0f) {
        sead::Vector3f direction = actor_position - player;
        direction.normalize();
        pos = player + direction * 20.0f;
        _d0 = true;
    }
}

void PriestBossEyeBeamThird::leave_() {
    PriestBossEyeBeam::leave_();
}

void PriestBossEyeBeamThird::loadParams_() {
    PriestBossEyeBeam::loadParams_();
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mFacePos_a, "FacePos");
}

}  // namespace uking::ai
