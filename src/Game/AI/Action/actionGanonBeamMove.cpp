#include "Game/AI/Action/actionGanonBeamMove.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GanonBeamMove::GanonBeamMove(const InitArg& arg) : BeamMove(arg) {}

GanonBeamMove::~GanonBeamMove() = default;

bool GanonBeamMove::init_(sead::Heap* heap) {
    return BeamMove::init_(heap);
}

void GanonBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamMove::enter_(params);
    if (auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent())) {
        parent->getMtx().getTranslation(_88);
        mActor->resetConnectedCalcParent(false);
    } else {
        mActor->getMtx().getTranslation(_88);
    }
}

void GanonBeamMove::leave_() {
    BeamMove::leave_();
}

void GanonBeamMove::loadParams_() {
    BeamMove::loadParams_();
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
    getMapUnitParam(&mPosOffset_m, "PosOffset");
}

void GanonBeamMove::calc_() {
    BeamMove::calc_();
}

}  // namespace uking::action
