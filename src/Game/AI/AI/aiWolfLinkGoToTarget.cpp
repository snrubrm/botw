#include "Game/AI/AI/aiWolfLinkGoToTarget.h"
#include "Game/Actor/actWolfLink.h"

namespace uking::ai {

WolfLinkGoToTarget::WolfLinkGoToTarget(const InitArg& arg) : HorseFollow(arg) {}

WolfLinkGoToTarget::~WolfLinkGoToTarget() = default;

bool WolfLinkGoToTarget::init_(sead::Heap* heap) {
    if (!HorseFollow::init_(heap))
        return false;
    _e0 = sead::DynamicCast<act::WolfLink>(mActor);
    return _e0 != nullptr;
}

void WolfLinkGoToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollow::enter_(params);
}

void WolfLinkGoToTarget::leave_() {
    HorseFollow::leave_();
}

void WolfLinkGoToTarget::loadParams_() {
    HorseFollow::loadParams_();
}

}  // namespace uking::ai
