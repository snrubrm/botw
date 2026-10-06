#include "Game/AI/Action/actionIdleAction.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

IdleAction::IdleAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IdleAction::~IdleAction() = default;

bool IdleAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IdleAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IdleAction::leave_() {
    if (*mDisablePhysics_d)
        mActor->sub_71011DABC0(&_28);
    if (mActor->getName() == "GameROMPlayer") {
        const sead::SafeString event_name = ksys::evt::Manager::instance()->sub_7100DB1184();
        if (event_name == "Demo143_4" || event_name == "Demo720_0") {
            if (auto* controller = mActor->getCharacterController())
                controller->sub_7100F5EC30();
        }
    }
}

void IdleAction::loadParams_() {
    getDynamicParam(&mDisablePhysics_d, "DisablePhysics");
}

void IdleAction::calc_() {
    if (isFinished() || isFailed())
        return;
    setFinished();
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
