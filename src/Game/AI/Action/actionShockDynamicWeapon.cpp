#include "Game/AI/Action/actionShockDynamicWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

ShockDynamicWeapon::ShockDynamicWeapon(const InitArg& arg) : Shock(arg) {}

ShockDynamicWeapon::~ShockDynamicWeapon() = default;

void ShockDynamicWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    Shock::enter_(params);
    _88 = false;
}

void ShockDynamicWeapon::leave_() {
    if (!_88)
        sub_710024DA0C();
    Shock::leave_();
}

void ShockDynamicWeapon::loadParams_() {
    Shock::loadParams_();
    getDynamicParam(&mDropWeapon_d, "DropWeapon");
    getDynamicParam(&mDropDir_d, "DropDir");
}

void ShockDynamicWeapon::calc_() {
    Shock::calc_();
    if (auto* as_list = mActor->getASList()) {
        if (as_list->x(71, nullptr, *mASSlot_s, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
            sub_710024DA0C();
    }
}

void ShockDynamicWeapon::sub_710024DA0C() {
    if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) {
        actor->getWeapons();
        sead::Vector3f velocity = *mDropDir_d;
        s32 index = -1;
        for (s32 i = 0; i < 6; ++i) {
            auto* weapon =
                sead::DynamicCast<uking::act::Weapon>(actor->getWeapons()->getEquippedWeapon(i));
            if (weapon && mDropWeapon_d->hasProcById(weapon)) {
                index = i;
                break;
            }
        }
        if (index >= 0) {
            velocity *= *mWeaponDropSpeedXZ_s;
            velocity.y = *mWeaponDropSpeedY_s;
            playerOrEnemyDropWeapon(mActor, &velocity, index, true, false, nullptr, false);
            _88 = true;
        }
    }
}

void ShockDynamicWeapon::m33(const sead::Vector3f* velocity) {}

bool ShockDynamicWeapon::m32() {
    return mDropWeapon_d->hasProc();
}

}  // namespace uking::action
