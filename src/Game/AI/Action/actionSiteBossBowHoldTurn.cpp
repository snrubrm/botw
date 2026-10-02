#include "Game/AI/Action/actionSiteBossBowHoldTurn.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

SiteBossBowHoldTurn::SiteBossBowHoldTurn(const InitArg& arg) : TurnBase(arg) {}

SiteBossBowHoldTurn::~SiteBossBowHoldTurn() = default;

bool SiteBossBowHoldTurn::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void SiteBossBowHoldTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void SiteBossBowHoldTurn::leave_() {
    TurnBase::leave_();
}

void SiteBossBowHoldTurn::loadParams_() {
    TurnBase::loadParams_();
    getStaticParam(&mSpineControlOffsetAngleLR_s, "SpineControlOffsetAngleLR");
    getStaticParam(&mSpineControlOffsetAngleUD_s, "SpineControlOffsetAngleUD");
    getStaticParam(&mASName_s, "ASName");
}

void SiteBossBowHoldTurn::calc_() {
    TurnBase::calc_();
    sub_71005DB51C(mActor, *mSpineControlOffsetAngleLR_s, true);
    sub_71005DB558(mActor, *mSpineControlOffsetAngleUD_s, true);
}

}  // namespace uking::action
