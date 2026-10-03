#include "Game/AI/AI/aiWolfLinkLeadToTarget.h"
#include "Game/Actor/actWolfLink.h"

namespace uking::ai {

WolfLinkLeadToTarget::WolfLinkLeadToTarget(const InitArg& arg) : LeadToTarget(arg) {}

WolfLinkLeadToTarget::~WolfLinkLeadToTarget() = default;

bool WolfLinkLeadToTarget::init_(sead::Heap* heap) {
    if (!LeadToTarget::init_(heap))
        return false;
    _98 = sead::DynamicCast<act::WolfLink>(mActor);
    return _98 != nullptr;
}

void WolfLinkLeadToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    LeadToTarget::enter_(params);
    _a0 = false;
}

void WolfLinkLeadToTarget::leave_() {
    LeadToTarget::leave_();
}

void WolfLinkLeadToTarget::loadParams_() {
    LeadToTarget::loadParams_();
}

}  // namespace uking::ai
