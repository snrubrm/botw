#include "Game/AI/AI/aiGuardianMiniRangeKeepMove.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007091AC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::ai {

GuardianMiniRangeKeepMove::GuardianMiniRangeKeepMove(const InitArg& arg)
    : EnemyRangeKeepMove(arg) {}

GuardianMiniRangeKeepMove::~GuardianMiniRangeKeepMove() = default;

void GuardianMiniRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRangeKeepMove::enter_(params);
}

void GuardianMiniRangeKeepMove::leave_() {
    EnemyRangeKeepMove::leave_();
}

void GuardianMiniRangeKeepMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
}

void GuardianMiniRangeKeepMove::calc_() {
    if (getCurrentChild()->isFailed() && isCurrentChild("戦闘歩行")) {
        setFailed();
        return;
    }
    if (getCurrentChild()->isChangeable() && isCurrentChild("戦闘歩行") && sub_71003AD1F8() &&
        sub_71003AD160()) {
        sub_71003ABF50();
        return;
    }
    EnemyRangeKeepMove::calc_();
}

// NON_MATCHING: the original loads the weapon slot (`a`) before the getWeapons() virtual call (and so
// needs a second callee-saved register / a different frame) and returns through a pointer select.
int GuardianMiniRangeKeepMove::m35() {
    s32 a;
    s32 b;
    s32 c = -1;
    sub_71007091AC(mActor, &a, &b, &c);
    auto* actor = mActor;
    if (!sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return a;
    auto* weapon = static_cast<uking::act::Enemy*>(actor)->getWeapons()->getEquippedWeapon(a);
    if (sead::IsDerivedFrom<uking::act::Weapon>(weapon) && weapon->getProfile() != "WeaponShield")
        return a;
    return b;
}

}  // namespace uking::ai
