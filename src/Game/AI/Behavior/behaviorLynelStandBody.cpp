#include "Game/AI/Behavior/behaviorLynelStandBody.h"
#include "Game/AI/aiUnk_71025ba778.h"

namespace uking::behavior {

LynelStandBody::LynelStandBody(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

LynelStandBody::~LynelStandBody() = default;

bool LynelStandBody::m6(sead::Heap* heap) {
    return true;
}

void LynelStandBody::m7() {}

void LynelStandBody::m8() {
    if (auto* unit = sead::DynamicCast<Unk_71025ba778>(*static_cast<Unk_71025afb58**>(mLynelBodyControlUnit_a)))
        unit->_c = 1.0f;
}

void LynelStandBody::m9() {
    if (auto* unit = sead::DynamicCast<Unk_71025ba778>(*static_cast<Unk_71025afb58**>(mLynelBodyControlUnit_a)))
        unit->_c = 0.0f;
}

void LynelStandBody::loadParams() {
    getStaticParam(&mStandRatioFB_s, "StandRatioFB");
    getStaticParam(&mStandRatioLR_s, "StandRatioLR");
    getAITreeVariable(&mLynelBodyControlUnit_a, "LynelBodyControlUnit");
}

}  // namespace uking::behavior
