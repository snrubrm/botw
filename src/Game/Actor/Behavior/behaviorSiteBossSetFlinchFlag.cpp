#include "Game/Actor/Behavior/behaviorSiteBossSetFlinchFlag.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::behavior {

SiteBossSetFlinchFlag::SiteBossSetFlinchFlag(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SiteBossSetFlinchFlag::~SiteBossSetFlinchFlag() = default;

bool SiteBossSetFlinchFlag::init_(sead::Heap* heap) {
    return true;
}

void SiteBossSetFlinchFlag::calc() {}

void SiteBossSetFlinchFlag::loadParams() {

}

void SiteBossSetFlinchFlag::enter() {
    if (auto* boss = sead::DynamicCast<uking::act::SiteBoss>(mActor))
        boss->_1558.set(0x200000);
}

void SiteBossSetFlinchFlag::leave() {
    if (auto* boss = sead::DynamicCast<uking::act::SiteBoss>(mActor))
        boss->_1558.reset(0x200000);
}

}  // namespace uking::behavior
