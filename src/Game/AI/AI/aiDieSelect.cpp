#include "Game/AI/AI/aiDieSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

DieSelect::DieSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DieSelect::~DieSelect() = default;

bool DieSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DieSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool DieSelect::isChangeable() const {
    return false;
}

void DieSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DieSelect::loadParams_() {}

void DieSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        m35();
        callDeleteAndCreateDropAndEmit(mActor, 0);
        setFinished();
    }
}

}  // namespace uking::ai
