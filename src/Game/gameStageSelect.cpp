#include "Game/gameStageSelect.h"
#include "KingSystem/Utils/StateMachine.h"

// The state objects of the stage select menu are ksys::StateTemplate<StageSelect> (vtable 0x710245c000; the member
// functions 0x7d06a4-0x7d0738).
template class ksys::StateTemplate<uking::StageSelect>;

namespace uking {

void StageSelect::activeEnter() {}

void StageSelect::activeLeave() {}

bool StageSelect::activeReenter(void* arg) {
    return false;
}

void StageSelect::moveEnter() {}

void StageSelect::moveRun() {
    _10 = _4f0;
}

void StageSelect::moveLeave() {}

bool StageSelect::moveReenter(void* arg) {
    return false;
}

}  // namespace uking
