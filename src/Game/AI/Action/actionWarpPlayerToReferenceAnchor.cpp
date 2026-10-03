#include "Game/AI/Action/actionWarpPlayerToReferenceAnchor.h"
#include "Game/gameResetter.h"

namespace uking::action {

WarpPlayerToReferenceAnchor::WarpPlayerToReferenceAnchor(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WarpPlayerToReferenceAnchor::~WarpPlayerToReferenceAnchor() = default;

bool WarpPlayerToReferenceAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpPlayerToReferenceAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpPlayerToReferenceAnchor::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPlayerToReferenceAnchor::loadParams_() {}

void WarpPlayerToReferenceAnchor::calc_() {
    if (isFinished() || isFailed())
        return;
    if (auto* resetter = Resetter::instance()) {
        if (resetter->finishedReset())
            setFinished();
    } else {
        setFailed();
    }
}

}  // namespace uking::action
