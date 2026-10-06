#include "Game/AI/Action/actionSandwormTackleMove.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

// Out of line in the original (a TU of its own around 0x71f6dc); kept apart from the actions so that their destructors
// do not inline these helpers.
namespace uking::action {

// Deletes all targets (called from the owners' destructors).
void Unk_SandwormTackleMoveList::sub_71F858() {
    while (mTargets.size() > 0) {
        if (auto* target = mTargets.popBack())
            delete target;
    }
}

void Unk_SandwormTackleMoveList::sub_71FEFC() {
    for (s32 i = 0, n = mTargets.size(); i < n; ++i) {
        auto* target = mTargets.at(i);
        target->_38.reset();
        target->_58 = 0;
    }
}

bool Unk_SandwormTackleMoveList::sub_71FF70(const ksys::MessageAck* ack) {
    for (s32 i = 0, n = mTargets.size(); i < n; ++i) {
        if (mTargets.at(i)->sub_710073E5E0(ack)) {
            if (mTargets(i)->_58 == 2)
                xlinkSearchAndEmit(mActor, "BombEatAngry", 2, nullptr);
            return true;
        }
    }
    return false;
}

bool Unk_SandwormTackleMoveList::sub_71FEB4() const {
    for (s32 i = 0, n = mTargets.size(); i < n; ++i) {
        if (mTargets(i)->_58 == 1)
            return true;
    }
    return false;
}

}  // namespace uking::action
