#include "Game/AI/Action/actionForkASTrgTurnGround.h"

namespace uking::action {

ForkASTrgTurnGround::ForkASTrgTurnGround(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgTurnGround::~ForkASTrgTurnGround() = default;

bool ForkASTrgTurnGround::init_(sead::Heap* heap) {
    _58.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_58._0)) {
        if (!(unit->_b0 & 1)) {
            unit->_8.setName("Skl_Root");
            unit->_8._68 = sead::Matrix34f::ident;
            unit->_b4 = 0;
            unit->_b0 |= 1;
        }
    }
    _58.sub_7100137A28(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    _58.x();
    return true;
}

void ForkASTrgTurnGround::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASTrgTurnGround::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgTurnGround::loadParams_() {
    getStaticParam(&mSpeedBasePosRatio_s, "SpeedBasePosRatio");
    getStaticParam(&mOnAfterGroundRotAngle_s, "OnAfterGroundRotAngle");
    getStaticParam(&mAxis_s, "Axis");
    getStaticParam(&mCtrlOffset_s, "CtrlOffset");
    getStaticParam(&mCtrlAngleOffset_s, "CtrlAngleOffset");
    getStaticParam(&mActMoveVec_s, "ActMoveVec");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void ForkASTrgTurnGround::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
