#include "Game/AI/AI/aiWeaponEquipEnemyWakeUp.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WeaponEquipEnemyWakeUp::WeaponEquipEnemyWakeUp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponEquipEnemyWakeUp::~WeaponEquipEnemyWakeUp() = default;

bool WeaponEquipEnemyWakeUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponEquipEnemyWakeUp::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->sub_71000198E4(sead::DynamicCast<act::Weapon>(
            enemy->_c38[*mWeaponIdx_s].getProc(nullptr, nullptr)));
    }
    changeChild("起きる", nullptr);
}

// NON_MATCHING: distance component loads and subtraction scheduling differ.
void WeaponEquipEnemyWakeUp::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;
    if (isCurrentChild("盾拾い")) {
        setFinished();
        return;
    }
    if (isCurrentChild("武器拾い")) {
        if (*mShieldIdx_s >= 0) {
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                if (auto* weapon = sead::DynamicCast<act::Weapon>(
                            enemy->_c38[*mShieldIdx_s].getProc(nullptr, nullptr))) {
                    if (sead::Vector2f(weapon->getMtx()(0, 3) - enemy->getMtx()(0, 3),
                                      weapon->getMtx()(2, 3) - enemy->getMtx()(2, 3)).length() <
                        *mWeaponGetRange_s) {
                        ksys::act::ai::InlineParamPack pack;
                        pack.acquireActor(weapon, "TargetWeapon", -1);
                        changeChild("盾拾い", &pack);
                        return;
                    }
                }
            }
        }
    } else {
        if (*mWeaponIdx_s >= 0) {
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                if (auto* weapon = sead::DynamicCast<act::Weapon>(
                            enemy->_c38[*mWeaponIdx_s].getProc(nullptr, nullptr))) {
                    if (sead::Vector2f(weapon->getMtx()(0, 3) - enemy->getMtx()(0, 3),
                                      weapon->getMtx()(2, 3) - enemy->getMtx()(2, 3)).length() <
                        *mWeaponGetRange_s) {
                        ksys::act::ai::InlineParamPack pack;
                        pack.acquireActor(weapon, "TargetWeapon", -1);
                        changeChild("武器拾い", &pack);
                        return;
                    }
                }
            }
        }
    }
    setFinished();
}

void WeaponEquipEnemyWakeUp::leave_() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->sub_7100019C58(sead::DynamicCast<act::Weapon>(
            enemy->_c38[*mWeaponIdx_s].getProc(nullptr, nullptr)));
        enemy->sub_7100019C58(sub_71005D83E8(enemy, *mWeaponIdx_s));
    }
}

void WeaponEquipEnemyWakeUp::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mShieldIdx_s, "ShieldIdx");
    getStaticParam(&mWeaponGetRange_s, "WeaponGetRange");
}

}  // namespace uking::ai
