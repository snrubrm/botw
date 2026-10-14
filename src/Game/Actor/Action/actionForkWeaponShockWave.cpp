#include "Game/Actor/Action/actionForkWeaponShockWave.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::action {

ForkWeaponShockWave::ForkWeaponShockWave(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkWeaponShockWave::~ForkWeaponShockWave() = default;

void ForkWeaponShockWave::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    _48 = false;
}

void ForkWeaponShockWave::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mShockWaveRadius_s, "ShockWaveRadius");
    getStaticParam(&mUnderRayLength_s, "UnderRayLength");
}

// NON_MATCHING: the position output and scoped request have different stack allocation.
void ForkWeaponShockWave::calc_() {
    sead::Vector3f position;
    if (_48 || !sub_710016A388(&position))
        return;
    _48 = true;
    {
        act::Unk_71002eda38 arg;
        arg._0 = 8;
        arg._8 = position;
        arg._34 = *mShockWaveRadius_s;
        sub_71005D787C(mActor, *mWeaponIdx_s, arg);
    }
    const u32 value = 0;
    sub_71005D8C94(mActor, *mWeaponIdx_s, value);
}

// NON_MATCHING: stack slots (the original reuses the AABB vector slot for the ray start).
// Ground position below the tip of the enemy's weapon (ray from 2 above the tip down to UnderRayLength
// below it); zero while the AS trigger (m32) is off.
bool ForkWeaponShockWave::sub_710016A388(sead::Vector3f* out) {
    if (!out || !mActor)
        return false;
    if (!m32()) {
        *out = sead::Vector3f::zero;
        return false;
    }
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    const s32 weapon_idx = *mWeaponIdx_s;
    auto* weapon = sead::DynamicCast<act::Weapon>(enemy->getWeapons()->getEquippedWeapon(weapon_idx));
    if (!weapon)
        return false;

    sead::Vector3f size;
    weapon->sub_71002E5DDC(&size);
    const sead::Vector3f dir = weapon->getMtx().getBase(2);
    const sead::Vector3f pos = weapon->getMtx().getTranslation();
    sead::Vector3f tip = pos + dir * size.length();
    const sead::Vector3f& up = sead::Vector3f::ey;
    const sead::Vector3f from = up + up + tip;
    tip -= up * *mUnderRayLength_s;
    return sub_710072E928(from, tip, out, nullptr, nullptr, 0.0f);
}

bool ForkWeaponShockWave::m32() {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return false;
    if (as_list->x(3, nullptr, *mTargetBone_s, *mSeqBank_s,
                   &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        return true;
    }
    return as_list->x(3, nullptr, *mTargetBone_s, *mSeqBank_s,
                      &ksys::as::ASList::Unk2::sub_710116388C, true);
}

}  // namespace uking::action
