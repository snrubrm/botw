#include "Game/AI/AI/aiSiteBossReflectArrowRoot.h"

namespace uking::ai {

SiteBossReflectArrowRoot::SiteBossReflectArrowRoot(const InitArg& arg)
    : SiteBossShootNormalArrowRoot(arg) {}

SiteBossReflectArrowRoot::~SiteBossReflectArrowRoot() = default;

bool SiteBossReflectArrowRoot::init_(sead::Heap* heap) {
    return SiteBossShootNormalArrowRoot::init_(heap);
}

void SiteBossReflectArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossShootNormalArrowRoot::enter_(params);
}

void SiteBossReflectArrowRoot::leave_() {
    SiteBossShootNormalArrowRoot::leave_();
}

void SiteBossReflectArrowRoot::loadParams_() {
    SiteBossShootNormalArrowRoot::loadParams_();
    getDynamicParam(&mIsReflectAmongChild_d, "IsReflectAmongChild");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool SiteBossReflectArrowRoot::m34() {
    return sub_7100588164(false);
}

void SiteBossReflectArrowRoot::m41() {}

s32 SiteBossReflectArrowRoot::m43() {
    return 1;
}

}  // namespace uking::ai
