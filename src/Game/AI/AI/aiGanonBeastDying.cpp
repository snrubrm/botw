#include "Game/AI/AI/aiGanonBeastDying.h"

namespace uking::ai {

GanonBeastDying::GanonBeastDying(const InitArg& arg) : GanonBeastWait(arg) {}

GanonBeastDying::~GanonBeastDying() = default;

bool GanonBeastDying::init_(sead::Heap* heap) {
    return GanonBeastWait::init_(heap);
}

void GanonBeastDying::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonBeastWait::enter_(params);
}

void GanonBeastDying::calc_() {
    GanonBeastWait::calc_();
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("復帰"))
        _41 = false;
}

void GanonBeastDying::leave_() {
    GanonBeastWait::leave_();
}

void GanonBeastDying::loadParams_() {
    GanonBeastWait::loadParams_();
}

bool GanonBeastDying::m34() {
    return false;
}

}  // namespace uking::ai
