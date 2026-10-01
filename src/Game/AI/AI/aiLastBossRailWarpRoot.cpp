#include "Game/AI/AI/aiLastBossRailWarpRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LastBossRailWarpRoot::LastBossRailWarpRoot(const InitArg& arg) : LastBossNormalWarpRoot(arg) {}

LastBossRailWarpRoot::~LastBossRailWarpRoot() = default;

void LastBossRailWarpRoot::loadParams_() {
    LastBossNormalWarpRoot::loadParams_();
    getDynamicParam(&mRailIndex_d, "RailIndex");
}

void LastBossRailWarpRoot::m35(ksys::act::ai::InlineParamPack* params) {
    params->addInt(*mRailIndex_d, "RailIndex", -1);
}

}  // namespace uking::ai
