#include "Game/AI/Action/actionForceRagdollOffFreeze.h"

namespace uking::action {

ForceRagdollOffFreeze::ForceRagdollOffFreeze(const InitArg& arg) : Freeze(arg) {}

ForceRagdollOffFreeze::~ForceRagdollOffFreeze() = default;

bool ForceRagdollOffFreeze::init_(sead::Heap* heap) {
    if (!Freeze::init_(heap))
        return false;
    _80.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_80._0)) {
        if (!(unit->_b0 & 1)) {
            unit->_8.setName("Skl_Root");
            unit->_8._68 = sead::Matrix34f::ident;
            unit->_b4 = 0;
            unit->_b0 |= 1;
        }
    }
    _80.sub_7100137A28(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    _80.x();
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
