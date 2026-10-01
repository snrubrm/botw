#include "Game/AI/Action/actionNPCCalculateMaterialValue.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

NPCCalculateMaterialValue::NPCCalculateMaterialValue(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCCalculateMaterialValue::~NPCCalculateMaterialValue() = default;

bool NPCCalculateMaterialValue::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    return gdm->setS32(ui::PauseMenuDataMgr::instance()->calculateEnemyMaterialMamo(),
                       "AllMaterialValue");
}

}  // namespace uking::action
