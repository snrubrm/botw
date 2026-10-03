#include "Game/AI/Action/actionPlayerForkDropWeaponWithSpeed.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::action {

PlayerForkDropWeaponWithSpeed::PlayerForkDropWeaponWithSpeed(const InitArg& arg)
    : ForkDropWeaponWithSpeed(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
PlayerForkDropWeaponWithSpeed::~PlayerForkDropWeaponWithSpeed() {
    ;
}

bool PlayerForkDropWeaponWithSpeed::init_(sead::Heap* heap) {
    return ForkDropWeaponWithSpeed::init_(heap);
}

void PlayerForkDropWeaponWithSpeed::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDropWeaponWithSpeed::enter_(params);
    if (auto* player = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) {
        const int slot = *mWeaponIdx_s;
        _48 = player->getWeapons()->mWeapons[slot].link.hasProc();
        if (_48) {
            const int idx = *mWeaponIdx_s;
            auto* weapon =
                sead::DynamicCast<uking::act::Weapon>(player->getWeapons()->getEquippedWeapon(idx));
            if (weapon) {
                _50.copy(weapon->getName());
                return;
            }
        }
        _50.copy("");
    }
}

void PlayerForkDropWeaponWithSpeed::leave_() {
    ForkDropWeaponWithSpeed::leave_();
}

void PlayerForkDropWeaponWithSpeed::loadParams_() {
    ForkDropWeapon::loadParams_();
}

void PlayerForkDropWeaponWithSpeed::calc_() {
    if (!_48)
        return;
    auto* poe = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (!poe) {
        ui::showRuntimeTip(17);
        ForkDropWeaponWithSpeed::calc_();
        return;
    }
    if (auto* player = sead::DynamicCast<ksys::act::Player>(poe)) {
        if (player->sub_71008859EC() > 2)
            return;
        if (player->_cf0.isOnBit(8))
            return;
        const int slot = *mWeaponIdx_s;
        auto* weapon =
            sead::DynamicCast<uking::act::Weapon>(player->getWeapons()->getEquippedWeapon(slot));
        if (weapon && weapon->getParam()->getRes().mActorLink->hasTag("NotDropFromPlayer"))
            return;
        const bool is_selected =
            player->_cf0.isOnBit(23) && player->playerWeapons_return1() == *mWeaponIdx_s;
        if (!is_selected) {
            const int idx = *mWeaponIdx_s;
            if (player->getWeapons()->mWeapons[idx]._10)
                return;
        }
    }
    ui::showRuntimeTip(17);
    ForkDropWeaponWithSpeed::calc_();
    const int idx = *mWeaponIdx_s;
    if (!poe->getWeapons()->mWeapons[idx].link.hasProc()) {
        _48 = false;
        ui::showInfoOverlayWithString(10, _50);
    }
}

}  // namespace uking::action
