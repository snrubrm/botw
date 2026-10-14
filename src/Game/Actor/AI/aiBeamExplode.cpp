#include "Game/Actor/AI/aiBeamExplode.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

BeamExplode::BeamExplode(const InitArg& arg) : SimpleBeamExplode(arg) {}

BeamExplode::~BeamExplode() = default;

bool BeamExplode::init_(sead::Heap* heap) {
    return SimpleBeamExplode::init_(heap);
}

void BeamExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleBeamExplode::enter_(params);
}

void BeamExplode::calc_() {
    SimpleBeamExplode::calc_();
    auto* child = getCurrentChild();
    if (!child)
        return;
    if ((child->isFinished() || child->isFailed() || child->isChangeable()) &&
        isCurrentChild("爆発")) {
        changeToCleanup();
    }
}

void BeamExplode::leave_() {
    SimpleBeamExplode::leave_();
}

void BeamExplode::loadParams_() {
    SimpleBeamExplode::loadParams_();
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
