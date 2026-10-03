#pragma once

#include <basis/seadTypes.h>
#include <evfl/Action.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace ksys::evt {

class ActionContext;
class ActorBase;

// The event system's per-actor action state (CSV evt::ActionBase / evt::Action; 0x720 bytes, created by
// ukingEventMgr::makeAction 0x71008ac620). It owns 32 slots, each an evfl::ActionDoneHandler plus the ActionContext
// the handler belongs to. Only the constructor / destructor / RTTI and the first virtual slots are modelled.
class ActionBase {
public:
    struct Slot {
        evfl::ActionDoneHandler handler;
        ActionContext* context;
    };

    SEAD_RTTI_BASE(ActionBase)

    ActionBase(const void* action_data, ActorBase* actor);
    virtual ~ActionBase();

    // 0x7100da69bc (CSV evt::ActionBase::m4): starts an action in `slot`, moving `handler` into it. Not decompiled.
    virtual void m4(Slot* slot, const evfl::ActionArg& arg, evfl::ActionDoneHandler* handler) = 0;
    // 0x7100da6c58 (CSV evt::ActionBase::m5)
    virtual void m5(ActionContext* context, const evfl::ActionArg& arg);
    // 0x7100da6cb4 (CSV evt::ActionBase::m6). Not decompiled.
    virtual void m6(ActionContext* context, const evfl::ActionArg& arg) = 0;
    // 0x7100da7ed4 (CSV evt::ActionBase::m7_null)
    virtual void m7();
    // 0x7100da6d24 (CSV evt::ActionBase::play). Not decompiled.
    virtual void play() = 0;

protected:
    /* 0x008 */ ActorBase* mActor;
    /* 0x010 */ Slot mSlots[32];
    /* 0x710 */ const void* mActionData;
    /* 0x718 */ s32 _718 = 0;
};

// CSV evt::Action (vtable 0x246c8a8).
class Action : public ActionBase {
public:
    SEAD_RTTI_OVERRIDE(Action, ActionBase)

    Action(const void* action_data, ActorBase* actor);
    ~Action() override;

    // Not decompiled (0x71008a7278 / 0x71008a7758 / 0x71008a7784 / 0x71008a7788; m6 is a tail call to ActionBase::m6).
    void m4(Slot* slot, const evfl::ActionArg& arg, evfl::ActionDoneHandler* handler) override = 0;
    void m5(ActionContext* context, const evfl::ActionArg& arg) override = 0;
    void m6(ActionContext* context, const evfl::ActionArg& arg) override = 0;
    void m7() override = 0;

private:
    /* 0x71c */ s32 _71c = 0;
};

}  // namespace ksys::evt
