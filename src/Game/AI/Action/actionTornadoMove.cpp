#include "Game/AI/Action/actionTornadoMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

TornadoMove::TornadoMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TornadoMove::~TornadoMove() = default;

bool TornadoMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: same stores; the original issues the matrix loads in address order (translation components interleaved)
void TornadoMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _64 = ksys::Timer(*mDeleteTimer_s, *mDeleteTimer_s);
    _58 = ksys::Timer(*mIgnoreHitFrame_s, *mIgnoreHitFrame_s);
    _a4 = ksys::Timer(0.0f, 0.0f, 1.0f);
    _70 = *mMinAmplitude_s;
    const sead::Vector3f translation = mActor->getMtx().getTranslation();
    const sead::Matrix33f rotation(mActor->getMtx());
    _98 = translation;
    _74 = rotation;
    if (auto* body = mActor->getMainBody())
        body->setGravityFactor(0.0f);
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
