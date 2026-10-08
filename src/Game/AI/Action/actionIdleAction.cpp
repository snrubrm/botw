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
    if (*mDisablePhysics_d)
        _28 = mActor->sub_71011DA9F8();
    if (mActor->getName() == "GameROMPlayer") {
        const sead::SafeString event_name = ksys::evt::Manager::instance()->sub_7100DB1184();
        if (event_name == "Demo143_4") {
            if (auto* controller = mActor->getCharacterController()) {
                controller->sub_7100F5F6FC(sead::Vector3f::zero);
                controller->sub_7100F5FB24(sead::Vector3f::zero);
                controller->sub_7100F60500(mActor->getMtx());
                controller->sub_7100F5EC44();
            }
        }
    }
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
