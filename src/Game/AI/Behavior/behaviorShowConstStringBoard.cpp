#include "Game/AI/Behavior/behaviorShowConstStringBoard.h"

namespace uking::behavior {

// NON_MATCHING: the members after 0x98 are not declared yet (placeholder bytes)
ShowConstStringBoard::ShowConstStringBoard(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ShowConstStringBoard::~ShowConstStringBoard() = default;

void ShowConstStringBoard::m8() {}

void ShowConstStringBoard::m9() {}

}  // namespace uking::behavior
