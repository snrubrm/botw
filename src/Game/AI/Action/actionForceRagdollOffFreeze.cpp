#include "Game/AI/Action/actionForceRagdollOffFreeze.h"

namespace uking::action {

ForceRagdollOffFreeze::ForceRagdollOffFreeze(const InitArg& arg) : Freeze(arg) {}

ForceRagdollOffFreeze::~ForceRagdollOffFreeze() = default;

bool ForceRagdollOffFreeze::init_(sead::Heap* heap) {
    if (!Freeze::init_(heap))
        return false;
    _80.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    setupCRBOffsetUnit(_80);
    return true;
}

void ForceRagdollOffFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
}

void ForceRagdollOffFreeze::leave_() {
    Freeze::leave_();
}

void ForceRagdollOffFreeze::loadParams_() {
    Freeze::loadParams_();
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void ForceRagdollOffFreeze::calc_() {
    Freeze::calc_();
}

}  // namespace uking::action
