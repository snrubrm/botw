#include "Game/AI/AI/aiLandHumEnemyThrowWeapon.h"
#include <limits>
#include "KingSystem/ActorSystem/actAiInlineParam.h"

#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"

namespace uking::ai {

LandHumEnemyThrowWeapon::LandHumEnemyThrowWeapon(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LandHumEnemyThrowWeapon::~LandHumEnemyThrowWeapon() = default;

void LandHumEnemyThrowWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    changeToThrowWeapon();
}

void LandHumEnemyThrowWeapon::changeToThrowWeapon() {
    _64 = sub_710046CC20();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("武器投げ", &pack);
}

// NON_MATCHING: the original returns through separate constant blocks; ours merges the results into
// one register (eor / and). Same tests.
bool LandHumEnemyThrowWeapon::sub_710046C380() {
    if (!_64)
        return false;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    auto* proc = enemy->_c38[*mWeaponIdx_s].getProc(nullptr, nullptr);
    if (!sead::DynamicCast<act::Weapon>(proc)) {
        if (enemy->_c38[*mWeaponIdx_s].hasProc())
            return false;
        return true;
    }
    if (!proc->isCalc())
        return true;
    auto* weapon = sead::DynamicCast<act::Weapon>(proc);
    if (weapon && weapon->hasParentActor() && weapon->isParentPlayer())
        return true;
    return false;
}

bool LandHumEnemyThrowWeapon::sub_710046C6E0() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto* proc = enemy->_c38[*mWeaponIdx_s].getProc(nullptr, nullptr);
        if (sead::DynamicCast<act::Weapon>(proc) && proc->isCalc()) {
            if (auto* weapon = sead::DynamicCast<act::Weapon>(proc)) {
                if (weapon->m211())
                    return true;
                if (weapon->hasParentActor() && !weapon->isParentPlayer())
                    return true;
                if (weapon->_d90 && weapon->_d90->m2())
                    return true;
                if (weapon->get68f())
                    return true;
            }
        }
    }
    return _58.value <= std::numeric_limits<f32>::epsilon();
}

void LandHumEnemyThrowWeapon::sub_710046C574() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        const s32 index = *mWeaponIdx_s;
        enemy->_c38[index].reset();
        enemy->_e80.resetBit(index);
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("怒り", &pack);
}

bool LandHumEnemyThrowWeapon::isChangeable() const {
    return false;
}

void LandHumEnemyThrowWeapon::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LandHumEnemyThrowWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mThrowWeaponNearDist_s, "ThrowWeaponNearDist");
    getStaticParam(&mWaitTimeMax_s, "WaitTimeMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool LandHumEnemyThrowWeapon::sub_710046CC20() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    auto* proc = enemy->_c38[*mWeaponIdx_s].getProc(nullptr, nullptr);
    auto* weapon = sead::DynamicCast<act::Weapon>(proc);
    auto* checked = sead::DynamicCast<act::Weapon>(weapon);
    if (!checked)
        return false;
    return checked->isBoomerang();
}

}  // namespace uking::ai
