#include "Game/AI/Action/actionAdvanceTime.h"
#include "Game/gameResetter.h"

namespace uking::action {

AdvanceTime::AdvanceTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AdvanceTime::~AdvanceTime() = default;

bool AdvanceTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AdvanceTime::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AdvanceTime::leave_() {
    ksys::act::ai::Action::leave_();
}

void AdvanceTime::loadParams_() {
    getDynamicParam(&mDestTime_d, "DestTime");
    getDynamicParam(&mDirectTime_d, "DirectTime");
    getDynamicParam(&mPassTime_d, "PassTime");
    getDynamicParam(&mActReset_d, "ActReset");
}

void AdvanceTime::calc_() {
    if (isFinished() || isFailed())
        return;

    if (*mActReset_d) {
        auto* resetter = Resetter::instance();
        if (_40) {
            if (!resetter->finishedReset())
                return;
        } else {
            if (resetter->startReset(ResetType{1}, ResetOption{0}, sead::SafeString::cEmptyString, false, false))
                _40 = true;
            return;
        }
    }
    setFinished();
}

}  // namespace uking::action
