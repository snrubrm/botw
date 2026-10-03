#include "Game/AI/AI/aiBeamExplode.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

BeamExplode::BeamExplode(const InitArg& arg) : BeamExplodeBase(arg) {}

BeamExplode::~BeamExplode() = default;

bool BeamExplode::init_(sead::Heap* heap) {
    return BeamExplodeBase::init_(heap);
}

void BeamExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamExplodeBase::enter_(params);
}

void BeamExplode::calc_() {
    BeamExplodeBase::calc_();
    auto* child = getCurrentChild();
    if (!child)
        return;
    if ((child->isFinished() || child->isFailed() || child->isChangeable()) &&
        isCurrentChild("爆発")) {
        sub_710056CA00();
    }
}

void BeamExplode::leave_() {
    BeamExplodeBase::leave_();
}

void BeamExplode::loadParams_() {
    BeamExplodeBase::loadParams_();
}

void BeamExplode::m34() {
    sub_710056CA8C();
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D909A4();
    m35();
}

void BeamExplode::m35() {
    changeChild("爆発");
}

}  // namespace uking::ai
