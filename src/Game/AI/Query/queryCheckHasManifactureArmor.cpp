#include "Game/AI/Query/queryCheckHasManifactureArmor.h"
#include <evfl/Query.h>
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::query {

CheckHasManifactureArmor::CheckHasManifactureArmor(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckHasManifactureArmor::~CheckHasManifactureArmor() = default;

int CheckHasManifactureArmor::doQuery() {
    const s32 revival_num = ksys::gdt::getFlag_FairyRevivalNum();
    if (auto* mgr = ui::PauseMenuDataMgr::instance())
        return mgr->armorShopStuff(revival_num + 1);
    return 0;
}

void CheckHasManifactureArmor::loadParams(const evfl::QueryArg& arg) {}

void CheckHasManifactureArmor::loadParams() {}

}  // namespace uking::query
