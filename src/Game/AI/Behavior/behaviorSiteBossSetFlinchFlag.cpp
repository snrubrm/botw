#include "Game/AI/Behavior/behaviorSiteBossSetFlinchFlag.h"

namespace uking::behavior {

SiteBossSetFlinchFlag::SiteBossSetFlinchFlag(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SiteBossSetFlinchFlag::~SiteBossSetFlinchFlag() = default;

bool SiteBossSetFlinchFlag::m6(sead::Heap* heap) {
    return true;
}

void SiteBossSetFlinchFlag::m7() {}

void SiteBossSetFlinchFlag::loadParams() {

}

}  // namespace uking::behavior
