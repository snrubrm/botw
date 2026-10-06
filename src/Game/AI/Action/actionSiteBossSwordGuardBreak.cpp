#include "Game/AI/Action/actionSiteBossSwordGuardBreak.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

SiteBossSwordGuardBreak::SiteBossSwordGuardBreak(const InitArg& arg) : OnetimeStopASPlay(arg) {}

SiteBossSwordGuardBreak::~SiteBossSwordGuardBreak() = default;

bool SiteBossSwordGuardBreak::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

// NON_MATCHING: scheduling only: the original builds the "Break_Shield" SafeString temporary before it loads mActor /
// the ASList, ours loads them first
void SiteBossSwordGuardBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getASList()->goLimpFromHeadShotMaybe(0x2f, "Break_Shield", 0);
    xlinkSearchAndEmit(mActor, "ShieldBreak", 2, nullptr);
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->_14c8._30.set(0x4);
        boss->sub_71002D1FD4();
        boss->x_6(false);
        act::SiteBoss::sub_71002D3498(boss, mActor);
    }
    playAS("Break_Shield", false, 3, 0, -1.0f);
    OnetimeStopASPlay::enter_(params);
}

void SiteBossSwordGuardBreak::leave_() {
    OnetimeStopASPlay::leave_();
}

void SiteBossSwordGuardBreak::loadParams_() {
    OnetimeStopASPlay::loadParams_();
}

void SiteBossSwordGuardBreak::calc_() {
    OnetimeStopASPlay::calc_();
}

bool SiteBossSwordGuardBreak::isChangeable() const {
    return true;
}

}  // namespace uking::action
