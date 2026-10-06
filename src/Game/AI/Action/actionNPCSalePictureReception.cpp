#include "Game/AI/Action/actionNPCSalePictureReception.h"
#include "Game/Actor/actNPC.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

NPCSalePictureReception::NPCSalePictureReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSalePictureReception::~NPCSalePictureReception() = default;

bool NPCSalePictureReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCSalePictureReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::gdt::setFlag_Shop_IsDecide(false, false);
    if (ui::sub_7100A98304()) {
        ui::sub_7100A9826C();
        return;
    }
    _30 = false;
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor)) {
        if (npc->_f88.giveItem(mActor->getParam()->getRes().mShopData, mActor->getName(),
                               mTableName_d, false))
            _30 = true;
        _34 = 0;
        ui::sub_7100A985B8(&npc->_f88);
    }
}

void NPCSalePictureReception::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCSalePictureReception::loadParams_() {
    getDynamicParam(&mTableName_d, "TableName");
}

void NPCSalePictureReception::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (_30) {
        if (_34 >= 2) {
            if (ksys::gdt::getFlag_Shop_DecideTrig()) {
                ksys::gdt::setFlag_Shop_IsDecide(true);
                ksys::gdt::setFlag_Shop_CurrentItemState(ksys::gdt::getFlag_Shop_ItemState());
                const char* name;
                ksys::gdt::getFlag_Shop_SelectItemName(&name);
                ksys::gdt::setFlag_Shop_SelectItemNameJpn(name);
                ksys::gdt::setFlag_Shop_DecideTrig(false);
                setFinished();
            }
            if (!ui::sub_7100A98304()) {
                if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
                    npc->_f88.sub_710091D030(mActor->getName());
                setFinished();
            }
        } else {
            _34 = _34 + 1;
        }
    } else {
        setFailed();
    }
}

}  // namespace uking::action
