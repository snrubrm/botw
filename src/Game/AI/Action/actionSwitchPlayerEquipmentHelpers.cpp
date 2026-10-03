#include "Game/AI/Action/actionSwitchPlayerEquipment.h"
#include "Game/Actor/actPlayerCreateMgr.h"
#include "Game/Actor/actWeapon.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

// NON_MATCHING: the original has an unused leading parameter (name in x1), and its failure exits
// share one `mov w0, wzr` block.
bool sub_710028DA58(const sead::SafeString& name) {
    if (!name.isEmpty()) {
        auto* player_info = ksys::act::PlayerInfo::instance();
        if (!player_info)
            return false;
        if (!player_info->getPlayer())
            return false;
        auto* create_mgr = act::CreatePlayerEquipActorMgr::instance();
        auto* mgr = ui::PauseMenuDataMgr::instance();
        if (create_mgr && mgr) {
            auto* player = ksys::act::PlayerInfo::instance()->getPlayer();
            bool changed = false;
            if (name.comparen("Weapon_Default_", 15) != 0) {
                int value = 0;
                act::WeaponModifierInfo modifier;
                if (mgr->switchEquipment(name, &value, &modifier)) {
                    create_mgr->requestCreateWeapon(name, value, &modifier,
                                                    "action::SwitchPlayerEquipment");
                    changed = true;
                }
            } else {
                player->switchEquipment(name, 0x1e, -1);
                changed = true;
            }
            return changed;
        }
    }
    return false;
}

// NON_MATCHING: as sub_710028DA58.
bool sub_710028DBC8(const sead::SafeString& name, bool needs_head_b) {
    if (!name.isEmpty()) {
        auto* player_info = ksys::act::PlayerInfo::instance();
        if (!player_info)
            return false;
        if (!player_info->getPlayer())
            return false;
        auto* create_mgr = act::CreatePlayerEquipActorMgr::instance();
        auto* mgr = ui::PauseMenuDataMgr::instance();
        if (create_mgr && mgr) {
            ksys::act::PlayerInfo::instance()->getPlayer();
            int dye = -1;
            if (name.comparen("Armor_Default_", 14) != 0) {
                if (!mgr->switchEquipment(name, &dye))
                    return false;
                if (needs_head_b) {
                    create_mgr->requestCreateArmorHeadB(name, dye, "action::SwitchPlayerEquipment");
                    return true;
                }
            }
            create_mgr->requestCreateArmor(name, dye, "action::SwitchPlayerEquipment");
            return true;
        }
    }
    return false;
}

}  // namespace uking::action
