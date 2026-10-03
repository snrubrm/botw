#include "KingSystem/Event/evtActorBase.h"
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

}  // namespace ksys::evt
