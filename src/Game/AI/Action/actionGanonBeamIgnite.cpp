#include "Game/AI/Action/actionGanonBeamIgnite.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

GanonBeamIgnite::GanonBeamIgnite(const InitArg& arg) : OnetimeStopASPlay(arg) {}

GanonBeamIgnite::~GanonBeamIgnite() = default;

bool GanonBeamIgnite::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void GanonBeamIgnite::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void GanonBeamIgnite::leave_() {
    OnetimeStopASPlay::leave_();
}

void GanonBeamIgnite::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mIsConnectChild_s, "IsConnectChild");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteActor_d, "IgniteActor");
}

void GanonBeamIgnite::calc_() {
    OnetimeStopASPlay::calc_();
    if (sub_71005DD780(mActor, 71, nullptr, 0, 0))
        sub_71001745F8();
}

}  // namespace uking::action
