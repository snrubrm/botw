#include "Game/gameStageStateMaybe.h"
#include "KingSystem/System/GameTool.h"

namespace uking {

StageStateMaybe* StageStateMaybe::sInstance;

bool StageStateMaybe::isActiveNaviMaybe(const Unk_71024f13f0* tool) {
    StageStateMaybe* state = sInstance;
    return state->_58[state->_38]->m24() == tool;
}

}  // namespace uking
