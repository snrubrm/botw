#include "Game/AI/Action/actionChemicalPhysBall.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

ChemicalPhysBall::ChemicalPhysBall(const InitArg& arg) : ChemicalAttackBall(arg) {}

ChemicalPhysBall::~ChemicalPhysBall() = default;

bool ChemicalPhysBall::init_(sead::Heap* heap) {
    return ChemicalAttackBall::init_(heap);
}

void ChemicalPhysBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttackBall::enter_(params);
    _98 = mActor->getMtx().getTranslation();
    _a4 = 0;
    if (*mDeleteTime_s >= 0) {
        const f32 time = m40();
        _a8 = ksys::Timer(time, time);
        _b4 = true;
    } else {
        _b4 = false;
    }
}

void ChemicalPhysBall::leave_() {
    ChemicalAttackBall::leave_();
}

void ChemicalPhysBall::loadParams_() {
    ChemicalAttackBall::loadParams_();
    getStaticParam(&mDeleteTime_s, "DeleteTime");
}

void ChemicalPhysBall::calc_() {
    ChemicalAttackBall::calc_();
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    _a4 += (pos - _98).length();
    _98 = pos;
    if (_b4)
        _a8.update();
}

void ChemicalPhysBall::m32() {}

bool ChemicalPhysBall::m33() {
    if (hasAttackInfo(mActor))
        return true;
    if (_a4 > m34())
        return true;
    if (_b4)
        return _a8.value <= sead::Mathf::epsilon();
    return false;
}

f32 ChemicalPhysBall::m40() {
    return *mDeleteTime_s;
}

}  // namespace uking::action
