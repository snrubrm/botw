#include "Game/AI/AI/aiGuardianMiniNoWeaponSelect.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71007091AC.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::ai {

// inline-only in the original (twice in each of the 0x710041cce0 / d304 / d4ec helpers); name is a guess.
static bool hasNonType4Weapon(uking::act::Enemy* enemy, s32 idx) {
    auto* weapon = enemy->getWeapons()->getEquippedWeapon(idx);
    if (sead::IsDerivedFrom<uking::act::Weapon>(weapon)) {
        if (static_cast<uking::act::Weapon*>(weapon)->_cf0 != 4)
            return true;
    }
    return false;
}

// 0x710041d304 (placeholder name): whether the weapons in both slots selected by sub_71007091AC are of
// type 4 (or are no weapons); false without the slots / for non-enemies.
// NON_MATCHING: the final `return true` is a `cset eq` in ours (select) but separate return blocks in the
// original; everything else (incl. reading the slot before the getWeapons() call) matches.
bool sub_710041D304(ksys::act::Actor* actor) {
    if (!sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return false;
    s32 a;
    s32 b;
    s32 c = -1;
    sub_71007091AC(actor, &a, &b, &c);
    if (a == -1 || b == -1)
        return false;
    auto* enemy = static_cast<uking::act::Enemy*>(actor);
    if (hasNonType4Weapon(enemy, a))
        return false;
    if (hasNonType4Weapon(enemy, b))
        return false;
    return true;
}

GuardianMiniNoWeaponSelect::GuardianMiniNoWeaponSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniNoWeaponSelect::~GuardianMiniNoWeaponSelect() = default;

void GuardianMiniNoWeaponSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool GuardianMiniNoWeaponSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool GuardianMiniNoWeaponSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool GuardianMiniNoWeaponSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void GuardianMiniNoWeaponSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniNoWeaponSelect::loadParams_() {
    getStaticParam(&mIsSelectFirstTime_s, "IsSelectFirstTime");
}

}  // namespace uking::ai
