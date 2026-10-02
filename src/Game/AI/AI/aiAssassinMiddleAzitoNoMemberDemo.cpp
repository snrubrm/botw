#include "Game/AI/AI/aiAssassinMiddleAzitoNoMemberDemo.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

// NON_MATCHING: the zero store to _d0 is scheduled before the _c0-_cc stores
AssassinMiddleAzitoNoMemberDemo::AssassinMiddleAzitoNoMemberDemo(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinMiddleAzitoNoMemberDemo::~AssassinMiddleAzitoNoMemberDemo() = default;

bool AssassinMiddleAzitoNoMemberDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: scheduling of the nullptr argument of changeChild
void AssassinMiddleAzitoNoMemberDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    _48.x();
    const s32 min = *mDelayTimeMin_s;
    const s32 max = *mDelayTimeMax_s;
    _c4 = sead::Mathi::min(min, max);
    _c8 = sead::Mathi::max(min, max);
    const s32 delay = _c4 == _c8 ? _c4 : sead::GlobalRandom::instance()->getS32Range(_c4, _c8);
    _cc = false;
    _c0 = delay;
    changeChild("待機");
}

void AssassinMiddleAzitoNoMemberDemo::calc_() {
    f32& timer = _c0;
    if (_cc)
        ksys::Timer::update(&timer, -1.0f);
    else if (_48._30)
        _cc = true;

    if (isCurrentChild("気づき")) {
        if (_d0 < 0.0f)
            mActor->m93(0, 0.0f);
        else
            _d0 = -1.0f;
    }

    auto* child = getCurrentChild();
    if (child->isFinished()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }
    if (child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }

    if (child->isChangeable() && isCurrentChild("待機") && timer < 0.0f)
        sub_710031E040();
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

void AssassinMiddleAzitoNoMemberDemo::sub_710031E040() {
    mActor->m93(4, 0.0f);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    _d0 = 20.0f;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_48._38.mData._0, &accessor);
    sub_71005D8DE8(mActor, _48._38.mData._0, &accessor.getActorMtx(), nullptr);

    ksys::act::ai::InlineParamPack params;
    params.addVec3(_48._38.mData._28, "TargetPos", -1);
    changeChild("気づき", &params);
    _48.x();
}

}  // namespace uking::ai
