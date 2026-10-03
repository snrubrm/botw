#include "Game/AI/Action/actionNPCDyeShopSelectMaterial.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
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
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
