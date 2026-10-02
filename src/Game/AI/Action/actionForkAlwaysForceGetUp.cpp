#include "Game/AI/Action/actionForkAlwaysForceGetUp.h"

namespace uking::action {

ForkAlwaysForceGetUp::ForkAlwaysForceGetUp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAlwaysForceGetUp::~ForkAlwaysForceGetUp() = default;

bool ForkAlwaysForceGetUp::init_(sead::Heap* heap) {
    if (*mIsUseCRBOffsetUnit_s) {
        _78.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
        if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_78._0)) {
            if (!(unit->_b0 & 1)) {
                unit->_8.setName("Skl_Root");
                unit->_8._68 = sead::Matrix34f::ident;
                unit->_b4 = 0;
                unit->_b0 |= 1;
            }
        }
    }
    return true;
}

void ForkAlwaysForceGetUp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAlwaysForceGetUp::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAlwaysForceGetUp::loadParams_() {
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mRotSpdMin_s, "RotSpdMin");
    getStaticParam(&mRotSpdMax_s, "RotSpdMax");
    getStaticParam(&mIsUseCRBOffsetUnit_s, "IsUseCRBOffsetUnit");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void ForkAlwaysForceGetUp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
