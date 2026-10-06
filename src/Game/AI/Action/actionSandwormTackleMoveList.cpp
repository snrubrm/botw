#include "Game/AI/Action/actionSandwormTackleMove.h"

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

}  // namespace uking::action
