#include "Game/AI/Action/actionTurnAndLookToObjNotAnimDriven.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "Game/AI/aiUnk_71007368A4.h"
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
    m33();
    ksys::act::BaseProcLink link;
    sead::Vector3f pos;
    pos = sead::Vector3f::zero;
    bool found = true;
    if (_30 == 0) {
        found = m34(&link, &pos, _48, _58);
    } else if (_30 == 4) {
        found = m35(&link, &pos, _48, _58);
    }
    if (!found) {
        _f1 = true;
        _34 = 0;
    } else {
        _f1 = false;
    }

    if (link.hasProc())
        m36(&link, sead::Vector3f::zero);
    else
        m36(nullptr, pos);

    switch (_34) {
    case 0:
        sub_7100739900(mActor);
        break;
    case 1:
        if (auto* bone_control = sub_71007398A8(mActor)) {
            bone_control->sub_7100D85644();
            bone_control->sub_7100D85794();
        }
        break;
    case 2:
        if (auto* bone_control = sub_71007398A8(mActor)) {
            sead::Vector3f target;
            mActor->getMtx().getTranslation(target);
            target += _38;
            bone_control->sub_7100D8571C(target);
        }
        break;
    }
    m40();
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
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (_f0 || _f1) {
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        return;
    }
    m41(controller);
}

}  // namespace uking::action
