#include "Game/AI/AI/aiOctarockServiceHideWait.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace uking::ai {

OctarockServiceHideWait::OctarockServiceHideWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OctarockServiceHideWait::~OctarockServiceHideWait() = default;

bool OctarockServiceHideWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OctarockServiceHideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = ksys::act::isAttClientEnabled(mActor, "AutoAim");
    _69 = ksys::act::isAttClientEnabled(mActor, "AutoAimHidden");
    sub_71004EF670();
}

void OctarockServiceHideWait::leave_() {
    if (_68)
        ksys::act::enableAttClient(mActor, "AutoAimHidden");
    if (!_69)
        ksys::act::disableAttClient(mActor, "AutoAim");
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EAE4(0);
    mActor->m93(0, 0.0f);
}

void OctarockServiceHideWait::loadParams_() {
    getStaticParam(&mSafeAreaDist_s, "SafeAreaDist");
    getStaticParam(&mSafeAreaDistRange_s, "SafeAreaDistRange");
    getStaticParam(&mMinWaitTime_s, "MinWaitTime");
    getStaticParam(&mMinWaitTimeRand_s, "MinWaitTimeRand");
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
    getStaticParam(&mNoticeWorryRange_s, "NoticeWorryRange");
}

bool OctarockServiceHideWait::isChangeable() const {
    return isCurrentChild("待機") && getCurrentChild()->isChangeable();
}

void OctarockServiceHideWait::sub_71004EF670() {
    if (_68)
        ksys::act::enableAttClient(mActor, "AutoAimHidden");
    if (!_69)
        ksys::act::disableAttClient(mActor, "AutoAim");
    const f32 time = *mMinWaitTime_s + *mMinWaitTimeRand_s * sead::GlobalRandom::instance()->getF32();
    _6c = ksys::Timer(time, time);
    changeChild("待機");
}

}  // namespace uking::ai
