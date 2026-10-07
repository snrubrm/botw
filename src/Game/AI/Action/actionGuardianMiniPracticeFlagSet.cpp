#include "Game/AI/Action/actionGuardianMiniPracticeFlagSet.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "Game/Damage/dmgDamageManagerBase.h"

namespace uking::action {

GuardianMiniPracticeFlagSet::GuardianMiniPracticeFlagSet(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GuardianMiniPracticeFlagSet::~GuardianMiniPracticeFlagSet() = default;

bool GuardianMiniPracticeFlagSet::init_(sead::Heap* heap) {
    *mGuardianMiniPracticeState_a = 4;
    return true;
}

// NON_MATCHING: compiler orders the three state comparisons differently.
void GuardianMiniPracticeFlagSet::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* damage = mActor->getDamageMgr();
    if (!damage || s32(damage->getDamage()) < 1)
        return;
    --*mGuardianMiniPracticeState_a;
    auto* bgm = ksys::snd::sub_7100FFDA7C();
    if (!bgm)
        return;
    if (*mGuardianMiniPracticeState_a == 1)
        bgm->sub_7100FFC934();
    else if (*mGuardianMiniPracticeState_a == 2)
        bgm->sub_7100FFC894();
    else if (*mGuardianMiniPracticeState_a == 3)
        bgm->sub_7100FFC7F4();
}

void GuardianMiniPracticeFlagSet::leave_() {
    switch (*mGuardianMiniPracticeState_a) {
    case 0:
        ksys::gdt::setFlag_ClearTutorial_SpinAttack(true);
        break;
    case 1:
        ksys::gdt::setFlag_ClearTutorial_GuardJust(true);
        break;
    case 2:
        ksys::gdt::setFlag_ClearTutorial_BackStep(true);
        break;
    case 3:
        ksys::gdt::setFlag_ClearTutorial_SideStep(true);
        break;
    default:
        break;
    }
}

void GuardianMiniPracticeFlagSet::loadParams_() {
    getAITreeVariable(&mGuardianMiniPracticeState_a, "GuardianMiniPracticeState");
}

void GuardianMiniPracticeFlagSet::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
