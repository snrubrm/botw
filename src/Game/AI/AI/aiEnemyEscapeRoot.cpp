#include "Game/AI/AI/aiEnemyEscapeRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyEscapeRoot::EnemyEscapeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyEscapeRoot::~EnemyEscapeRoot() = default;

void EnemyEscapeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyEscapeRoot::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyEscapeRoot::loadParams_() {
    if (mActor->getParam())
        getDynamicParam(&mTargetPos_d, "TargetPos");
}

void EnemyEscapeRoot::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("逃走開始振り向き")) {
            sead::Vector3f pos = *mTargetPos_d;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(pos, "TargetPos", -1);
            changeChild("逃走", &pack);
            return;
        }
        if (isCurrentChild("逃走終了振り向き")) {
            setFinished();
            return;
        }
        if (isCurrentChild("逃走")) {
            sead::Vector3f pos = *mTargetPos_d;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(pos, "TargetPos", -1);
            changeChild("逃走終了振り向き", &pack);
            return;
        }
    }

    if (isCurrentChild("逃走開始振り向き") || isCurrentChild("逃走終了振り向き") ||
        isCurrentChild("逃走")) {
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    }
}

}  // namespace uking::ai
