#include "Game/AI/AI/aiEnemyTired.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyTired::EnemyTired(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyTired::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    changeChild("見まわす");
}

void EnemyTired::loadParams_() {}

void EnemyTired::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("帰還")) {
        if (isFailed())
            setFailed();
        else
            setFinished();
    } else {
        sub_71003C16B0();
    }
}

void EnemyTired::sub_71003C16B0() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    mActor->getHomePos(&pos);
    params.addVec3(pos, "TargetPos", -1);
    changeChild("帰還", &params);
}

}  // namespace uking::ai
