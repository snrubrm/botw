#include "Game/AI/Action/actionIgniteToTarget.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

IgniteToTarget::IgniteToTarget(const InitArg& arg) : OnetimeStopASPlay(arg) {}

IgniteToTarget::~IgniteToTarget() = default;

bool IgniteToTarget::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void IgniteToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void IgniteToTarget::leave_() {
    OnetimeStopASPlay::leave_();
}

void IgniteToTarget::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mMaxNoiseDist_s, "MaxNoiseDist");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
    getStaticParam(&mBaseNode_s, "BaseNode");
}

void IgniteToTarget::calc_() {
    OnetimeStopASPlay::calc_();
    if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        sub_71001B734C(m32());
}

ksys::act::BaseProcHandle* IgniteToTarget::m32() {
    return *mIgniteHandle_d;
}

const sead::Vector3f* IgniteToTarget::m33() {
    return mIgniteOffset_s;
}

const sead::Vector3f* IgniteToTarget::m34() {
    return mIgniteRotate_s;
}

f32 IgniteToTarget::m35(ksys::act::Actor* actor) {
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, actor);
    return gravity.y * (1.0f / 900.0f);
}

}  // namespace uking::action
