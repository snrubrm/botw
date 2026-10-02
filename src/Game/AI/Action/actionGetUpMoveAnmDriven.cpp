#include "Game/AI/Action/actionGetUpMoveAnmDriven.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

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
}

}  // namespace uking::action
