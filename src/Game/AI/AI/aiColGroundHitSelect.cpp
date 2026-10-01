#include "Game/AI/AI/aiColGroundHitSelect.h"

namespace uking::ai {

ColGroundHitSelect::ColGroundHitSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ColGroundHitSelect::~ColGroundHitSelect() = default;

bool ColGroundHitSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool ColGroundHitSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool ColGroundHitSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ColGroundHitSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ColGroundHitSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ColGroundHitSelect::loadParams_() {
    getStaticParam(&mIsCheckEachFrame_s, "IsCheckEachFrame");
}

}  // namespace uking::ai
