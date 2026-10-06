#include "Game/AI/Action/actionNPCHorseCustomReception.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

NPCHorseCustomReception::NPCHorseCustomReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCHorseCustomReception::~NPCHorseCustomReception() = default;

bool NPCHorseCustomReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCHorseCustomReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCHorseCustomReception::loadParams_() {
    getDynamicParam(&mCustomItemType_d, "CustomItemType");
}

void NPCHorseCustomReception::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (_28) {
        if (_2c >= 2) {
            if (ksys::gdt::getFlag_Shop_DecideTrig(false)) {
                ksys::gdt::setFlag_Shop_IsDecide(true, false);
                ksys::gdt::setFlag_Shop_CurrentItemState(ksys::gdt::getFlag_Shop_ItemState(false),
                                                         false);
                const char* name;
                ksys::gdt::getFlag_Shop_SelectItemName(&name, false);
                ksys::gdt::setFlag_Shop_SelectItemNameJpn(name, false);
                ksys::gdt::setFlag_Shop_DecideTrig(false, false);
                setFinished();
            } else if (!ui::sub_7100A990BC()) {
                setFinished();
            }
        } else {
            ++_2c;
        }
    } else {
        setFailed();
    }
}

}  // namespace uking::action
