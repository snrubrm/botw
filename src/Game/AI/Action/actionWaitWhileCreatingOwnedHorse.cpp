#include "Game/AI/Action/actionWaitWhileCreatingOwnedHorse.h"
#include "Game/gameHorseMgr.h"

namespace uking::action {

WaitWhileCreatingOwnedHorse::WaitWhileCreatingOwnedHorse(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WaitWhileCreatingOwnedHorse::~WaitWhileCreatingOwnedHorse() = default;

bool WaitWhileCreatingOwnedHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitWhileCreatingOwnedHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitWhileCreatingOwnedHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitWhileCreatingOwnedHorse::loadParams_() {}

void WaitWhileCreatingOwnedHorse::calc_() {
    auto* mgr = HorseMgr::instance();
    if (!mgr) {
        setFailed();
        return;
    }
    if (mgr->sub_7100E86CF4())
        return;
    mgr->sub_7100E86D44();
    setFinished();
}

}  // namespace uking::action
