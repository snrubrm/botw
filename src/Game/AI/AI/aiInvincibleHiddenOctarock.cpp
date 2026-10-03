#include "Game/AI/AI/aiInvincibleHiddenOctarock.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

InvincibleHiddenOctarock::InvincibleHiddenOctarock(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InvincibleHiddenOctarock::~InvincibleHiddenOctarock() = default;

bool InvincibleHiddenOctarock::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InvincibleHiddenOctarock::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* damage_mgr = mActor->getDamageMgr())
        damage_mgr->addDamageCallback(4, &_38);
    changeChild("待機", params);
}

void InvincibleHiddenOctarock::calc_() {
    auto* child_actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (sub_71007A274C(mActor) || (child_actor && sub_71007A274C(child_actor))) {
        changeChild("リアクション");
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("待機"))
            setFinished();
        else
            changeChild("待機");
        return;
    }
    child->isChangeable();
}

void InvincibleHiddenOctarock::leave_() {
    if (auto* damage_mgr = mActor->getDamageMgr())
        damage_mgr->removeDamageCallback(&_38);
}

void InvincibleHiddenOctarock::loadParams_() {}

}  // namespace uking::ai
