#include "Game/AI/Action/actionGanonThrowFireBall.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

GanonThrowFireBall::GanonThrowFireBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonThrowFireBall::~GanonThrowFireBall() = default;

bool GanonThrowFireBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonThrowFireBall::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    sub_710017BBA0(0);
}

void GanonThrowFireBall::leave_() {
    ksys::act::ai::Action::leave_();
}

const sead::SafeString& GanonThrowFireBall::m32(int idx) {
    return mThrowPartsName_d;
}

void GanonThrowFireBall::m33(sead::Vector3f* out, int idx) {
    out->x = 0.0f;
    out->y = *mBallAppearOffset_s;
    out->z = 0.0f;
}

void GanonThrowFireBall::loadParams_() {
    getStaticParam(&mInitVelocity_s, "InitVelocity");
    getStaticParam(&mFireBallScale_s, "FireBallScale");
    getStaticParam(&mBallAppearOffset_s, "BallAppearOffset");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mThrowPartsName_d, "ThrowPartsName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void GanonThrowFireBall::calc_() {
    if (sub_71005DD780(mActor, 0x47, nullptr, 0, 0))
        sub_710017BE48(0);
    if (isFinishedAS(0, 0))
        setFinished();
}

bool GanonThrowFireBall::isFinished() const {
    return isFinishedAS(0, 0);
}

}  // namespace uking::action
