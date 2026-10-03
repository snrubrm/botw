#include "Game/AI/Action/actionTornadoMove.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

TornadoMove::TornadoMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TornadoMove::~TornadoMove() = default;

bool TornadoMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TornadoMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TornadoMove::leave_() {
    if (_b0 && _b0->isAddedToWorld()) {
        _b0->removeFromWorld();
        _b0 = nullptr;
    }
}

void TornadoMove::loadParams_() {
    getStaticParam(&mMaxAmplitude_s, "MaxAmplitude");
    getStaticParam(&mMinAmplitude_s, "MinAmplitude");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mAmplitudeAddRate_s, "AmplitudeAddRate");
    getStaticParam(&mDeleteTimer_s, "DeleteTimer");
    getStaticParam(&mFrequency_s, "Frequency");
    getStaticParam(&mIgnoreHitFrame_s, "IgnoreHitFrame");
}

void TornadoMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
