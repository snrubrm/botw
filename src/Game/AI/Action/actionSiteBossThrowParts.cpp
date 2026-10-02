#include "Game/AI/Action/actionSiteBossThrowParts.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

SiteBossThrowParts::SiteBossThrowParts(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossThrowParts::~SiteBossThrowParts() = default;

bool SiteBossThrowParts::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossThrowParts::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _b8 = *mTargetPos_d;
}

void SiteBossThrowParts::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossThrowParts::loadParams_() {
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mMaxNoiseDist_s, "MaxNoiseDist");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mPredictionFrame_s, "PredictionFrame");
    getStaticParam(&mIsCalcNextPos_s, "IsCalcNextPos");
    getStaticParam(&mIsCheckPlayerAround_s, "IsCheckPlayerAround");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mPartsName_s, "PartsName");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteBaseProcHandle_d, "IgniteBaseProcHandle");
}

void SiteBossThrowParts::calc_() {
    if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        m35();
    if (isFinishedAS(0, 0))
        setFinished();
    _b8 = *mTargetPos_d;
}

bool SiteBossThrowParts::isFinished() const {
    return isFinishedAS(0, 0);
}

const sead::SafeString& SiteBossThrowParts::m34() {
    return mPartsName_s;
}

void SiteBossThrowParts::m35() {
    sub_710026E3B0(true);
}

}  // namespace uking::action
