#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <evfl/ResActor.h>
#include <math/seadMatrix.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::evt {

class ActionBase;
class Action;
class ActorBinding;
class EventActorSet;
class EventFlow;
class Query;

// The event-side actor (CSV evt::ActorBase; the 0x1d0-byte evt::Actor derives from it, ctor 0x7100da7ed8 takes an
// ActorBinding, the factory is ukingEventMgr::makeActor). Only the members used so far are modelled; the slots that
// are not decompiled yet are pure here.
class ActorBase {
public:
    // 0x7100da7ed8 (CSV evt::ActorBase::ctor; not decompiled)
    ActorBase(ActorBinding* binding, EventActorSet* set, sead::Heap* heap);
    SEAD_RTTI_BASE(ActorBase)

    virtual ~ActorBase();
    virtual bool m4() = 0;
    // 0x7100daa670 (CSV evt::ActorBase::m5; not decompiled)
    virtual void m5(bool a1, bool a2);
    // 0x7100daaa10 (CSV evt::ActorBase::m6): state 0x15 -> 0x16, returns true
    virtual bool m6();
    virtual void m7(bool a1, bool a2) = 0;
    virtual void m8();
    // 0x7100dab5f8 (CSV evt::ActorBase::play)
    virtual void play();
    virtual void m10() = 0;
    virtual void m11() = 0;
    virtual void m12() = 0;

    // 0x7100da9c2c (CSV evt::ActorBase::getActionByName): the action whose resource is `res`
    ActionBase* getActionByName(const evfl::ResAction* res) const;
    // 0x7100da9c90 (CSV unnamed; placeholder name; declared only: the original searches `res` in two loops)
    Query* getQueryByRes(const evfl::ResQuery* res) const;

    // 0x7100dab470: applies the event actor state to the linked actor.
    void sub_7100DAB470();

    /* 0x008 */ act::BaseProcLink mLink;
    /* 0x018 */ act::BaseProcHandle mHandle;
    /* 0x028 */ sead::FixedSafeString<64> mName;
    /* 0x080 */ sead::FixedSafeString<64> mSubName;
    /* 0x0d8 */ s32 mState;
    /* 0x0dc */ u8 _dc[0xe8 - 0xdc];
    /* 0x0e8 */ sead::PtrArray<ActionBase> mActions;  // the elements are Action objects
    /* 0x0f8 */ sead::PtrArray<Query> mQueries;
    /* 0x108 */ void* _108;  // passed to EventSystem::x_0/x_1 (Actor::m4); type unknown
    /* 0x110 */ EventActorSet* mActorSet;
    // Produced by Actor::init / da8cd8 and consumed by dab470.
    /* 0x118 */ sead::Matrix34f mTransform;
    /* 0x148 */ sead::Matrix34f mOriginalTransform;
    /* 0x178 */ sead::Matrix34f mAppliedTransform;
    u8 _1a8[0x1b4 - 0x1a8];
    /* 0x1b4 */ bool _1b4;
    /* 0x1b5 */ u8 _1b5[0x1b8 - 0x1b5];
    /* 0x1b8 */ void* _1b8;
    /* 0x1c0 */ void* _1c0;
    /* 0x1c8 */ u32 mFlags;
};

// The 0x1d0-byte event-side actor (CSV evt::Actor). Only the non-virtual members used so far are declared; it is
// abstract here like its base.
class Actor : public ActorBase {
public:
    // 0x71008a8b78 (CSV evt::Actor::ctor)
    Actor(ActorBinding* binding, EventActorSet* set, sead::Heap* heap);
    SEAD_RTTI_OVERRIDE(Actor, ActorBase)
    // D1 0x71008a8bac (CSV evt::Actor::m2), D0 0x71008a8e68 (m3)
    ~Actor() override;

    bool m4() override;
    void m7(bool a1, bool a2) override;
    void m8() override;
    void m10() override;
    void m11() override;
    void m12() override;

    // 0x71008a8be0 (CSV unnamed; placeholder name): called by the destructor
    void sub_71008A8BE0();

    // 0x7100da82c0 (CSV evt::Actor::init; not decompiled)
    void init(ActorBinding* binding, EventFlow* slot);
    // 0x7100dab86c (CSV evt::Actor::x_0)
    bool x_0();
    // 0x7100dab548 / 0x7100dac578 (CSV unnamed; placeholder names)
    void sub_7100DAB548();
    void sub_7100DAC578();
    // 0x7100daa2e0 (CSV unnamed; placeholder name): the state is one of 9-20 / 27
    bool sub_7100DAA2E0() const;

private:
    /* 0x1cc */ s32 _1cc = 0;
};
KSYS_CHECK_SIZE_NX150(Actor, 0x1d0);

}  // namespace ksys::evt
