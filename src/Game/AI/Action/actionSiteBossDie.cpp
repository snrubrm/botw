#include "Game/AI/Action/actionSiteBossDie.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

SiteBossDie::SiteBossDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossDie::~SiteBossDie() = default;

bool SiteBossDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossDie::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossDie::loadParams_() {
    getStaticParam(&mWarpWaitTime_s, "WarpWaitTime");
    getStaticParam(&mIsUseYAxisSignal_s, "IsUseYAxisSignal");
}

void SiteBossDie::calc_() {
    if (mActor->getASList()->x(0x3b, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        _30 = ksys::eft::searchAndEmitELink(mActor, "WarpCharge");
        m32();
    }
    if (isFinishedAS(0, 0)) {
        _30.fade();
        setFinished();
    }
}

bool SiteBossDie::isFinished() const {
    if (isFinishedAS(0, 0))
        return true;
    return isFinishedAS(0, 0);
}

void SiteBossDie::m32() {
    if (*mIsUseYAxisSignal_s) {
        mActor->emitBasicSigOff();
        mActor->emitSignalAxisY_1();
    } else {
        mActor->emitBasicSigOn();
    }
}

}  // namespace uking::action
