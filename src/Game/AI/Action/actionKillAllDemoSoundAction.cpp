#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include "Game/AI/Action/actionKillAllDemoSoundAction.h"

namespace uking::action {

KillAllDemoSoundAction::KillAllDemoSoundAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KillAllDemoSoundAction::~KillAllDemoSoundAction() = default;

bool KillAllDemoSoundAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool KillAllDemoSoundAction::oneShot_() {
    if (auto* mgr = aal::SystemAccessor::getGroupMgr()) {
        if (auto* group = mgr->findGroup("Demo"))
            group->stopAllSound(-1.0f);
        if (auto* group = mgr->findGroup("SystemAcrossScene"))
            group->stopAllSound(-1.0f);
    }
    return true;
}

void KillAllDemoSoundAction::loadParams_() {}

}  // namespace uking::action
