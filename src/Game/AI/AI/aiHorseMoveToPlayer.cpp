#include "Game/AI/AI/aiHorseMoveToPlayer.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

HorseMoveToPlayer::HorseMoveToPlayer(const InitArg& arg) : HorseFollow(arg) {}

HorseMoveToPlayer::~HorseMoveToPlayer() = default;

bool HorseMoveToPlayer::init_(sead::Heap* heap) {
    return HorseFollow::init_(heap);
}

void HorseMoveToPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollow::enter_(params);
}

void HorseMoveToPlayer::leave_() {
    HorseFollow::leave_();
}

void HorseMoveToPlayer::loadParams_() {
    HorseFollow::loadParams_();
    getStaticParam(&mDistanceSuccessEndIfInterrupted_s, "DistanceSuccessEndIfInterrupted");
    getStaticParam(&mDistanceResetGearInput_s, "DistanceResetGearInput");
}

void HorseMoveToPlayer::m34(sead::Vector3f* out, const sead::Vector3f& pos,
                            const sead::Vector3f& target_pos, const sead::Vector3f& target_velocity,
                            const sead::Vector3f& up) {
    HorseFollow::m34(out, pos, target_pos, target_velocity, up);

    const f32 sec = *mTargetVelocityDistanceSec_s;
    if (sec > 0.0f) {
        ksys::act::ActorConstDataAccess acc;
        if (ksys::act::acquireActor(mTargetActor_d, &acc) && acc.sub_7100D12E64())
            out->setScaleAdd(sec * -30.0f, target_velocity, *out);
    }
}

}  // namespace uking::ai
