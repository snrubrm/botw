#include "Game/AI/Action/actionGuardianMiniWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/AI/Action/actionGuardianMiniUtil.h"

namespace uking::action {

GuardianMiniWait::GuardianMiniWait(const InitArg& arg) : Wait(arg) {}

GuardianMiniWait::~GuardianMiniWait() = default;

void GuardianMiniWait::enter_(ksys::act::ai::InlineParamPack* params) {
    Wait::enter_(params);
    m32();
}

void GuardianMiniWait::loadParams_() {
    WaitBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
    getDynamicParam(&mDynRightWeaponIdx_d, "DynRightWeaponIdx");
    getDynamicParam(&mDynLeftWeaponIdx_d, "DynLeftWeaponIdx");
    getDynamicParam(&mDynBackWeaponIdx_d, "DynBackWeaponIdx");
}

void GuardianMiniWait::calc_() {
    WaitBase::calc_();
    sub_710019896C();
}

void GuardianMiniWait::sub_710019896C() {
    auto* list = mActor->getASList();
    if (!list)
        return;
    if (!list->x_4(0, 0))
        return;
    if (list->x_1(0, 0) == mASName_s)
        return;
    list->startAnimationMaybe(-1.0f, -1.0f, mASName_s, 0, 0, true);
    const f32 value = list->x_5(1, 0, &ksys::as::ASList::Unk2::sub_71011632F8);
    list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, value);
}

// NON_MATCHING: the 2nd and 3rd blocks load the weapon-index parameter pointer before reloading mActor
// (the original reloads mActor first); the first block matches.
void GuardianMiniWait::m32() {
    auto* list = mActor->getASList();
    if (!list)
        return;
    goLimpWithWeaponProfile(mActor, list, *mDynRightWeaponIdx_d);
    playAS(mASName_s.cstr(), true, *mASSlotRight_s, 0, -1.0f);
    goLimpWithWeaponProfile(mActor, list, *mDynLeftWeaponIdx_d);
    playAS(mASName_s.cstr(), true, *mASSlotLeft_s, 0, -1.0f);
    goLimpWithWeaponProfile(mActor, list, *mDynBackWeaponIdx_d);
    playAS(mASName_s.cstr(), true, *mASSlotBack_s, 0, -1.0f);
}

}  // namespace uking::action
