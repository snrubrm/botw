#include "KingSystem/Event/evtAction.h"
#include "KingSystem/Event/evtActionContext.h"
#include "KingSystem/Event/evtActorBase.h"

namespace ksys::evt {

// 0x7100da6748 (CSV evt::ActionBase::ctor)
ActionBase::ActionBase(const evfl::ResAction* res, ActorBase* actor)
    : mActor(actor), mRes(res) {
    for (auto& slot : mSlots)
        slot.context = nullptr;
}

// 0x7100da6818 (CSV evt::ActionBase::dtor), 0x7100da685c (m3)
ActionBase::~ActionBase() = default;

// 0x7100da6c58 (CSV evt::ActionBase::m5)
void ActionBase::m5(ActionContext* context, const evfl::ActionArg& arg) {
    mActor->m12();
    context->setStatus1(arg);
    context->x_3(&mActor->mLink);
    _718 = 0;
}

// 0x7100da7ed4 (CSV evt::ActionBase::m7_null)
void ActionBase::m7() {}

}  // namespace ksys::evt
