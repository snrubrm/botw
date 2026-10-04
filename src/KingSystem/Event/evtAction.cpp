#include "KingSystem/Event/evtAction.h"
#include "KingSystem/Event/evtActionContext.h"

namespace ksys::evt {

// 0x71008a71fc (CSV evt::Action::ctor)
Action::Action(const evfl::ResAction* res, ActorBase* actor) : ActionBase(res, actor) {}

// 0x71008a7230 (CSV evt::Action::dtor), 0x71008a7244 (dtorDelete)
// (user-provided empty body: the original keeps the vtable pointer store, see uiScreenDtors2.cpp)
Action::~Action() { ; }

// 0x7100da7c44
bool Action::x() {
    for (s64 i = 0; i < 32; ++i) {
        ActionContext* context = mSlots[i].context;
        if (context && !(context->_af4 & 0x20) && context->mStatus != 0 && context->mStatus < 5)
            return false;
    }
    return true;
}

// 0x7100da7c8c
void Action::sub_7100DA7C8C() {
    for (s64 i = 0; i < 32; ++i) {
        ActionContext* context = mSlots[i].context;
        if (context && !(context->_af4 & 0x20) && context->statusStuff_0())
            mSlots[i].handler.Reset();
    }
}

// 0x7100da7d1c
void Action::x_0(Slot* slot) {
    if (slot->context->statusStuff(true))
        slot->handler.Invoke();
    ActionContext* context = slot->context;
    if (context && !(context->_af4 & 0x20)) {
        context->reset();
        slot->context = nullptr;
    }
}

// 0x7100da7dc4
void Action::sub_7100DA7DC4() {
    for (s64 i = 0; i < 32; ++i) {
        ActionContext* context = mSlots[i].context;
        if (context && !(context->_af4 & 0x20)) {
            context->reset();
            mSlots[i].context = nullptr;
        }
    }
}

}  // namespace ksys::evt
