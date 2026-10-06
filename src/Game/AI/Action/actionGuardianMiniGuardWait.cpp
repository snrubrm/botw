#include "Game/AI/Action/actionGuardianMiniGuardWait.h"
#include "Game/AI/Action/actionGuardianMiniUtil.h"

namespace uking::action {

GuardianMiniGuardWait::GuardianMiniGuardWait(const InitArg& arg) : GuardianMiniWait(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GuardianMiniGuardWait::~GuardianMiniGuardWait() {
    ;
}

void GuardianMiniGuardWait::loadParams_() {
    GuardianMiniWait::loadParams_();
    getStaticParam(&mGuardASName_s, "GuardASName");
}

// NON_MATCHING: same as GuardianMiniWait::m32 (blocks 2 and 3 load the weapon-index parameter pointer
// before reloading mActor; the original reloads mActor first).
void GuardianMiniGuardWait::m32() {
    auto* list = mActor->getASList();
    if (!list)
        return;
    if (auto* weapon = goLimpWithWeaponProfile(mActor, list, *mDynRightWeaponIdx_d)) {
        if (weapon->_cf0 == 4)
            list->sub_710115B140(sead::SafeString(mGuardASName_s.cstr()), *mASSlotRight_s,
                                 *mASSlotRight_s, 0, 0);
        else
            playAS(mASName_s.cstr(), true, *mASSlotRight_s, 0, -1.0f);
    }
    if (auto* weapon = goLimpWithWeaponProfile(mActor, list, *mDynLeftWeaponIdx_d)) {
        if (weapon->_cf0 == 4)
            list->sub_710115B140(sead::SafeString(mGuardASName_s.cstr()), *mASSlotLeft_s,
                                 *mASSlotLeft_s, 0, 0);
        else
            playAS(mASName_s.cstr(), true, *mASSlotLeft_s, 0, -1.0f);
    }
    if (auto* weapon = goLimpWithWeaponProfile(mActor, list, *mDynBackWeaponIdx_d)) {
        if (weapon->_cf0 == 4)
            list->sub_710115B140(sead::SafeString(mGuardASName_s.cstr()), *mASSlotBack_s,
                                 *mASSlotBack_s, 0, 0);
        else
            playAS(mASName_s.cstr(), true, *mASSlotBack_s, 0, -1.0f);
    }
}

}  // namespace uking::action
