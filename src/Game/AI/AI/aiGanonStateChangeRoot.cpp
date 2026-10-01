#include "Game/AI/AI/aiGanonStateChangeRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

GanonStateChangeRoot::GanonStateChangeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonStateChangeRoot::~GanonStateChangeRoot() = default;

bool GanonStateChangeRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonStateChangeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonStateChangeRoot::leave_() {
    sub_71005DB434(mActor);
}

void GanonStateChangeRoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
