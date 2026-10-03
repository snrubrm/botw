#include "Game/AI/Action/actionTurnAndLookToObjNotAnimDriven.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

TurnAndLookToObjNotAnimDriven::TurnAndLookToObjNotAnimDriven(const InitArg& arg)
    : LookAtObjectBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
TurnAndLookToObjNotAnimDriven::~TurnAndLookToObjNotAnimDriven() {
    ;
}

bool TurnAndLookToObjNotAnimDriven::init_(sead::Heap* heap) {
    return LookAtObjectBase::init_(heap);
}

void TurnAndLookToObjNotAnimDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    LookAtObjectBase::enter_(params);
}

void TurnAndLookToObjNotAnimDriven::leave_() {
    LookAtObjectBase::leave_();
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
}

void TurnAndLookToObjNotAnimDriven::loadParams_() {
    LookAtObjectBase::loadParams_();
    getDynamicParam(&mRotSpdMax_d, "RotSpdMax");
    getDynamicParam(&mRotSpdMin_d, "RotSpdMin");
    getDynamicParam(&mRotInitSpd_d, "RotInitSpd");
    getDynamicParam(&mRotAccel_d, "RotAccel");
    getDynamicParam(&mRotRate_d, "RotRate");
}

void TurnAndLookToObjNotAnimDriven::calc_() {
    LookAtObjectBase::calc_();
}

}  // namespace uking::action
