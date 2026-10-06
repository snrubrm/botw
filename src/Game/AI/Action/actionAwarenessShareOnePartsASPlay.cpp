#include "Game/AI/Action/actionAwarenessShareOnePartsASPlay.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AwarenessShareOnePartsASPlay::AwarenessShareOnePartsASPlay(const InitArg& arg)
    : OnetimeStopASPlay(arg) {}

AwarenessShareOnePartsASPlay::~AwarenessShareOnePartsASPlay() = default;

bool AwarenessShareOnePartsASPlay::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void AwarenessShareOnePartsASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void AwarenessShareOnePartsASPlay::leave_() {
    OnetimeStopASPlay::leave_();
    auto* actor = mActor;
    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    if (!enemy)
        return;

    auto& link = enemy->getActorPartsActor(mPartsKey_s);
    if (!link.hasProc())
        return;

    auto* target = sub_71005D9050(mActor);
    auto* owner = mActor;
    const sead::Vector3f& pos = sub_71005D9330(owner);
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_58._18.mLock);
        auto& data = _58._18.mData;
        if (target)
            data._0 = *target;
        else
            data._0.reset();
        data._10.acquire(owner, false);
        data._20 = 0;
        data._24 = 2;
        data._28 = pos;
        data._34 = 0;
    }
    _58.sub_710070DCC0(&link, true);
}

void AwarenessShareOnePartsASPlay::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mPartsKey_s, "PartsKey");
}

void AwarenessShareOnePartsASPlay::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
