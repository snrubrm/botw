#include "Game/AI/AI/aiGanonRecognizeRoot.h"

namespace uking::ai {

GanonRecognizeRoot::GanonRecognizeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonRecognizeRoot::~GanonRecognizeRoot() = default;

bool GanonRecognizeRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonRecognizeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("後半");
}

void GanonRecognizeRoot::calc_() {
    if (!isCurrentChild("前半"))
        return;

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        changeChild("後半");
}

void GanonRecognizeRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonRecognizeRoot::loadParams_() {}

}  // namespace uking::ai
