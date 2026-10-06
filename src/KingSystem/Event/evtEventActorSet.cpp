#include "KingSystem/Event/evtAction.h"
#include "KingSystem/Event/evtActionContext.h"
#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Event/evtActorBindings.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtManager.h"

namespace ksys::evt {

// 0x7100da23c4
EventActorSet::EventActorSet(EventFlowBase* flow)
    : _18(0), mFlow(flow), mResource(nullptr), mNoDeleteCurrentActor(false), _38(nullptr), _40(0), _44(0) {
    _50 = sead::Vector2f::zero;
    _48 = sead::Vector2f::zero;
}

// 0x7100da2408
void EventActorSet::allocActors(ActorBindings* bindings, sead::Heap* heap, EventFlow* slot) {
    if (bindings->getNumBindings() >= 1) {
        mActors.allocBuffer(bindings->getNumBindings(), heap, 8);
        for (s32 i = 0; i < bindings->getNumBindings(); ++i) {
            ActorBinding* binding = bindings->getBinding(i);
            Actor* actor = Manager::instance()->getActorFactory()->makeActor(binding, this, heap);
            actor->init(binding, slot);
            mActors.pushBack(actor);
        }
    }
    _18 = 0;
}

// NON_MATCHING: the original compares the last state (`== 6`) through a stack round trip (`str w8, [sp, #0xc]; ldr w8,
// [sp, #0xc]`), the SEAD_ENUM by-value pattern: the state is probably a SEAD_ENUM there.
// 0x7100da2618
bool EventActorSet::sub_7100DA2618(ActorBindings* bindings) {
    bool all_ready = true;
    for (s32 i = 0; i < mActors.size(); ++i) {
        Actor* actor = mActors(i);
        if (actor->m4())
            continue;
        if (actor->mState == 0x1a) {
            actor->init(bindings->getBinding(i), nullptr);
            ++_40;
        }
        if (u32(actor->mState - 0x18) >= 3)
            all_ready &= actor->mState == 6;
    }
    if (!all_ready)
        return false;
    _18 = 1;
    return true;
}

// 0x7100da2510 (D1) / 0x7100da2590 (D0)
EventActorSet::~EventActorSet() {
    for (s32 i = 0; i < mActors.size(); ++i)
        delete mActors.at(i);
    mActors.freeBuffer();
}

// 0x7100da2774
bool EventActorSet::x_3(bool a1, bool a2) {
    bool all = true;
    for (s32 i = 0; i < mActors.size(); ++i)
        all &= mActors(i)->m6();
    if (!all)
        return false;
    for (s32 i = 0; i < mActors.size(); ++i)
        mActors(i)->m7(a1, a2);
    _18 = 3;
    return true;
}

// 0x7100da283c
void EventActorSet::callActorStuff() {
    for (s32 i = 0; i < mActors.size(); ++i)
        mActors(i)->m8();
}

// 0x7100da28e8
void EventActorSet::playActors() {
    for (s32 i = 0; i < mActors.size(); ++i)
        mActors(i)->play();
}

// 0x7100da2c18
ActorBase* EventActorSet::getActorByPointer(act::BaseProc* proc) const {
    for (s32 i = 0; i < mActors.size(); ++i) {
        auto* actor = mActors.at(i);
        if (actor->mLink.hasProcById(proc))
            return actor;
    }
    return nullptr;
}

// 0x7100da2e84
ActorBase* EventActorSet::sub_7100DA2E84(act::BaseProc* proc) {
    for (s32 i = 0; i < mActors.size(); ++i) {
        auto* actor = mActors.at(i);
        if (actor->mLink.hasProcById(proc))
            return actor;
    }
    return nullptr;
}

// 0x7100da288c
void EventActorSet::x_1() {
    for (s32 i = 0; i < mActors.size(); ++i)
        mActors.at(i)->sub_7100DAB548();
}

// 0x7100da2700
void EventActorSet::sub_7100DA2700(bool a1, bool a2) {
    for (s32 i = 0; i < mActors.size(); ++i)
        mActors(i)->m5(a1, a2);
    _18 = 2;
    _44 = 0;
}

// 0x7100da3878
void EventActorSet::x_0() {
    for (s32 i = 0; i < mActors.size(); ++i)
        mActors.at(i)->sub_7100DAC578();
}

// 0x7100da3624
bool EventActorSet::x_4() {
    for (s32 i = 0; i < mActors.size(); ++i) {
        if (!mActors.at(i)->x_0())
            return false;
    }
    return true;
}

// NON_MATCHING: same instructions, but the original re-reads the (checked) action pointer for the entry instead of
// reusing the one it used for the slot test, and orders the first array reads slightly differently.
// 0x7100da375c
void EventActorSet::x_2() {
    struct Entry {
        Action* action;
        ActionBase::Slot* slot;
    };
    sead::SafeArray<Entry, 32> entries;
    s32 count = 0;

    for (s32 i = 0; i < mActors.size(); ++i) {
        auto* actor = mActors(i);
        for (s32 j = 0; j < actor->mActions.size(); ++j) {
            for (s32 k = 0; k < 32; ++k) {
                auto* action = static_cast<Action*>(actor->mActions.at(j));
                auto& slot = action->mSlots[k];
                if (slot.context && slot.context->mStatus == 6) {
                    entries[count] = {static_cast<Action*>(actor->mActions.at(j)), &slot};
                    ++count;
                }
            }
        }
    }

    for (s32 i = 0; i < count; ++i)
        entries[i].action->x_0(entries[i].slot);
}

}  // namespace ksys::evt
