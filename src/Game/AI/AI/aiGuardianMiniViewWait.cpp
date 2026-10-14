#include "Game/AI/AI/aiGuardianMiniViewWait.h"
#include "Game/AI/aiUnk_71007091AC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>

namespace uking::ai {

GuardianMiniViewWait::GuardianMiniViewWait(const InitArg& arg) : ViewWait(arg) {}

// The original keeps the vtable store, which a defaulted destructor drops; written as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
GuardianMiniViewWait::~GuardianMiniViewWait() { ; }

void GuardianMiniViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void GuardianMiniViewWait::calc_() {
    ViewWait::calc_();
}

void GuardianMiniViewWait::leave_() {
    ViewWait::leave_();
}

void GuardianMiniViewWait::m36() {
    s32 a;
    s32 b;
    s32 c = -1;
    sub_71007091AC(mActor, &a, &b, &c);
    sub_7100429D14(a, b);
    _5c = false;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(m34(), "TargetPos", -1);
    pack.addInt(a, "DynRightWeaponIdx", -1);
    pack.addInt(b, "DynLeftWeaponIdx", -1);
    pack.addInt(c, "DynBackWeaponIdx", -1);
    changeChild("待機", &pack);
}

// NON_MATCHING: stack slots of the names and bone keys (the original addresses each name slot directly).
// Binds the root and arm bones to the AS slots: the arm of each weapon slot (right, left, back) is
// chosen from the weapon pair (a, b).
void GuardianMiniViewWait::sub_7100429D14(s32 a, s32 b) {
    if (!*mIsPartialBind_s)
        return;
    auto* actor = mActor;
    if (!actor || !actor->getModel())
        return;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;

    sead::SafeString root = mRootNodeName_s;
    // Arm node names for the back, left and right weapon slots.
    sead::SafeString arms[3];
    if (a == 2 && b == 0) {
        arms[2] = mArm3NodeName_s;
        arms[1] = mArm1NodeName_s;
        arms[0] = mArm2NodeName_s;
    } else if (a == 1 && b == 2) {
        arms[2] = mArm2NodeName_s;
        arms[1] = mArm3NodeName_s;
        arms[0] = mArm1NodeName_s;
    } else {
        arms[2] = mArm1NodeName_s;
        arms[1] = mArm2NodeName_s;
        arms[0] = mArm3NodeName_s;
    }

    const auto root_key = actor->getModel()->searchBone(root);
    const auto right_key = actor->getModel()->searchBone(arms[2]);
    const auto left_key = actor->getModel()->searchBone(arms[1]);
    const auto back_key = actor->getModel()->searchBone(arms[0]);
    if (!root_key.isValid() || !right_key.isValid() || !left_key.isValid() || !back_key.isValid())
        return;

    as_list->sub_710115C9E0(0);
    as_list->mSlots[0].sub_7101165008(root_key, 0, true);
    as_list->mSlots[0].sub_7101165008(right_key, 3, true);
    as_list->mSlots[0].sub_7101165008(left_key, 3, true);
    as_list->mSlots[0].sub_7101165008(back_key, 3, true);
    as_list->mSlots[0].sub_7101164E38(false);

    const s32 right_slot = *mASSlotRight_s;
    as_list->sub_710115C9E0(right_slot);
    as_list->mSlots[right_slot].sub_7101165008(root_key, 3, true);
    as_list->mSlots[right_slot].sub_7101165008(right_key, 0, true);
    as_list->mSlots[right_slot].sub_7101164E38(false);

    const s32 left_slot = *mASSlotLeft_s;
    as_list->sub_710115C9E0(left_slot);
    as_list->mSlots[left_slot].sub_7101165008(root_key, 3, true);
    as_list->mSlots[left_slot].sub_7101165008(left_key, 0, true);
    as_list->mSlots[left_slot].sub_7101164E38(false);

    const s32 back_slot = *mASSlotBack_s;
    as_list->sub_710115C9E0(back_slot);
    as_list->mSlots[back_slot].sub_7101165008(root_key, 3, true);
    as_list->mSlots[back_slot].sub_7101165008(back_key, 0, true);
    as_list->mSlots[back_slot].sub_7101164E38(false);

    as_list->startAnimationMaybe(-1.0f, -1.0f, "Wait", 0, 0, true);
}

void GuardianMiniViewWait::loadParams_() {
    ViewWait::loadParams_();
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mArm1NodeName_s, "Arm1NodeName");
    getStaticParam(&mArm2NodeName_s, "Arm2NodeName");
    getStaticParam(&mArm3NodeName_s, "Arm3NodeName");
    getStaticParam(&mIsPartialBind_s, "IsPartialBind");
}

void GuardianMiniViewWait::m37() {
    if (*mIsPartialBind_s) {
        auto* actor = mActor;
        if (actor && actor->getModel() && actor->getASList()) {
            actor->getASList()->sub_710115C11C();
            actor->getASList()->sub_710115BED4(true);
        }
    }
    ViewWait::m37();
}

}  // namespace uking::ai
