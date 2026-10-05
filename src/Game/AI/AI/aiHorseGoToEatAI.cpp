#include "Game/AI/AI/aiHorseGoToEatAI.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

HorseGoToEatAI::HorseGoToEatAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseGoToEatAI::~HorseGoToEatAI() = default;

bool HorseGoToEatAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseGoToEatAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(*mTargetActor_d, "TargetActor", -1);
    pack.addFloat(0.0f, "DistanceKept", -1);
    changeChild("移動", &pack);
    _48 = 0.0f;

    ksys::act::ActorConstDataAccess acc;
    u32 id = -1;
    if (ksys::act::acquireActor(mTargetActor_d, &acc))
        id = acc.getId();
    _4c = id;
}

void HorseGoToEatAI::leave_() {
    if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor))
        horse->sub_7100E6C464(_4c);
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->_18.sub_7100E770C4(false);
}

void HorseGoToEatAI::loadParams_() {
    getStaticParam(&mTimeoutFrame_s, "TimeoutFrame");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void HorseGoToEatAI::calc_() {
    if (isCurrentChild("移動")) {
        if (*mTimeoutFrame_s >= 1) {
            ksys::Timer::update(&_48, 1.0f);
            if (_48 > *mTimeoutFrame_s) {
                setFailed();
                return;
            }
        }
        if (!mTargetActor_d->hasProc()) {
            setFailed();
            return;
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("移動")) {
            if (child->isFinished()) {
                ksys::act::ai::InlineParamPack pack;
                pack.addActor(*mTargetActor_d, "TargetActor", -1);
                changeChild("食べる", &pack);
            } else {
                setFailed();
            }
        } else if (child->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    } else {
        child->isChangeable();
    }
}

}  // namespace uking::ai
