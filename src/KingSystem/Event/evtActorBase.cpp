#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtAction.h"

namespace ksys::evt {

// 0x7100da9bb0 (CSV evt::ActorBase::m2), 0x7100da9be8 (m3)
ActorBase::~ActorBase() = default;

// 0x7100da9c2c
ActionBase* ActorBase::getActionByName(const evfl::ResAction* res) const {
    for (s32 i = 0; i < mActions.size(); ++i) {
        ActionBase* action = mActions.at(i);
        if (action->getRes() == res)
            return action;
    }
    return nullptr;
}

// 0x7100daaa10
bool ActorBase::m6() {
    if (mState == 0x15)
        mState = 0x16;
    return true;
}

// 0x7100dab5f8
void ActorBase::play() {
    if (!(mFlags & 1))
        return;

    for (s32 i = 0; i < mActions.size(); ++i) {
        ActionBase* action = mActions.at(i);
        if (mState == 6) {
            m4();
        } else if (_1b4 && !mLink.hasProc()) {
            mState = 6;
        }
        action->play();
    }
}

// 0x7100dab86c
bool Actor::x_0() {
    for (s32 i = 0; i < mActions.size(); ++i) {
        if (!static_cast<Action*>(mActions.at(i))->x())
            return false;
    }
    return true;
}

// 0x7100dac578
void Actor::sub_7100DAC578() {
    for (s32 i = 0; i < mActions.size(); ++i)
        static_cast<Action*>(mActions.at(i))->sub_7100DA7DC4();
}

// 0x7100dab548
void Actor::sub_7100DAB548() {
    if (u32(mState - 9) <= 1) {
        if (auto* actor = sead::DynamicCast<act::Actor>(mLink.getProc(nullptr)))
            actor->sleep(act::BaseProc::SleepWakeReason::_0);
    }
}

// 0x7100daa2e0
bool Actor::sub_7100DAA2E0() const {
    if (u32(mState - 9) < 5)
        return true;
    switch (mState) {
    case 14 ... 20:
    case 27:
        return true;
    default:
        return false;
    }
}

}  // namespace ksys::evt
