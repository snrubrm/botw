#include "Game/AI/Action/actionEventPickOutFromPorch.h"

// Existing CSV utility name; source namespace is unknown.
bool aiActionEventPickOutFromPorch(ksys::act::BaseProcHandle* handle);

namespace uking::action {

EventPickOutFromPorch::EventPickOutFromPorch(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPickOutFromPorch::~EventPickOutFromPorch() = default;

bool EventPickOutFromPorch::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPickOutFromPorch::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPickOutFromPorch::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPickOutFromPorch::loadParams_() {
    getStaticParam(&mPickOutItemType_s, "PickOutItemType");
    getDynamicParam(&mIsUseCarryBox_d, "IsUseCarryBox");
}

void EventPickOutFromPorch::calc_() {
    if (isFinished() || isFailed())
        return;
    if (_30.hasProcCreationFailed()) {
        setFailed();
        _30.deleteProcIfFailed();
    } else if (_30.isProcReady()) {
        if (aiActionEventPickOutFromPorch(&_30))
            setFinished();
        else
            setFailed();
    }
}

}  // namespace uking::action
