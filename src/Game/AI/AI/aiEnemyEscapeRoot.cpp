#include "Game/AI/AI/aiEnemyEscapeRoot.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyEscapeRoot::EnemyEscapeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyEscapeRoot::~EnemyEscapeRoot() = default;

// NON_MATCHING: Matrix and target loads are scheduled differently around normalization.
void EnemyEscapeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_7100736D98(mActor) || testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        sead::Vector3f direction = *mTargetPos_d - mActor->getMtx().getTranslation();
        direction.y = 0.0f;
        const sead::Vector3f front = mActor->getMtx().getBase(2);
        direction.normalize();
        if (!(front.dot(direction) > 0.0f)) {
            const sead::Vector3f target = *mTargetPos_d;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target, "TargetPos", -1);
            changeChild("逃走", &pack);
            return;
        }
    }
    sub_710038B1C4();
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
