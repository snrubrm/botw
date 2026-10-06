#include "Game/AI/Query/queryCheckMasterSwordState.h"
#include <evfl/Query.h>
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUtils.h"

namespace uking::query {

CheckMasterSwordState::CheckMasterSwordState(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckMasterSwordState::~CheckMasterSwordState() = default;

int CheckMasterSwordState::doQuery() {
    if (auto* item = ui::PauseMenuDataMgr::instance()->getMasterSword())
        return ui::sub_7100AA6F90(*item);
    return 3;
}

void CheckMasterSwordState::loadParams(const evfl::QueryArg& arg) {}

void CheckMasterSwordState::loadParams() {}

}  // namespace uking::query
