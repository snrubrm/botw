#include "Game/AI/AI/aiBlownOff.h"

namespace uking::ai {

BlownOff::BlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool BlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("ふっとび", params);
}

void BlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BlownOff::loadParams_() {
    getStaticParam(&mDrownDepth_s, "DrownDepth");
    getStaticParam(&mIsForceGetUp_s, "IsForceGetUp");
    getStaticParam(&mIsIceBreak_s, "IsIceBreak");
}

bool BlownOff::isFinished() const {
    return ActionBase::isFinished() || (isCurrentChild("起き上がり") && getCurrentChild()->isFinished());
}

}  // namespace uking::ai
