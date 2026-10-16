#include "Game/Actor/Behavior/behaviorPartsMagneFollowRatioChanger.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::behavior {

PartsMagneFollowRatioChanger::PartsMagneFollowRatioChanger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
PartsMagneFollowRatioChanger::~PartsMagneFollowRatioChanger() {
    ;
}

bool PartsMagneFollowRatioChanger::init_(sead::Heap* heap) {
    return true;
}

void PartsMagneFollowRatioChanger::calc() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        auto& link = enemy->getActorPartsActor(mPartsName_s);
        if (link.hasProcInCalcState()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (accessor.sub_7100D13BB8()) {
                _40._18 = *mRatio_s;
                _40.sub_710070DCC0(&link, true);
            }
        }
    }
}

void PartsMagneFollowRatioChanger::enter() {}

void PartsMagneFollowRatioChanger::leave() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        auto& link = enemy->getActorPartsActor(mPartsName_s);
        if (link.hasProcInCalcState()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (accessor.sub_7100D13BB8()) {
                _40._18 = 1.0f;
                _40.sub_710070DCC0(&link, true);
            }
        }
    }
}

void PartsMagneFollowRatioChanger::loadParams() {
    getStaticParam(&mRatio_s, "Ratio");
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::behavior
