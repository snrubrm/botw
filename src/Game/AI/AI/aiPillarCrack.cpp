#include "Game/AI/AI/aiPillarCrack.h"

namespace uking::ai {

PillarCrack::PillarCrack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PillarCrack::~PillarCrack() = default;

bool PillarCrack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PillarCrack::enter_(ksys::act::ai::InlineParamPack* params) {
    _38._28 = mActor;
    _38._30 = 3;
    _38._34 = 12;
    setDamageCallbackTiming(mActor, 4, &_38);
    changeChild("通常");
}

void PillarCrack::calc_() {}

void PillarCrack::leave_() {
    sub_71005DA114(mActor, &_38);
}

void PillarCrack::loadParams_() {}

}  // namespace uking::ai
