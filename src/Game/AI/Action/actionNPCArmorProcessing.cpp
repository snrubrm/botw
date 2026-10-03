#include "Game/AI/Action/actionNPCArmorProcessing.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

NPCArmorProcessing::NPCArmorProcessing(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCArmorProcessing::~NPCArmorProcessing() = default;

bool NPCArmorProcessing::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCArmorProcessing::enter_(ksys::act::ai::InlineParamPack* params) {
    _29 = false;
    ksys::gdt::setFlag_Shop_IsDecide(false);
}

void NPCArmorProcessing::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCArmorProcessing::loadParams_() {
    getDynamicParam(&mArmorProcessingRank_d, "ArmorProcessingRank");
}

void NPCArmorProcessing::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (_29) {
        if (ui::sub_7100A98498()) {
            if (!ksys::gdt::getFlag_Shop_DecideTrig())
                return;
            ksys::gdt::setFlag_Shop_IsDecide(true);
            ksys::gdt::setFlag_Shop_CurrentItemState(ksys::gdt::getFlag_Shop_ItemState());
            const char* name;
            ksys::gdt::getFlag_Shop_SelectItemName(&name);
            ksys::gdt::setFlag_PlacedItemName(name);
            ksys::gdt::setFlag_Shop_SelectItemNameJpn(name);
            ksys::gdt::setFlag_Shop_DecideTrig(false);
        }
        setFinished();
    } else {
        const s32 rank = mArmorProcessingRank_d ? *mArmorProcessingRank_d : 2;
        if (ui::sub_7100A98498())
            ui::sub_7100A9826C();
        else
            ui::sub_7100A98474(rank);
        _29 = true;
    }
}

}  // namespace uking::action
