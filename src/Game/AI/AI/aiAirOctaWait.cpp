#include "Game/AI/AI/aiAirOctaWait.h"

namespace uking::ai {

AirOctaWait::AirOctaWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AirOctaWait::~AirOctaWait() = default;

bool AirOctaWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AirOctaWait::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    changeChild("通常");
}

void AirOctaWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AirOctaWait::loadParams_() {
    getDynamicParam(&mIsSameChange_d, "IsSameChange");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai
