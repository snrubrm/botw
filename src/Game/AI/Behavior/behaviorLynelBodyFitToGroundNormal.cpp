#include "Game/AI/Behavior/behaviorLynelBodyFitToGroundNormal.h"
#include "Game/AI/aiUnk_71025ba778.h"

namespace uking::behavior {

LynelBodyFitToGroundNormal::LynelBodyFitToGroundNormal(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

LynelBodyFitToGroundNormal::~LynelBodyFitToGroundNormal() = default;

bool LynelBodyFitToGroundNormal::m6(sead::Heap* heap) {
    return true;
}

void LynelBodyFitToGroundNormal::m7() {}

void LynelBodyFitToGroundNormal::m8() {
    if (auto* unit = sead::DynamicCast<Unk_71025ba778>(
            *static_cast<Unk_71025afb58**>(mLynelBodyControlUnit_a))) {
        unit->_1a8 = *mCorrectAngleMax_s;
        unit->sub_710070F79C(mActor);
    }
}

void LynelBodyFitToGroundNormal::m9() {
    if (auto* unit = sead::DynamicCast<Unk_71025ba778>(
            *static_cast<Unk_71025afb58**>(mLynelBodyControlUnit_a)))
        unit->sub_710070F820(mActor);
}

void LynelBodyFitToGroundNormal::loadParams() {
    getStaticParam(&mCorrectAngleMax_s, "CorrectAngleMax");
    getAITreeVariable(&mLynelBodyControlUnit_a, "LynelBodyControlUnit");
}

}  // namespace uking::behavior
