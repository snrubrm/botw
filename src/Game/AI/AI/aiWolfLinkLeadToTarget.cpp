#include "Game/AI/AI/aiWolfLinkLeadToTarget.h"
#include "Game/Actor/actWolfLink.h"
#include <math/seadMathCalcCommon.h>

// Declaration only; original source namespace is unknown.
bool sub_7100742738(sead::Vector3f* out, uking::act::WolfLink* wolf, f32 value);

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

// NON_MATCHING: the string and enum temporaries occupy separate stack slots.
void WolfLinkLeadToTarget::calc_() {
    LeadToTarget::calc_();
    using Idx = act::WolfLink::Idx14f8;
    if (isCurrentChild("待機")) {
        if (_a0) {
            if (_98->_14f8[Idx(Idx::_13)].value <= sead::Mathf::epsilon())
                setFailed();
        } else {
            _a0 = true;
            _98->sub_71002F2E78(Idx::_13);
            _98->_14f8[Idx(Idx::_13)].rate = -1.0f;
        }
    } else {
        if (_a0) {
            _98->sub_71002F2E78(Idx::_13);
            _a0 = false;
        }
        if (!sub_7100742738(nullptr, _98, -1.0f))
            setFailed();
    }
}

void WolfLinkLeadToTarget::leave_() {
    LeadToTarget::leave_();
}

void WolfLinkLeadToTarget::loadParams_() {
    LeadToTarget::loadParams_();
}

}  // namespace uking::ai
