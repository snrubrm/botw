#include "Game/AI/AI/aiWolfLinkShiekSensorRoot.h"
#include "Game/UI/uiUtils.h"

namespace uking::ai {

WolfLinkShiekSensorRoot::WolfLinkShiekSensorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkShiekSensorRoot::~WolfLinkShiekSensorRoot() = default;

bool WolfLinkShiekSensorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkShiekSensorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ui::showRuntimeTip(14);
    changeChild("誘導", params);
}

void WolfLinkShiekSensorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkShiekSensorRoot::loadParams_() {
    if (getStaticParam(&mDistanceUntilUpdateTarget_s, "DistanceUntilUpdateTarget"))
        _48 = *mDistanceUntilUpdateTarget_s * *mDistanceUntilUpdateTarget_s;
    getDynamicParam(&mUpdateTarget_d, "UpdateTarget");
}

}  // namespace uking::ai
