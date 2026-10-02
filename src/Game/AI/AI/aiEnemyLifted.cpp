#include "Game/AI/AI/aiEnemyLifted.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::ai {

EnemyLifted::EnemyLifted(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyLifted::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLifted::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* dynamic = sead::DynamicCast<ksys::act::DynamicActor>(mActor))
        dynamic->_a68 &= ~1;
    setDamageCallbackTiming(mActor, 4, &_48);
    auto* actor = mActor;
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_40000000);
    actor->getPhysics()->sub_7100FBADDC();
    changeChild("所持");
}

void EnemyLifted::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyLifted::m34() {}

void EnemyLifted::loadParams_() {}

bool EnemyLifted::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;
    if (isCurrentChild("着地"))
        return getCurrentChild()->isFinished();
    return false;
}

}  // namespace uking::ai
