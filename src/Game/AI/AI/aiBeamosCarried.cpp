#include "Game/AI/AI/aiBeamosCarried.h"

namespace uking::ai {

BeamosCarried::BeamosCarried(const InitArg& arg) : AddCarried(arg) {}

BeamosCarried::~BeamosCarried() = default;

bool BeamosCarried::init_(sead::Heap* heap) {
    if (!AddCarried::init_(heap))
        return false;
    return _168.acquire(heap, static_cast<Unk_71025afb58**>(mBeamActorLink_a));
}

void BeamosCarried::enter_(ksys::act::ai::InlineParamPack* params) {
    AddCarried::enter_(params);
}

void BeamosCarried::calc_() {
    AddCarried::calc_();
}

void BeamosCarried::leave_() {
    AddCarried::leave_();
}

void BeamosCarried::loadParams_() {
    AddCarried::loadParams_();
    getAITreeVariable(&mBeamActorLink_a, "BeamActorLink");
}

}  // namespace uking::ai
