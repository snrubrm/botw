#include "Game/AI/Action/actionPlayerEquipNearMasterSword.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorNameSearch.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include <prim/seadDelegate.h>

namespace uking::action {

PlayerEquipNearMasterSword::PlayerEquipNearMasterSword(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerEquipNearMasterSword::~PlayerEquipNearMasterSword() = default;

bool PlayerEquipNearMasterSword::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerEquipNearMasterSword::loadParams_() {}

// NON_MATCHING: stack/delegate setup differs and the separate-TU search destructor remains a call.
bool PlayerEquipNearMasterSword::oneShot_() {
    auto* player = sead::DynamicCast<ksys::act::Player>(mActor);
    if (!player)
        return true;
    auto* mgr = ksys::act::BaseProcMgr::instance();
    if (!mgr)
        return true;
    ksys::act::BaseProc* result = nullptr;
    ksys::act::ActorNearestSearch search("", mActor, &result, sead::Vector3f::zero);
    sead::Delegate1<ksys::act::ActorNearestSearch, ksys::act::BaseProc*> callback(
        &search, &ksys::act::ActorNearestSearch::sub_7100EDC9E8);
    mgr->forEachProc("Weapon_Sword_070", callback, ksys::act::BaseProcMgr::ProcFilters(0));
    if (result) {
        if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(result)) {
            player->m164(3, weapon, false, true);
            player->getWeapons()->mWeapons[3]._10 = false;
        }
    }
    return true;
}

}  // namespace uking::action
