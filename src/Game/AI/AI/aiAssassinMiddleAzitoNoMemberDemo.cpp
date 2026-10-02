#include "Game/AI/AI/aiAssassinMiddleAzitoNoMemberDemo.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

// NON_MATCHING: the zero store to _d0 is scheduled before the _c0-_cc stores
AssassinMiddleAzitoNoMemberDemo::AssassinMiddleAzitoNoMemberDemo(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinMiddleAzitoNoMemberDemo::~AssassinMiddleAzitoNoMemberDemo() = default;

bool AssassinMiddleAzitoNoMemberDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AssassinMiddleAzitoNoMemberDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AssassinMiddleAzitoNoMemberDemo::leave_() {
    mActor->m93(0, 0.0f);
}

void AssassinMiddleAzitoNoMemberDemo::loadParams_() {
    getStaticParam(&mDelayTimeMin_s, "DelayTimeMin");
    getStaticParam(&mDelayTimeMax_s, "DelayTimeMax");
}

bool AssassinMiddleAzitoNoMemberDemo::handleMessage_(const ksys::Message& message) {
    if (!isCurrentChild("待機") || _48._30)
        return false;
    return _48.m2(message);
}

}  // namespace uking::ai
