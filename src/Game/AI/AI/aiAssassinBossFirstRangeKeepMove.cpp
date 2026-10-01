#include "Game/AI/AI/aiAssassinBossFirstRangeKeepMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

AssassinBossFirstRangeKeepMove::AssassinBossFirstRangeKeepMove(const InitArg& arg)
    : EnemyRangeKeepMove(arg) {}

AssassinBossFirstRangeKeepMove::~AssassinBossFirstRangeKeepMove() = default;

bool AssassinBossFirstRangeKeepMove::init_(sead::Heap* heap) {
    if (!EnemyRangeKeepMove::init_(heap))
        return false;
    sub_7100317AB8();
    return true;
}

void AssassinBossFirstRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f target_pos = sub_71005D9330(mActor);
    const sead::Vector3f diff = target_pos - _128;
    if (sqrtf(diff.x * diff.x + diff.z * diff.z) > *mNoMoveAnchorDist_s) {
        EnemyRangeKeepMove::enter_(params);
        return;
    }
    if (sub_71003AD298() && !sub_71003AD058())
        sub_71003AB8A0();
    else
        sub_71003ABF50();
}

void AssassinBossFirstRangeKeepMove::leave_() {
    EnemyRangeKeepMove::leave_();
}

void AssassinBossFirstRangeKeepMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
    getStaticParam(&mNoMoveAnchorDist_s, "NoMoveAnchorDist");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

void AssassinBossFirstRangeKeepMove::calc_() {
    const sead::Vector3f target_pos = sub_71005D9330(mActor);
    const sead::Vector3f diff = target_pos - _128;
    if (!(sqrtf(diff.x * diff.x + diff.z * diff.z) > *mNoMoveAnchorDist_s)) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            sub_71003ABF50();
            return;
        }
        if (isCurrentChild("戦闘待機")) {
            getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
            return;
        }
    }
    EnemyRangeKeepMove::calc_();
}

}  // namespace uking::ai
