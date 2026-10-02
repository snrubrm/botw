#include "Game/AI/AI/aiWolfLinkFollowPlayerRoot.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actWolfLink.h"

namespace uking::ai {

WolfLinkFollowPlayerRoot::WolfLinkFollowPlayerRoot(const InitArg& arg) : HorseFollow(arg) {}

WolfLinkFollowPlayerRoot::~WolfLinkFollowPlayerRoot() = default;

bool WolfLinkFollowPlayerRoot::init_(sead::Heap* heap) {
    if (!HorseFollow::init_(heap))
        return false;

    _100 = sead::DynamicCast<act::WolfLink>(mActor);
    if (!_100)
        return false;

    _144.makeIdentity();
    return true;
}

void WolfLinkFollowPlayerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollow::enter_(params);
    m39(true);
    m40();
    m35();
    _17c = false;
}

void WolfLinkFollowPlayerRoot::leave_() {
    if (auto* rideable = _100->m132()) {
        rideable->_154 = 1.0f;
        HorseFollow::leave_();
    } else {
        setFailed();
    }
}

void WolfLinkFollowPlayerRoot::loadParams_() {
    HorseFollow::loadParams_();
    getStaticParam(&mLateralDistance_s, "LateralDistance");
    getStaticParam(&mAnteriorDistanceStop_s, "AnteriorDistanceStop");
    getStaticParam(&mAnteriorDistanceRun_s, "AnteriorDistanceRun");
    getStaticParam(&mAnteriorDistanceSprint_s, "AnteriorDistanceSprint");
}

void WolfLinkFollowPlayerRoot::m35() {
    HorseFollow::m35();
}

}  // namespace uking::ai
