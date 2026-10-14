#include "Game/Actor/Action/actionOneHandActionWithLegTurn.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

OneHandActionWithLegTurn::OneHandActionWithLegTurn(const InitArg& arg)
    : AttackWithAS(arg) {}

OneHandActionWithLegTurn::~OneHandActionWithLegTurn() = default;

bool OneHandActionWithLegTurn::init_(sead::Heap* heap) {
    return AttackWithAS::init_(heap);
}

void OneHandActionWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    AttackWithAS::enter_(params);
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

void OneHandActionWithLegTurn::leave_() {
    _180.sub_7100715B3C();
    AttackWithAS::leave_();
}

void OneHandActionWithLegTurn::loadParams_() {
    AttackWithAS::loadParams_();
    getStaticParam(&mTraceLRAngleMax_s, "TraceLRAngleMax");
    getStaticParam(&mTraceLRAngleMin_s, "TraceLRAngleMin");
    getStaticParam(&mTraceDistFar_s, "TraceDistFar");
    getStaticParam(&mTraceDistNear_s, "TraceDistNear");
    getStaticParam(&mShoulderBoneName_s, "ShoulderBoneName");
    getStaticParam(&mRotOffsetMin_s, "RotOffsetMin");
    getStaticParam(&mRotOffsetMax_s, "RotOffsetMax");
    getStaticParam(&mBaseTargetPos_s, "BaseTargetPos");
}

void OneHandActionWithLegTurn::calc_() {
    AttackWithAS::calc_();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD798(mActor, 0x2c, &query, 0, 0)) {
        if (query.name != "Stop")
            _180.sub_7100715B4C(mTargetPos_d);
    } else {
        _180.sub_7100716264(0.95f);
    }
}

}  // namespace uking::action
