#include "Game/Actor/Action/actionForceChangeAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

namespace uking::action {

ForceChangeAction::ForceChangeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceChangeAction::~ForceChangeAction() = default;

void ForceChangeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::FixedSafeString<64> name;
    ksys::act::ai::ActionBase* action = mActor->getRootAi()->getChild(1);
    auto it = mTree_s.tokenBegin("/");
    const auto end = mTree_s.tokenEnd("/");
    while (end != it && action) {
        it.getAndForward(&name);
        action = action->changeChildLater(name);
    }
    setFinished();
}

void ForceChangeAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceChangeAction::loadParams_() {
    getStaticParam(&mTree_s, "Tree");
}

void ForceChangeAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
