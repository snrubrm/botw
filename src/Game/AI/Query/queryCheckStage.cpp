#include "Game/AI/Query/queryCheckStage.h"
#include <evfl/Query.h>
#include "KingSystem/System/StageInfo.h"

namespace uking::query {

CheckStage::CheckStage(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckStage::~CheckStage() = default;

int CheckStage::doQuery() {
    return ksys::StageInfo::sIsRemainsFire;
}

void CheckStage::loadParams(const evfl::QueryArg& arg) {}

void CheckStage::loadParams() {}

}  // namespace uking::query
