#include "Game/AI/AI/aiAppearNearTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

AppearNearTarget::AppearNearTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AppearNearTarget::~AppearNearTarget() = default;

bool AppearNearTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AppearNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool AppearNearTarget::isChangeable() const {
    return false;
}

bool AppearNearTarget::m36(const sead::Vector3f& pos) {
    return true;
}

void AppearNearTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AppearNearTarget::loadParams_() {
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mTeraDist_s, "TeraDist");
    getMapUnitParam(&mNearCreateAppearID_m, "NearCreateAppearID");
    getAITreeVariable(&mIsStopFallCheck_a, "IsStopFallCheck");
}

void AppearNearTarget::m34(sead::Vector3f* out) {
    sub_71005D96A8(mActor).getBase(*out, 2);
}

void AppearNearTarget::m35(sead::Vector3f* out) {
    *out = sub_71005D9330(mActor);
}

bool AppearNearTarget::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("湧出"))
        return getCurrentChild()->isFinished();
    return false;
}

}  // namespace uking::ai
