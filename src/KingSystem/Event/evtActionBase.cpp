#include "KingSystem/Event/evtAction.h"
#include "KingSystem/ActorSystem/aiDemoRootAI.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtActionContext.h"
#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Event/evtEventFlow.h"

namespace ksys::evt {

// 0x7100da6748 (CSV evt::ActionBase::ctor)
ActionBase::ActionBase(const evfl::ResAction* res, ActorBase* actor)
    : mActor(actor), mRes(res) {
    for (auto& slot : mSlots)
        slot.context = nullptr;
}

// 0x7100da6818 (CSV evt::ActionBase::dtor), 0x7100da685c (m3)
ActionBase::~ActionBase() = default;

// 0x7100da69bc
// NON_MATCHING: the ActionDoneHandler move (lib/EventFlow ore::IntrusiveListNode::operator=) links the node differently:
// the original also relinks the destination node's old neighbour
void ActionBase::m4(Slot* slot, const evfl::ActionArg& arg, evfl::ActionDoneHandler* handler) {
    mActor->m12();
    slot->context->setStatus2(arg);
    slot->context->x_3(&mActor->mLink);
    slot->handler = std::move(*handler);

    if (auto* actor = sead::DynamicCast<act::Actor>(mActor->mLink.getProc(nullptr, nullptr))) {
        auto* demo_ai = actor->getRootAi()->sub_7100D65CBC();
        if (demo_ai->sub_7100D62D18(mRes->name.Get()->data()) || !(slot->context->_af4 & 1)) {
            if (slot->context->statusStuff(false))
                slot->handler.Invoke();
        }
    }

    if (mActor->mActorSet->mFlow->hasFlag(EventFlowBase::Flag::_1000) && slot->context &&
        (slot->context->_af4 & 0x21) == 1) {
        slot->handler.Invoke();
    }
    _718 = 0;
}

// 0x7100da6c58 (CSV evt::ActionBase::m5)
void ActionBase::m5(ActionContext* context, const evfl::ActionArg& arg) {
    mActor->m12();
    context->setStatus1(arg);
    context->x_3(&mActor->mLink);
    _718 = 0;
}

// 0x7100da6cb4
void ActionBase::m6(ActionContext* context, const evfl::ActionArg& arg) {
    context->setStatus1_0(arg);
    if (mActor->mActorSet->mFlow->m10(arg))
        context->_af4 |= 8;
    context->sub_7100DA53E4(&mActor->mLink);
}

// 0x7100da6fe8
void ActionBase::x() {
    for (s64 i = 0; i < 32; ++i) {
        Slot& slot = mSlots[i];
        ActionContext* context = slot.context;
        if (context && !(context->_af4 & 0x20)) {
            if (context->statusStuff(true))
                slot.handler.Invoke();
            if (slot.context)
                slot.context->reset();
            slot.context = nullptr;
        }
    }
}

// 0x7100da7ed4 (CSV evt::ActionBase::m7_null)
void ActionBase::m7() {}

}  // namespace ksys::evt
