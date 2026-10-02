#include "Game/AI/Action/actionFreeze.h"

namespace uking::action {

Freeze::Freeze(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Freeze::~Freeze() = default;

bool Freeze::init_(sead::Heap* heap) {
    _68.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_68._0)) {
        if (!(unit->_b0 & 1)) {
            unit->_8.setName("Skl_Root");
            unit->_8._68 = sead::Matrix34f::ident;
            unit->_b4 = 0;
            unit->_b0 |= 1;
        }
    }
    return true;
}

void Freeze::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void Freeze::leave_() {
    ActionWithPosAngReduce::leave_();
}

void Freeze::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mIsChangeInAir_s, "IsChangeInAir");
    getStaticParam(&mTransBoneKey_s, "TransBoneKey");
    getAITreeVariable(&mIsKeepFreeze_a, "IsKeepFreeze");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void Freeze::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
