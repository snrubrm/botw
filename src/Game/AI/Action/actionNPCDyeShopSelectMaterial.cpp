#include "Game/AI/Action/actionNPCDyeShopSelectMaterial.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCDyeShopSelectMaterial::NPCDyeShopSelectMaterial(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCDyeShopSelectMaterial::~NPCDyeShopSelectMaterial() = default;

bool NPCDyeShopSelectMaterial::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCDyeShopSelectMaterial::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::gdt::setFlag_Shop_IsDecide(false);
    if (ui::sub_7100A98558()) {
        ui::sub_7100A98580();
    } else {
        _1c = 0;
        ui::sub_7100A9853C();
    }
}

void NPCDyeShopSelectMaterial::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCDyeShopSelectMaterial::loadParams_() {}

void NPCDyeShopSelectMaterial::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (_1c >= 2) {
        const s32 item_state = ksys::gdt::getFlag_Shop_ItemState();
        const bool decide = ksys::gdt::getFlag_Shop_DecideTrig();
        const bool shop_open = ui::sub_7100A98558();
        if ((item_state == 0 && decide) || !shop_open) {
            if (decide) {
                ksys::gdt::setFlag_Shop_IsDecide(true);
                ksys::gdt::setFlag_Shop_DecideTrig(false);
            }
            setFinished();
        }
    } else {
        _1c++;
    }
}

}  // namespace uking::action
