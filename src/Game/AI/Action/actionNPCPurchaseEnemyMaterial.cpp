#include "Game/AI/Action/actionNPCPurchaseEnemyMaterial.h"
#include "Game/AI/aiUnk_71007377D4.h"
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
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (_1c >= 2) {
        if (ksys::gdt::getFlag_Shop_DecideTrig(false)) {
            ksys::gdt::setFlag_Shop_IsDecide(true, false);
            ksys::gdt::setFlag_Shop_CurrentItemState(ksys::gdt::getFlag_Shop_ItemState(false),
                                                     false);
            const char* name;
            ksys::gdt::getFlag_Shop_SelectItemName(&name, false);
            ksys::gdt::setFlag_Shop_SelectItemNameJpn(name, false);
            ksys::gdt::setFlag_Shop_DecideTrig(false, false);
            setFinished();
        } else if (!ui::sub_7100A983DC()) {
            setFinished();
        }
    } else {
        ++_1c;
    }
}

}  // namespace uking::action
