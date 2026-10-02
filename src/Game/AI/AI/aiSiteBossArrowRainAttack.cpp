#include "Game/AI/AI/aiSiteBossArrowRainAttack.h"

namespace uking::ai {

SiteBossArrowRainAttack::SiteBossArrowRainAttack(const InitArg& arg)
    : SiteBossReflectArrowRoot(arg) {}

SiteBossArrowRainAttack::~SiteBossArrowRainAttack() = default;

bool SiteBossArrowRainAttack::init_(sead::Heap* heap) {
    return SiteBossReflectArrowRoot::init_(heap);
}

void SiteBossArrowRainAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossReflectArrowRoot::enter_(params);
}

void SiteBossArrowRainAttack::leave_() {
    SiteBossReflectArrowRoot::leave_();
}

void SiteBossArrowRainAttack::loadParams_() {
    SiteBossReflectArrowRoot::loadParams_();
}

void SiteBossArrowRainAttack::m37() {
    SiteBossReflectArrowRoot::m37();
}

s32 SiteBossArrowRainAttack::m43() {
    return SiteBossReflectArrowRoot::m43();
}

void SiteBossArrowRainAttack::m45(sead::Vector3f* out) {
    SiteBossReflectArrowRoot::m45(out);
    out->y += -0.5f;
}

bool SiteBossArrowRainAttack::m48() {
    return SiteBossReflectArrowRoot::m48();
}

}  // namespace uking::ai
