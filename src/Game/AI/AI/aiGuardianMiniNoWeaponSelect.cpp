#include "Game/AI/AI/aiGuardianMiniNoWeaponSelect.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiGuardianMiniWeaponUtil.h"
#include "Game/AI/aiUnk_71007091AC.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::ai {

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

// NON_MATCHING: the final `return true` is a `cset eq` in ours (select) but separate return blocks in the
// original; everything else matches.
// 0x710041d4ec (placeholder name): whether one of the two weapon slots selected by sub_71007091AC holds a
// type 4 weapon (the "盾はある" state).
bool GuardianMiniNoWeaponSelect::sub_710041D4EC() {
    auto* actor = mActor;
    if (!sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return false;
    s32 a;
    s32 b;
    s32 c = -1;
    sub_71007091AC(actor, &a, &b, &c);
    if (a == -1 || b == -1)
        return false;
    auto* enemy = static_cast<uking::act::Enemy*>(actor);
    if (hasType4Weapon(enemy, a))
        return true;
    if (hasType4Weapon(enemy, b))
        return true;
    return false;
}

void GuardianMiniNoWeaponSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!sub_710041D304(mActor))
        changeChild("武器がある", params);
    else if (sub_710041D4EC())
        changeChild("盾はある", params);
    else
        changeChild("武器がない", params);
}

void GuardianMiniNoWeaponSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }
    if (*mIsSelectFirstTime_s)
        return;
    if (!getCurrentChild()->isChangeable())
        return;
    if (isCurrentChild("武器がある")) {
        if (sub_710041D304(mActor)) {
            if (sub_710041D4EC())
                changeChild("盾はある");
            else
                changeChild("武器がない");
        }
    } else if (isCurrentChild("武器がない")) {
        if (sub_710041D304(mActor)) {
            if (sub_710041D4EC())
                changeChild("盾はある");
        } else {
            changeChild("武器がある");
        }
    } else if (isCurrentChild("盾はある")) {
        if (sub_710041D304(mActor)) {
            if (!sub_710041D4EC())
                changeChild("武器がない");
        } else {
            changeChild("武器がある");
        }
    }
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
