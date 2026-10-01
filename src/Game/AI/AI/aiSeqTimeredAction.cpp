#include "Game/AI/AI/aiSeqTimeredAction.h"

namespace uking::ai {

SeqTimeredAction::SeqTimeredAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqTimeredAction::~SeqTimeredAction() = default;

bool SeqTimeredAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqTimeredAction::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("行動", params);
    _40 = 0;
}

void SeqTimeredAction::calc_() {
    ksys::Timer::update(&_40, 1.0f);
    auto* child = getCurrentChild();
    if (child->isFinished()) {
        setFinished();
    } else if (child->isFailed()) {
        setFailed();
    } else if (child->isChangeable() && *mActionTime_s >= 1 && int(_40) > *mActionTime_s) {
        setFinished();
    }
}

void SeqTimeredAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqTimeredAction::loadParams_() {
    getStaticParam(&mActionTime_s, "ActionTime");
}

}  // namespace uking::ai
