#include "Game/AI/AI/aiSandwormBlownOff.h"

namespace uking::ai {

SandwormBlownOff::SandwormBlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormBlownOff::~SandwormBlownOff() = default;

bool SandwormBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("先行動");
}

void SandwormBlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormBlownOff::loadParams_() {
    getStaticParam(&mBlownOffTimer_s, "BlownOffTimer");
}

bool SandwormBlownOff::isFinished() const {
    return ksys::act::ai::Ai::isFinished() ||
           (isCurrentChild("後攻撃") && getCurrentChild()->isFinished());
}

}  // namespace uking::ai
