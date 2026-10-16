#include "Game/Actor/Behavior/behaviorDisableWeakPointActor.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

DisableWeakPointActor::DisableWeakPointActor(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

DisableWeakPointActor::~DisableWeakPointActor() = default;

bool DisableWeakPointActor::init_(sead::Heap* heap) {
    return true;
}

void DisableWeakPointActor::calc() {}

void DisableWeakPointActor::enter() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        auto& link = enemy->getActorPartsActor(mWeakPointKey_s);
        if (link.hasProc())
            _38.sub_710070DCC0(&link, true);
    }
}

void DisableWeakPointActor::leave() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        auto& link = enemy->getActorPartsActor(mWeakPointKey_s);
        if (link.hasProc())
            _50.sub_710070DCC0(&link, true);
    }
}

void DisableWeakPointActor::loadParams() {
    getStaticParam(&mWeakPointKey_s, "WeakPointKey");
}

}  // namespace uking::behavior
