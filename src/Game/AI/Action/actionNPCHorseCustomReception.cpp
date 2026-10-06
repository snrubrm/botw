#include "Game/AI/Action/actionNPCHorseCustomReception.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actNPC.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

NPCHorseCustomReception::NPCHorseCustomReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCHorseCustomReception::~NPCHorseCustomReception() = default;

bool NPCHorseCustomReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCHorseCustomReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::gdt::setFlag_Shop_IsDecide(false, false);
    if (ui::sub_7100A990BC()) {
        ui::sub_7100A9826C();
        return;
    }
    _2c = 0;
    if (*mCustomItemType_d == 0) {
        if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
            _28 = npc->_f88.giveItem(mActor->getParam()->getRes().mShopData, mActor->getName(),
                                     "Normal", false);
            if (_28)
                ui::sub_7100A99060(&npc->_f88);
        }
    } else {
        _28 = true;
        switch (*mCustomItemType_d) {
        case 1:
            ui::sub_7100A99084();
            break;
        case 2:
            ui::sub_7100A990A0();
            break;
        }
    }
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
