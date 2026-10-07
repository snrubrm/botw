#include "Game/AI/AI/aiGuardianMiniViewWait.h"
#include "Game/AI/aiUnk_71007091AC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

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
