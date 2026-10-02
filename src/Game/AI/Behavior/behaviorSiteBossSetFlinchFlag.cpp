#include "Game/AI/Behavior/behaviorSiteBossSetFlinchFlag.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::behavior {

SiteBossSetFlinchFlag::SiteBossSetFlinchFlag(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SiteBossSetFlinchFlag::~SiteBossSetFlinchFlag() = default;

bool SiteBossSetFlinchFlag::m6(sead::Heap* heap) {
    return true;
}

void SiteBossSetFlinchFlag::m7() {}

void SiteBossSetFlinchFlag::loadParams() {

}

void SiteBossSetFlinchFlag::m8() {
    if (auto* boss = sead::DynamicCast<uking::act::SiteBoss>(mActor))
        boss->_1558.set(0x200000);
}

void SiteBossSetFlinchFlag::m9() {
    if (auto* boss = sead::DynamicCast<uking::act::SiteBoss>(mActor))
        boss->_1558.reset(0x200000);
}

}  // namespace uking::behavior
