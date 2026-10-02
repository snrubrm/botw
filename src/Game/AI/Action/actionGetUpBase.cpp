#include "Game/AI/Action/actionGetUpBase.h"

namespace uking::action {

GetUpBase::GetUpBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GetUpBase::~GetUpBase() = default;

bool GetUpBase::init_(sead::Heap* heap) {
    _138.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_138._0)) {
        if (!(unit->_b0 & 1)) {
            unit->_8.setName("Skl_Root");
            unit->_8._68 = sead::Matrix34f::ident;
            unit->_b4 = 0;
            unit->_b0 |= 1;
        }
    }
    _138.sub_7100137A28(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    _138.x();
    return true;
}

void GetUpBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GetUpBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void GetUpBase::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mRootOffset_s, "RootOffset");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void GetUpBase::calc_() {
    ksys::act::ai::Action::calc_();
}

bool GetUpBase::isChangeable() const {
    return false;
}

bool GetUpBase::isFinished() const {
    return isFinishedAS(0, 0);
}

}  // namespace uking::action
