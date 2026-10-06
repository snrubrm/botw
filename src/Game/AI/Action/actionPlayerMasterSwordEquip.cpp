#include "Game/AI/Action/actionPlayerMasterSwordEquip.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

PlayerMasterSwordEquip::PlayerMasterSwordEquip(const InitArg& arg) : PlayerAction(arg) {}

PlayerMasterSwordEquip::~PlayerMasterSwordEquip() = default;

bool PlayerMasterSwordEquip::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

bool PlayerMasterSwordEquip::oneShot_() {
    static_cast<ksys::act::Player*>(mActor)->_c48.set(0x2000000);
    ksys::gdt::increaseFlag_WeaponPorchStockNum(1, false);
    static_cast<ksys::act::Player*>(mActor)->sub_7100007844(0);
    auto* weapon = sead::DynamicCast<act::Weapon>(
        static_cast<ksys::act::Player*>(mActor)->getWeapons()->getEquippedWeapon(3));
    static_cast<ksys::act::Player*>(mActor)->dropWeapon(3, sead::Vector3f::zero, false, false, nullptr,
                                                        false);
    static_cast<ksys::act::Player*>(mActor)->getWeapons()->mWeapons[3]._10 = true;
    if (weapon) {
        static_cast<ksys::act::Player*>(mActor)->m164(0, weapon, true, true);
        static_cast<ksys::act::Player*>(mActor)->_d24 = weapon->_cf0;
        static_cast<ksys::act::Player*>(mActor)->x_10(true);
        mActor->getASList()->x_2(0x42, 0x24, false, false);
        mActor->getASList()->x_2(0x42, 0x25, true, false);
    }
    return true;
}

}  // namespace uking::action
