#pragma once

#include <basis/seadTypes.h>
#include <evfl/Action.h>
#include <evfl/ResActor.h>
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

    ActionBase(const evfl::ResAction* res, ActorBase* actor);
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

    const evfl::ResAction* getRes() const { return mRes; }

    // 0x7100da6fe8 (CSV evt::ActionBase::x): finishes every slot's action and releases its context
    void x();

    // 0x7100da70a8 (2.7 KB, declaration only): the evfl action handler, run on the Action behind
    // `arg.action_user_data` (see ActorManager::actionHandler)
    void sub_7100DA70A8(const evfl::ActionArg& arg, evfl::ActionDoneHandler& handler);

protected:
    /* 0x008 */ ActorBase* mActor;
    /* 0x010 */ Slot mSlots[32];
    /* 0x710 */ const evfl::ResAction* mRes;
    /* 0x718 */ s32 _718 = 0;
};

// CSV evt::Action (vtable 0x246c8a8).
class Action : public ActionBase {
public:
    SEAD_RTTI_OVERRIDE(Action, ActionBase)

    Action(const evfl::ResAction* res, ActorBase* actor);
    ~Action() override;

    // Not decompiled (0x71008a7278 / 0x71008a7758 / 0x71008a7784 / 0x71008a7788; m6 is a tail call to ActionBase::m6).
    void m4(Slot* slot, const evfl::ActionArg& arg, evfl::ActionDoneHandler* handler) override = 0;
    void m5(ActionContext* context, const evfl::ActionArg& arg) override = 0;
    void m6(ActionContext* context, const evfl::ActionArg& arg) override = 0;
    void m7() override = 0;

    // 0x7100da7c44 (CSV evt::Action::x): true if no slot has a running context
    bool x();
    // 0x7100da7c8c: for every slot whose context passes statusStuff_0(): clears the slot's handler (called by
    // ActorBase::m5)
    void sub_7100DA7C8C();
    // 0x7100da7dc4: releases every slot context that is not flagged 0x20 (called from 0x7100dac578)
    void sub_7100DA7DC4();
    // 0x7100da7d1c (CSV evt::Action::x_0): finishes `slot`'s action and releases its context
    void x_0(Slot* slot);

private:
    /* 0x71c */ s32 _71c = 0;
};

}  // namespace ksys::evt
