#include "Game/AI/Action/actionForceRagdollOffWaterFloatFreeze.h"

namespace uking::action {

ForceRagdollOffWaterFloatFreeze::ForceRagdollOffWaterFloatFreeze(const InitArg& arg)
    : WaterFloatFreeze(arg) {}

ForceRagdollOffWaterFloatFreeze::~ForceRagdollOffWaterFloatFreeze() = default;

bool ForceRagdollOffWaterFloatFreeze::init_(sead::Heap* heap) {
    if (!WaterFloatFreeze::init_(heap))
        return false;
    _80.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_80.mHolder)) {
        if (!(unit->_b0 & 1)) {
            unit->_8.setName("Skl_Root");
            unit->_8._68 = sead::Matrix34f::ident;
            unit->_b4 = 0;
            unit->_b0 |= 1;
        }
    }
    return true;
}

void ForceRagdollOffWaterFloatFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatFreeze::enter_(params);
}

void ForceRagdollOffWaterFloatFreeze::loadParams_() {
    WaterFloatFreeze::loadParams_();
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

}  // namespace uking::action
