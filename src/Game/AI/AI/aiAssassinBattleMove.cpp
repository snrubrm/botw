#include "Game/AI/AI/aiAssassinBattleMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AssassinBattleMove::AssassinBattleMove(const InitArg& arg) : EnemyRangeKeepMove(arg) {}

AssassinBattleMove::~AssassinBattleMove() = default;

bool AssassinBattleMove::init_(sead::Heap* heap) {
    return EnemyRangeKeepMove::init_(heap);
}

void AssassinBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    const sead::Vector3f target_pos = sub_71005D9330(actor);
    const sead::Vector3f diff = target_pos - actor->getMtx().getTranslation();
    if (diff.x * diff.x + diff.z * diff.z < *mWarpDist_s * *mWarpDist_s) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("転移", &pack);
    } else {
        EnemyRangeKeepMove::enter_(params);
    }
}

void AssassinBattleMove::leave_() {
    EnemyRangeKeepMove::leave_();
}

void AssassinBattleMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
    getStaticParam(&mWarpDist_s, "WarpDist");
}

void AssassinBattleMove::calc_() {
    auto* child = getCurrentChild();
    if (isCurrentChild("転移")) {
        child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
        if (child->isFinished() || child->isFailed())
            sub_71003ABF50();
        return;
    }

    if (child->isChangeable()) {
        auto* actor = mActor;
        const sead::Vector3f target_pos = sub_71005D9330(actor);
        const sead::Vector3f diff = target_pos - actor->getMtx().getTranslation();
        if (diff.x * diff.x + diff.z * diff.z < *mWarpDist_s * *mWarpDist_s) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("転移", &pack);
            return;
        }
    }
    EnemyRangeKeepMove::calc_();
}

}  // namespace uking::ai
