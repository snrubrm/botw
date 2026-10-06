#include "Game/AI/Action/actionPlayerEquipHaveMasterSword.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::action {

PlayerEquipHaveMasterSword::PlayerEquipHaveMasterSword(const InitArg& arg) : PlayerAction(arg) {}

PlayerEquipHaveMasterSword::~PlayerEquipHaveMasterSword() = default;

bool PlayerEquipHaveMasterSword::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerEquipHaveMasterSword::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_c48.set(0x2000000);
    static_cast<ksys::act::PlayerOrEnemy*>(mActor)->sub_7100007844(0);
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor->getWeapons()->getEquippedWeapon(3));
    static_cast<ksys::act::PlayerOrEnemy*>(mActor)->dropWeapon(3, sead::Vector3f::zero, false, false,
                                                                nullptr, false);
    mActor->getWeapons()->mWeapons[3]._10 = true;
    if (weapon) {
        static_cast<ksys::act::PlayerOrEnemy*>(mActor)->m164(0, weapon, true, true);
        static_cast<ksys::act::Player*>(mActor)->_d24 = weapon->_cf0;
        static_cast<ksys::act::Player*>(mActor)->x_10(true);
        mActor->getASList()->x_2(0x42, 0x24, false, false);
        mActor->getASList()->x_2(0x42, 0x25, true, false);
    }
    setFinished();
}

void PlayerEquipHaveMasterSword::leave_() {}

void PlayerEquipHaveMasterSword::loadParams_() {}

void PlayerEquipHaveMasterSword::calc_() {}

}  // namespace uking::action
