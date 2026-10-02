#include "Game/AI/Behavior/behaviorShortRangeBattleAlignment.h"

namespace uking::behavior {

ShortRangeBattleAlignment::ShortRangeBattleAlignment(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

void ShortRangeBattleAlignment::loadParams() {
    getStaticParam(&mMode_s, "Mode");
    getStaticParam(&mOffsetY_s, "OffsetY");
}

}  // namespace uking::behavior
