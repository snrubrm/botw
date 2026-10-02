#include "Game/AI/AI/aiAssassinShooterJuniorAzitoRoot.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

AssassinShooterJuniorAzitoRoot::AssassinShooterJuniorAzitoRoot(const InitArg& arg)
    : RememberMesOneActorEnemyRoot(arg) {}

AssassinShooterJuniorAzitoRoot::~AssassinShooterJuniorAzitoRoot() = default;

bool AssassinShooterJuniorAzitoRoot::init_(sead::Heap* heap) {
    return RememberMesOneActorEnemyRoot::init_(heap);
}

void AssassinShooterJuniorAzitoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RememberMesOneActorEnemyRoot::enter_(params);
}

void AssassinShooterJuniorAzitoRoot::leave_() {
    RememberMesOneActorEnemyRoot::leave_();
}

void AssassinShooterJuniorAzitoRoot::loadParams_() {
    RememberMesOneActorEnemyRoot::loadParams_();
}

void AssassinShooterJuniorAzitoRoot::calc_() {
    auto* prev_child = getCurrentChild();
    RememberMesOneActorEnemyRoot::calc_();
    if (prev_child == getCurrentChild() || !isCurrentChild("リアクション"))
        return;

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    auto& link = enemy->getActorPartsActor(mRememberKey_s);
    if (!link.hasProc())
        return;

    auto* target = sub_71005D9050(mActor);
    auto* actor = mActor;
    const auto& target_pos = sub_71005D9330(actor);
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_268._18.mLock);
        auto& data = _268._18.mData;
        if (target)
            data._0 = *target;
        else
            data._0.reset();
        data._10.acquire(actor, false);
        data._20 = 0;
        data._24 = 2;
        data._28 = target_pos;
        data._34 = 0;
    }
    _268.sub_710070DCC0(&link, true);
}

}  // namespace uking::ai
