#include "Game/AI/AI/aiMoveAndFreeFallGondola.h"

namespace uking::ai {

MoveAndFreeFallGondola::MoveAndFreeFallGondola(const InitArg& arg) : RailMove(arg) {}

MoveAndFreeFallGondola::~MoveAndFreeFallGondola() = default;

bool MoveAndFreeFallGondola::init_(sead::Heap* heap) {
    return RailMove::init_(heap);
}

void MoveAndFreeFallGondola::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!_f0) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        return;
    }
    RailMove::enter_(params);
}

void MoveAndFreeFallGondola::m34() {}

f32 MoveAndFreeFallGondola::m35() {
    return *mRailMoveSpeed_m;
}

bool MoveAndFreeFallGondola::m40() {
    return false;
}

void MoveAndFreeFallGondola::leave_() {
    RailMove::leave_();
}

void MoveAndFreeFallGondola::loadParams_() {
    RailMove::loadParams_();
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
    getMapUnitParam(&mGondolaRailOffsetTime_m, "GondolaRailOffsetTime");
}

}  // namespace uking::ai
