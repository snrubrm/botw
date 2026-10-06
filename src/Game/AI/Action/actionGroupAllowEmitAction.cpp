#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include "Game/AI/Action/actionGroupAllowEmitAction.h"

namespace uking::action {

GroupAllowEmitAction::GroupAllowEmitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GroupAllowEmitAction::~GroupAllowEmitAction() = default;

bool GroupAllowEmitAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool GroupAllowEmitAction::oneShot_() {
    auto* group = aal::SystemAccessor::getGroupMgr()->findGroup(mGroupName_d);
    if (!group)
        group = aal::SystemAccessor::getGroupMgr()->findGroupFolder(mGroupName_d);
    if (!group)
        return false;
    group->allowEmit(true);
    return true;
}

void GroupAllowEmitAction::loadParams_() {
    getDynamicParam(&mGroupName_d, "GroupName");
}

}  // namespace uking::action
