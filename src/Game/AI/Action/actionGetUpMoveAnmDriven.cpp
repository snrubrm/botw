#include "Game/AI/Action/actionGetUpMoveAnmDriven.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GetUpMoveAnmDriven::GetUpMoveAnmDriven(const InitArg& arg) : GetUp(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GetUpMoveAnmDriven::~GetUpMoveAnmDriven() {
    ;
}

bool GetUpMoveAnmDriven::init_(sead::Heap* heap) {
    return GetUp::init_(heap);
}

void GetUpMoveAnmDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    GetUp::enter_(params);
    auto* as_list = mActor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }

    if (mTargetBoneName_s.isEmpty())
        return;

    sead::SafeString bone_name = "";
    const auto& key = as_list->_14;
    if (key.isValid()) {
        bone_name = mActor->getModel()
                        ->getUnits()
                        .unsafeAt(key.model_unit_index)
                        ->mModelUnit->getBoneName(key.bone_index);
    }
    if (bone_name == mTargetBoneName_s)
        return;

    as_list->sub_710115CE44(mTargetBoneName_s);
    _170 = true;
    if (!as_list->x_7(0, 0, &ksys::as::ASList::Unk2::sub_710002E82C) || !as_list->_14.isValid())
        setFailed();
}

// NON_MATCHING: the original loads the ASList before clearing _170 (scheduling)
void GetUpMoveAnmDriven::leave_() {
    GetUp::leave_();
    if (_170) {
        _170 = false;
        mActor->getASList()->sub_710115D0AC();
    }
}

void GetUpMoveAnmDriven::loadParams_() {
    GetUp::loadParams_();
    getStaticParam(&mTargetBoneName_s, "TargetBoneName");
}

void GetUpMoveAnmDriven::calc_() {
    GetUp::calc_();
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    if (!as_list || !controller) {
        setFailed();
        return;
    }
    act::sub_7100E7F4FC(as_list, controller, 1.0f);
}

}  // namespace uking::action
