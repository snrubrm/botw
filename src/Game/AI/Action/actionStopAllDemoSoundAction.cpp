#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include "Game/AI/Action/actionStopAllDemoSoundAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

StopAllDemoSoundAction::StopAllDemoSoundAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StopAllDemoSoundAction::~StopAllDemoSoundAction() = default;

bool StopAllDemoSoundAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StopAllDemoSoundAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = 1.0f;
}

void StopAllDemoSoundAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void StopAllDemoSoundAction::loadParams_() {}

void StopAllDemoSoundAction::calc_() {
    if (isFinished() || isFailed())
        return;
    if (_1c <= 0.0f) {
        if (auto* mgr = aal::SystemAccessor::getGroupMgr()) {
            if (auto* group = mgr->findGroup("Demo"))
                group->stopAllSound(-1.0f);
            if (auto* group = mgr->findGroup("SystemAcrossScene"))
                group->stopAllSound(-1.0f);
        }
        setFinished();
        mFlags.set(Flag::Changeable);
    }
    ksys::Timer::update(&_1c, -1.0f);
}

}  // namespace uking::action
