#include "Game/Actor/Action/actionSiteBossSwordSlowMove.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"
#include <cmath>

namespace uking::action {

SiteBossSwordSlowMove::SiteBossSwordSlowMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossSwordSlowMove::~SiteBossSwordSlowMove() = default;

bool SiteBossSwordSlowMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: load scheduling of the segment endpoints and the front vector.
void SiteBossSwordSlowMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    sead::DynamicCast<act::SiteBoss>(mActor);

    const auto& mtx = mActor->getMtx();
    const sead::Vector3f front_xz{mtx(0, 2), 0.0f, mtx(2, 2)};
    const f32 current = *mCurrentFrame_d;
    sead::Vector3f from;
    sead::Vector3f to;
    f32 rate;
    if (current < *mAfterImage0AppearFrame_s) {
        from = mtx.getTranslation();
        to = *mAfterImage0Pos_d;
        rate = current / *mAfterImage0AppearFrame_s;
    } else if (current < *mAfterImage1AppearFrame_s) {
        from = *mAfterImage0Pos_d;
        to = *mAfterImage1Pos_d;
        rate = (*mAfterImage1AppearFrame_s - current) /
               (*mAfterImage1AppearFrame_s - *mAfterImage0AppearFrame_s);
    } else {
        from = *mAfterImage1Pos_d;
        to = *mMoveDstPos_d;
        rate = (*mAppearFrame_s - current) / (*mAppearFrame_s - *mAfterImage1AppearFrame_s);
    }

    sead::Vector3f dir = to - from;
    const f32 distance = dir.length();
    if (distance > 0.0f)
        dir *= 1.0f / distance;
    const sead::Vector3f pos = from + dir * (std::fmin(rate, 1.0f) * distance);
    controller->warpActorToPosition(pos);

    sead::Vector3f front = front_xz;
    front.normalize();
    const sead::Vector3f up = sead::Vector3f::ey;
    sead::Vector3f to_target = to - pos;
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    angle = angle * 57.29578f * axis.y;
    if (angle >= 0.0f && angle < 180.0f)
        playAS("Run_Loop_L", false, 0, 0, -1.0f);
    else
        playAS("Run_Loop_R", false, 0, 0, -1.0f);

    sub_710073FA90(&_6c, mActor);
    const f32 remaining = *mAppearFrame_s - *mCurrentFrame_d;
    _60 = ksys::Timer(remaining, remaining);
}

void SiteBossSwordSlowMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossSwordSlowMove::loadParams_() {
    getStaticParam(&mAfterImage0AppearFrame_s, "AfterImage0AppearFrame");
    getStaticParam(&mAfterImage1AppearFrame_s, "AfterImage1AppearFrame");
    getStaticParam(&mAppearFrame_s, "AppearFrame");
    getDynamicParam(&mCurrentFrame_d, "CurrentFrame");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
    getDynamicParam(&mAfterImage0Pos_d, "AfterImage0Pos");
    getDynamicParam(&mAfterImage1Pos_d, "AfterImage1Pos");
}

void SiteBossSwordSlowMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
