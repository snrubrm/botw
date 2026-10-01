#include "Game/AI/Action/actionDisappearDeathCounter.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

DisappearDeathCounter::DisappearDeathCounter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisappearDeathCounter::~DisappearDeathCounter() = default;

bool DisappearDeathCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DisappearDeathCounter::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ksys::evt::Manager::instance())
        setFinished();
    else
        setFailed();
    mFlags.set(Flag::Changeable);
}

void DisappearDeathCounter::leave_() {
    ksys::act::ai::Action::leave_();
}

void DisappearDeathCounter::loadParams_() {}

void DisappearDeathCounter::calc_() {
    if (isFinished() || isFailed())
        return;
}

}  // namespace uking::action
