#include "Game/AI/Action/actionNPCPurchaseEnemyMaterial.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCPurchaseEnemyMaterial::NPCPurchaseEnemyMaterial(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCPurchaseEnemyMaterial::~NPCPurchaseEnemyMaterial() = default;

bool NPCPurchaseEnemyMaterial::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCPurchaseEnemyMaterial::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::gdt::setFlag_Shop_IsDecide(false);
    if (ui::sub_7100A983DC()) {
        ui::sub_7100A9826C();
    } else {
        _1c = 0;
        ui::sub_7100A98394();
    }
}

void NPCPurchaseEnemyMaterial::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
