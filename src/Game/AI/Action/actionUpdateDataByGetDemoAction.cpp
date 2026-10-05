#include "Game/AI/Action/actionUpdateDataByGetDemoAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

// Existing global helper names retained; original source namespaces are unknown.
void callGetDemoHandler(ksys::act::Actor* actor, const sead::SafeString& name);
void callGetDemoHandler2(ksys::act::Actor* actor, ksys::act::Actor* item,
                         const sead::SafeString& name);

namespace uking::action {

UpdateDataByGetDemoAction::UpdateDataByGetDemoAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

UpdateDataByGetDemoAction::~UpdateDataByGetDemoAction() = default;

bool UpdateDataByGetDemoAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void UpdateDataByGetDemoAction::loadParams_() {}

bool UpdateDataByGetDemoAction::oneShot_() {
    auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
    if (parent && ksys::act::hasTag(parent, 0x4abb738e))
        callGetDemoHandler2(parent, mActor, mActor->getName());
    else
        callGetDemoHandler(mActor, mActor->getName());
    return true;
}

}  // namespace uking::action
