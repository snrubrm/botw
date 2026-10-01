#include "Game/AI/Action/actionReqCreateManufactedEquipItem.h"
#include "Game/Actor/actPlayerCreateMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

ReqCreateManufactedEquipItem::ReqCreateManufactedEquipItem(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ReqCreateManufactedEquipItem::~ReqCreateManufactedEquipItem() = default;

bool ReqCreateManufactedEquipItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ReqCreateManufactedEquipItem::oneShot_() {
    auto* mgr = act::CreatePlayerEquipActorMgr::instance();
    if (!mgr)
        return false;
    const char* name;
    ksys::gdt::getFlag_Shop_ManufacturedEquipItemName(&name);
    const int color = ksys::gdt::getFlag_Shop_ManufacturedEquipItemColor();
    mgr->requestCreateArmor(name, color, sead::SafeString::cEmptyString);
    return true;
}

void ReqCreateManufactedEquipItem::loadParams_() {}

}  // namespace uking::action
