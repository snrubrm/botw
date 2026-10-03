#include "Game/AI/Action/actionIgniteToTargetSimple.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

IgniteToTargetSimple::IgniteToTargetSimple(const InitArg& arg) : OnetimeStopASPlay(arg) {}

IgniteToTargetSimple::~IgniteToTargetSimple() = default;

bool IgniteToTargetSimple::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void IgniteToTargetSimple::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void IgniteToTargetSimple::leave_() {
    OnetimeStopASPlay::leave_();
}

void IgniteToTargetSimple::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mIsConnectChild_s, "IsConnectChild");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
}

void IgniteToTargetSimple::calc_() {
    OnetimeStopASPlay::calc_();
    if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        auto* handle = *mIgniteHandle_d;
        m32(handle);
    }
}

}  // namespace uking::action
