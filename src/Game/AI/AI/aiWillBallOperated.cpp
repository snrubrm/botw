#include "Game/AI/AI/aiWillBallOperated.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

WillBallOperated::WillBallOperated(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WillBallOperated::~WillBallOperated() = default;

bool WillBallOperated::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WillBallOperated::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WillBallOperated::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
}

void WillBallOperated::loadParams_() {
    getDynamicParam(&mParams.mWaitTime_d, "WaitTime");
    getDynamicParam(&mParams.mCommand_d, "Command");
    getDynamicParam(&mParams.mBasePos_d, "BasePos");
    getDynamicParam(&mParams.mTargetActor_d, "TargetActor");
    getStaticParam(&mParams.mWarpDist_s, "WarpDist");
    getStaticParam(&mParams.mAttakedChangeDist_s, "AttakedChangeDist");
    getStaticParam(&mParams.mIsAttackedTimeAffect_s, "IsAttackedTimeAffect");
}

bool WillBallOperated::handleMessage_(const ksys::Message* message) {
    if (_78._30 || !_78.m2(*message))
        return false;

    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    _70 = _78._38._44;
    return true;
}

}  // namespace uking::ai
