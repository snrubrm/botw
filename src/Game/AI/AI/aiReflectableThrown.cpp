#include "Game/AI/AI/aiReflectableThrown.h"

namespace uking::ai {

ReflectableThrown::ReflectableThrown(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReflectableThrown::~ReflectableThrown() = default;

bool ReflectableThrown::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReflectableThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ReflectableThrown::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReflectableThrown::loadParams_() {
    getStaticParam(&mIsReflectByGuard_s, "IsReflectByGuard");
    getStaticParam(&mIsReflectByArrow_s, "IsReflectByArrow");
    getStaticParam(&mHitColName_s, "HitColName");
    getStaticParam(&mRefSpeedRatioByJustGuard_s, "RefSpeedRatioByJustGuard");
}

bool ReflectableThrown::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool ReflectableThrown::isFinished() const {
    return getCurrentChild()->isFinished() && !sub_710053DA04(nullptr);
}

void ReflectableThrown::m34() {
    changeChild("投擲");
}

}  // namespace uking::ai
