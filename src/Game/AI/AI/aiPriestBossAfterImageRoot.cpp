#include "Game/AI/AI/aiPriestBossAfterImageRoot.h"

namespace uking::ai {

PriestBossAfterImageRoot::PriestBossAfterImageRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossAfterImageRoot::~PriestBossAfterImageRoot() = default;

bool PriestBossAfterImageRoot::init_(sead::Heap* heap) {
    _38 = false;
    return true;
}

void PriestBossAfterImageRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossAfterImageRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossAfterImageRoot::loadParams_() {}

}  // namespace uking::ai
