#include "Game/AI/Action/actionEventSetItemDataToPouch.h"
#include "Game/Actor/actWeapon.h"

// The source namespace for this utility is unknown.
void setItemDataToPouch(const sead::SafeString& name,
                       const uking::act::WeaponModifierInfo* modifier);

namespace uking::action {

EventSetItemDataToPouch::EventSetItemDataToPouch(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetItemDataToPouch::~EventSetItemDataToPouch() = default;

bool EventSetItemDataToPouch::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetItemDataToPouch::loadParams_() {
    getDynamicParam(&mSharpWeaponAddValue_d, "SharpWeaponAddValue");
    getDynamicParam(&mSharpWeaponAddType_d, "SharpWeaponAddType");
    getDynamicParam(&mTargetActorName_d, "TargetActorName");
}

bool EventSetItemDataToPouch::oneShot_() {
    if (mTargetActorName_d.isEmpty())
        return false;
    uking::act::WeaponModifierInfo modifier;
    modifier.set(*mSharpWeaponAddType_d, *mSharpWeaponAddValue_d);
    setItemDataToPouch(mTargetActorName_d, &modifier);
    return true;
}

}  // namespace uking::action
