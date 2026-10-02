#include "Game/AI/AI/aiSiteBossBigFlameBall.h"

namespace uking::ai {

SiteBossBigFlameBall::SiteBossBigFlameBall(const InitArg& arg) : SiteBossFlameBall(arg) {}

SiteBossBigFlameBall::~SiteBossBigFlameBall() = default;

bool SiteBossBigFlameBall::init_(sead::Heap* heap) {
    return SiteBossFlameBall::init_(heap);
}

void SiteBossBigFlameBall::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossFlameBall::enter_(params);
    _1f4 = m35();
    _200 = *mDestOffset_s;
    _20c = *mRotOffset_m;
    _1f0 = *mSpeed_m;
}

void SiteBossBigFlameBall::calc_() {
    SiteBossFlameBall::calc_();
}

void SiteBossBigFlameBall::leave_() {
    SiteBossFlameBall::leave_();
}

void SiteBossBigFlameBall::loadParams_() {
    SiteBossFlameBall::loadParams_();
    getStaticParam(&mDestOffset_s, "DestOffset");
    getStaticParam(&mDestOffset1_s, "DestOffset1");
    getMapUnitParam(&mSpeed_m, "Speed");
    getMapUnitParam(&mRotOffset_m, "RotOffset");
}

void SiteBossBigFlameBall::m37() {}

u32 SiteBossBigFlameBall::m50() {
    return 8;
}

sead::Vector3f SiteBossBigFlameBall::m58() {
    return _20c;
}

}  // namespace uking::ai
