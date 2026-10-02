#include "Game/AI/Action/actionBackFlip.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

BackFlip::BackFlip(const InitArg& arg) : RotateTurnToTarget(arg) {}

BackFlip::~BackFlip() = default;

bool BackFlip::init_(sead::Heap* heap) {
    if (!RotateTurnToTarget::init_(heap))
        return false;
    return _a0.acquire(heap, static_cast<Unk_71025afb58**>(mRefPosVibrateChecker_a));
}

void BackFlip::enter_(ksys::act::ai::InlineParamPack* params) {
    RotateTurnToTarget::enter_(params);
    _cc = false;
    _cd = false;
    if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_a0._0))
        checker->reset(15.0f);
}

void BackFlip::leave_() {
    RotateTurnToTarget::leave_();
    auto* actor = mActor;
    sub_7100738AA8(actor, 0.0f);
    sub_7100738428(actor, 0.1f);
}

void BackFlip::loadParams_() {
    RotateTurnToTarget::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mPosRestRatio_s, "PosRestRatio");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mNearGrHeight_s, "NearGrHeight");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void BackFlip::calc_() {
    RotateTurnToTarget::calc_();
}

bool BackFlip::isFinished() const {
    if (!_cc)
        return false;
    auto* actor = mActor;
    if (isBgGroundHit(actor, false))
        return true;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    const sead::Vector3f down = -sead::Vector3f::ey;
    return somePositionCalc(&pos, pos, down, *mNearGrHeight_s);
}

}  // namespace uking::action
