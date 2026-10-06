#include "Game/AI/Action/actionDemoResetActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"

namespace uking::action {

DemoResetActor::DemoResetActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoResetActor::~DemoResetActor() = default;

bool DemoResetActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool DemoResetActor::oneShot_() {
    ksys::act::BaseProcMgr::ProcIteratorContext context(*ksys::act::BaseProcMgr::instance(), {});
    while (auto* proc = context.next()) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
            if (proc->getName() == mActorName_d)
                actor->becomePreActor(ksys::act::Actor::DeleteType::_2,
                                      ksys::act::BaseProc::DeleteReason::_a);
        }
    }
    return true;
}

void DemoResetActor::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action
