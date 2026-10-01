#include "Game/AI/Action/actionAppearDeathCounter.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

AppearDeathCounter::AppearDeathCounter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearDeathCounter::~AppearDeathCounter() = default;

bool AppearDeathCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearDeathCounter::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ksys::evt::Manager::instance())
        setFinished();
    else
        setFailed();
    mFlags.set(Flag::Changeable);
}

void AppearDeathCounter::leave_() {
    ksys::act::ai::Action::leave_();
}

void AppearDeathCounter::loadParams_() {}

void AppearDeathCounter::calc_() {
    if (isFinished() || isFailed())
        return;
}

}  // namespace uking::action
