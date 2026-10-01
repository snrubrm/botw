#include "Game/AI/Action/actionChemicalPhysBall.h"
#include "KingSystem/ActorSystem/actActor.h"

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
}

void ChemicalPhysBall::m32() {}

f32 ChemicalPhysBall::m40() {
    return *mDeleteTime_s;
}

}  // namespace uking::action
