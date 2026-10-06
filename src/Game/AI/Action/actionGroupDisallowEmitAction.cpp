#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include "Game/AI/Action/actionGroupDisallowEmitAction.h"

namespace uking::action {

GroupDisallowEmitAction::GroupDisallowEmitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GroupDisallowEmitAction::~GroupDisallowEmitAction() = default;

bool GroupDisallowEmitAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool GroupDisallowEmitAction::oneShot_() {
    auto* group = aal::SystemAccessor::getGroupMgr()->findGroup(mGroupName_d);
    if (!group)
        group = aal::SystemAccessor::getGroupMgr()->findGroupFolder(mGroupName_d);
    if (!group)
        return false;
    group->allowEmit(false);
    return true;
}

void GroupDisallowEmitAction::loadParams_() {
    getDynamicParam(&mGroupName_d, "GroupName");
}

}  // namespace uking::action
