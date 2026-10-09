#include "Game/gameUnk_71008ba8d8.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

// Thin UI-side wrappers around the game data flags (and a few Manager flag readers) from the 0x7100aa8000 UI TU.
namespace uking::ui {

namespace shop {

// 0x7100aa8108
void setScreenType(s32 type) {
    ksys::gdt::setFlag_Shop_ScreenType(type, false);
}

// 0x7100aa8110
void setDecideTrig(bool trig) {
    ksys::gdt::setFlag_Shop_DecideTrig(trig, false);
}

// 0x7100aa811c
void setSelectItemName(const sead::SafeString& name) {
    ksys::gdt::setFlag_Shop_SelectItemName(name, false);
}

// 0x7100aa8124
void setSelectItemPrice(s32 price) {
    ksys::gdt::setFlag_Shop_SelectItemPrice(price, false);
}

// 0x7100aa812c
void setItemState(s32 state) {
    ksys::gdt::setFlag_Shop_ItemState(state, false);
}

// 0x7100aa8134
void setSelectItemNum(s32 num) {
    ksys::gdt::setFlag_Shop_SelectItemNum(num, false);
}

// 0x7100aa813c
void setTradeItemNum(s32 num) {
    ksys::gdt::setFlag_Shop_TradeItemNum(num, false);
}

// 0x7100aa8144
void setTradePrice(s32 price) {
    ksys::gdt::setFlag_ShopTradePrice(price, false);
}

// 0x7100aa8154 (CSV unnamed; placeholder name)
void sub_7100AA8154(bool is_manufacture_equip_item) {
    ksys::gdt::setFlag_Shop_IsManufactureEquipItem(is_manufacture_equip_item, false);
}

// 0x7100aa8160 (CSV unnamed; placeholder name)
void sub_7100AA8160(s32 vacancy) {
    ksys::gdt::setFlag_Shop_SelectPictureBookVacancy(vacancy, false);
}

}  // namespace shop

// 0x7100aa814c
void setColorChangeMaterialIndex(s32 index) {
    ksys::gdt::setFlag_ColorChange_MaterialIndex(index, false);
}

// 0x7100aa8fc4
bool getMainScreenOnOff() {
    return ksys::gdt::getFlag_MainScreenOnOff(false);
}

// 0x7100aa8f78: `actor` itself, or the player if there is no actor.
// NON_MATCHING: the original tail-calls PlayerInfo::getPlayer; ours converts PlayerBase* -> Actor* and does not
// emit the tail call (and tests `actor` the other way round)
ksys::act::Actor* getPlayerActor(ksys::act::Actor* actor) {
    if (actor)
        return actor;
    if (auto* info = ksys::act::PlayerInfo::instance())
        return info->getPlayer();
    return nullptr;
}

// 0x7100aa8f94 (placeholder name): bit 29 of the player's state word at 0xc44
bool sub_7100AA8F94() {
    auto* info = ksys::act::PlayerInfo::instance();
    if (!info)
        return false;
    auto* player = info->getPlayer();
    return player && player->_c44.isOnBit(29);
}

// 0x7100a9c340 (placeholder name): bit 22 of the player's word at 0xcf0 is clear
bool sub_7100A9C340() {
    auto* info = ksys::act::PlayerInfo::instance();
    if (!info)
        return false;
    auto* player = info->getPlayer();
    return player && !player->_cf0.isOnBit(22);
}

// 0x7100a9b7bc (placeholder name): bit 22 of the word at 0xcf0 and bit 2 of the word at 0xcf8 are both clear
bool sub_7100A9B7BC() {
    auto* info = ksys::act::PlayerInfo::instance();
    if (!info)
        return false;
    auto* player = info->getPlayer();
    return player && !player->_cf0.isOnBit(22) && !player->_cf8.isOnBit(2);
}

// 0x7100aa379c (placeholder name): the two jump / action button ids 28 and 29 swap their icons when the
// JumpButtonChange option is set
s32 sub_7100AA379C(s32 button) {
    if (button == 28)
        return ksys::gdt::getFlag_JumpButtonChange(false) ? 8 : 7;
    if (button == 29)
        return ksys::gdt::getFlag_JumpButtonChange(false) ? 7 : 8;
    return button;
}

// 0x7100aa8e5c / 0x7100aa8e9c (placeholder names): bit 21 / bit 22 of the Manager's flag word.
bool sub_7100AA8E5C() {
    if (!uiManagerInitialised())
        return false;
    return (Manager::instance()->_64c30 & 0x200000) != 0;
}

bool sub_7100AA8E9C() {
    if (!uiManagerInitialised())
        return false;
    return (Manager::instance()->_64c30 & 0x400000) != 0;
}

// 0x7100aa8edc (placeholder name)
bool sub_7100AA8EDC() {
    return sub_71008BB804() || sub_71008BB600() || sub_71008BB830() || someEventMgrCheck();
}

// 0x7100aa8f30 / 0x7100aa8f50 (placeholder names): bit 13 / bit 18 of the Manager's flag word.
bool sub_7100AA8F30() {
    return (Manager::instance()->_64c30 & 0x2000) != 0;
}

bool sub_7100AA8F50() {
    return (Manager::instance()->_64c30 & 0x40000) != 0;
}

// 0x7100aa8f70
bool sub_7100AA8F70() {
    return isActiveEventDemo000Or001Or002();
}

// 0x7100aa948c (CSV uiManager::x_11) / 0x7100aa94a8 (placeholder name): the bytes at 0x64b14 / 0x64b15.
u8 sub_7100AA948C() {
    return Manager::instance()->_64b14;
}

bool sub_7100AA94A8() {
    return Manager::instance()->_64b15;
}

}  // namespace uking::ui
