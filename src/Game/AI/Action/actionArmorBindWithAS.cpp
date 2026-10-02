#include "Game/AI/Action/actionArmorBindWithAS.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

ArmorBindWithAS::ArmorBindWithAS(const InitArg& arg) : ArmorBindAction(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ArmorBindWithAS::~ArmorBindWithAS() {
    ;
}

// NON_MATCHING: argument register setup order (the float copy is scheduled last in the original)
void ArmorBindWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ArmorBindAction::enter_(params);
    auto* as_list = mActor->getASList();
    if (as_list && as_list->sub_710115AA68(mASName_d))
        as_list->startAnimationMaybe(-1.0f, -1.0f, mASName_d, 0, 1, true);
}

void ArmorBindWithAS::leave_() {
    ArmorBindAction::leave_();
    auto* as_list = mActor->getASList();
    if (as_list && as_list->sub_710115AA68(mASName_d))
        as_list->sub_710115B01C(0, 1, true);
}

void ArmorBindWithAS::loadParams_() {
    ArmorBindAction::loadParams_();
    getDynamicParam(&mASName_d, "ASName");
}

}  // namespace uking::action
