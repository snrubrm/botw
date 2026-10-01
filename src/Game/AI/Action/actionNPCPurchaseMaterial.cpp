#include "Game/AI/Action/actionNPCPurchaseMaterial.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

NPCPurchaseMaterial::NPCPurchaseMaterial(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCPurchaseMaterial::~NPCPurchaseMaterial() = default;

bool NPCPurchaseMaterial::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    const s32 value = ui::PauseMenuDataMgr::instance()->calculateEnemyMaterialMamo();
    if (!gdm->setS32(value, "AllMaterialValue"))
        return false;
    gdm->incrementS32(value, "CurrentMamo");
    ui::PauseMenuDataMgr::instance()->removeAllEnemyMaterials();
    return true;
}

}  // namespace uking::action
