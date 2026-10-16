#include "Game/Actor/Action/actionEventCheckAndCreateEquip.h"
#include "Game/Actor/actPlayerCreateMgr.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"

namespace uking::action {

EventCheckAndCreateEquip::EventCheckAndCreateEquip(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventCheckAndCreateEquip::~EventCheckAndCreateEquip() = default;

bool EventCheckAndCreateEquip::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: block order of the manager / slot check and the slot dispatch (the original tests the manager
// first and keeps the two setFailed paths apart)
void EventCheckAndCreateEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* info_data = ksys::act::InfoData::instance();
    const char* profile = nullptr;
    info_data->getActorProfile(&profile, mTargetActorName_d.cstr());
    s32 slot;
    if (!profile || (slot = sub_7100116C38(profile)) == 3) {
        sead::FixedSafeString<64> group_name;
        slot = 3;
        if (ksys::act::getSameGroupActorName(&group_name, mTargetActorName_d)) {
            profile = nullptr;
            info_data->getActorProfile(&profile, group_name.cstr());
            if (profile)
                slot = sub_7100116C38(profile);
        }
    }

    act::WeaponModifierInfo modifier;
    modifier.set(*mSharpWeaponAddType_d, *mSharpWeaponAddValue_d);
    const s32 general_life = ui::getItemGeneralLife(mTargetActorName_d.cstr());
    const s32 add_life = modifier.getAddLife();

    auto* mgr = act::CreatePlayerEquipActorMgr::instance();
    if (!mgr || slot == 3) {
        setFailed();
        return;
    }

    auto* player = act::PlayerInfo::instance()->getPlayer();
    if (!player) {
        setFailed();
        return;
    }

    bool equipped;
    if (slot == 2) {
        equipped = player->m270();
    } else if (slot == 1) {
        equipped = player->m269();
    } else if (slot == 0) {
        equipped = player->m268();
    } else {
        setFinished();
        return;
    }
    if (equipped) {
        setFinished();
        return;
    }

    ui::PauseMenuDataMgr::instance()->autoEquipLastAddedItem();
    mgr->requestCreateWeapon(mTargetActorName_d, add_life + general_life, &modifier,
                             sead::SafeString::cEmptyString);

    auto* player2 = act::PlayerInfo::instance()->getPlayer();
    if (!player2)
        return;
    u32 type;
    if (slot == 2)
        type = 0x8000015;
    else if (slot == 1)
        type = 0x8000014;
    else if (slot == 0)
        type = 0x8000013;
    else
        return;
    sendMessage(*player2->getMesTransceiverId(), ksys::MessageType(type), nullptr);
}

void EventCheckAndCreateEquip::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventCheckAndCreateEquip::loadParams_() {
    getDynamicParam(&mSharpWeaponAddValue_d, "SharpWeaponAddValue");
    getDynamicParam(&mSharpWeaponAddType_d, "SharpWeaponAddType");
    getDynamicParam(&mTargetActorName_d, "TargetActorName");
}

void EventCheckAndCreateEquip::calc_() {
    auto* mgr = act::CreatePlayerEquipActorMgr::instance();
    if (mgr && mgr->areAllWeaponActorsReady())
        setFinished();
}

s32 EventCheckAndCreateEquip::sub_7100116C38(const sead::SafeString& profile) {
    if (profile == "WeaponSmallSword" || profile == "WeaponLargeSword" || profile == "WeaponSpear")
        return 0;
    if (profile == "WeaponShield")
        return 1;
    if (profile == "WeaponBow")
        return 2;
    return 3;
}

}  // namespace uking::action
