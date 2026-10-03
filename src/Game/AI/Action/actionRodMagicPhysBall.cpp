#include "Game/AI/Action/actionRodMagicPhysBall.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

RodMagicPhysBall::RodMagicPhysBall(const InitArg& arg) : ChemicalPhysBall(arg) {}

RodMagicPhysBall::~RodMagicPhysBall() = default;

void RodMagicPhysBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalPhysBall::enter_(params);
}

void RodMagicPhysBall::leave_() {
    if (_160)
        mActor->sub_71011DA834(&_e8);
    ChemicalPhysBall::leave_();
}

void RodMagicPhysBall::loadParams_() {
    ChemicalPhysBall::loadParams_();
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mChemicalType_s, "ChemicalType");
    getStaticParam(&mBgCheckHeight_s, "BgCheckHeight");
}

void RodMagicPhysBall::calc_() {
    ChemicalPhysBall::calc_();
}

bool RodMagicPhysBall::m33() {
    return false;
}

int RodMagicPhysBall::m36() {
    const int type = *mChemicalType_s;
    int flags = ChemicalAttackBall::m36();
    if (type == 1)
        flags |= 8;
    return flags;
}

}  // namespace uking::action
