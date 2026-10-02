#include "Game/AI/Behavior/behaviorChangeEnableNearTrigger.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actSchedule.h"

namespace uking::behavior {

ChangeEnableNearTrigger::ChangeEnableNearTrigger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

ChangeEnableNearTrigger::~ChangeEnableNearTrigger() = default;

bool ChangeEnableNearTrigger::m6(sead::Heap* heap) {
    return true;
}

void ChangeEnableNearTrigger::m7() {}

void ChangeEnableNearTrigger::m8() {
    if (auto* schedule = mActor->getSchedule()) {
        _38 = schedule->_124;
        schedule->_124 = !*mEnable_s;
    }
}

void ChangeEnableNearTrigger::m9() {
    if (*mIsRestoreWhenLeave_s) {
        if (auto* schedule = mActor->getSchedule()) {
            if (_38)
                schedule->_124 = false;
            else
                schedule->_124 = true;
        }
    }
}

void ChangeEnableNearTrigger::loadParams() {
    getStaticParam(&mEnable_s, "Enable");
    getStaticParam(&mIsRestoreWhenLeave_s, "IsRestoreWhenLeave");
}

}  // namespace uking::behavior
