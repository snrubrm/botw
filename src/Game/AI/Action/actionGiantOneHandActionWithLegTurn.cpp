#include "Game/AI/Action/actionGiantOneHandActionWithLegTurn.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

GiantOneHandActionWithLegTurn::GiantOneHandActionWithLegTurn(const InitArg& arg)
    : GiantAttackWithAS(arg) {}

GiantOneHandActionWithLegTurn::~GiantOneHandActionWithLegTurn() = default;

bool GiantOneHandActionWithLegTurn::init_(sead::Heap* heap) {
    return GiantAttackWithAS::init_(heap);
}

void GiantOneHandActionWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantAttackWithAS::enter_(params);
    _180._24 = *mRotOffsetMax_s;
    _180._18 = *mRotOffsetMin_s;
    _180._30 = *mBaseTargetPos_s;
    _180._f4 = *mTraceDistFar_s;
    _180._f0 = *mTraceDistNear_s;
    _180._ec = *mTraceLRAngleMax_s;
    _180._e8 = *mTraceLRAngleMin_s;
    _180._f8 = true;
    _180.sub_7100715A20(mTargetPos_d, mShoulderBoneName_s);
}

void GiantOneHandActionWithLegTurn::leave_() {
    _180.sub_7100715B3C();
    GiantAttackWithAS::leave_();
}

void GiantOneHandActionWithLegTurn::loadParams_() {
    GiantAttackWithAS::loadParams_();
    getStaticParam(&mTraceLRAngleMax_s, "TraceLRAngleMax");
    getStaticParam(&mTraceLRAngleMin_s, "TraceLRAngleMin");
    getStaticParam(&mTraceDistFar_s, "TraceDistFar");
    getStaticParam(&mTraceDistNear_s, "TraceDistNear");
    getStaticParam(&mShoulderBoneName_s, "ShoulderBoneName");
    getStaticParam(&mRotOffsetMin_s, "RotOffsetMin");
    getStaticParam(&mRotOffsetMax_s, "RotOffsetMax");
    getStaticParam(&mBaseTargetPos_s, "BaseTargetPos");
}

void GiantOneHandActionWithLegTurn::calc_() {
    GiantAttackWithAS::calc_();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD798(mActor, 0x2c, &query, 0, 0)) {
        if (query.name != "Stop")
            _180.sub_7100715B4C(mTargetPos_d);
    } else {
        _180.sub_7100716264(0.95f);
    }
}

}  // namespace uking::action
