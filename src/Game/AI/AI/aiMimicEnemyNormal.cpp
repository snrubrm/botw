#include "Game/AI/AI/aiMimicEnemyNormal.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

MimicEnemyNormal::MimicEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

MimicEnemyNormal::~MimicEnemyNormal() = default;

void MimicEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

bool MimicEnemyNormal::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void MimicEnemyNormal::leave_() {
    EnemyNormal::leave_();
}

void MimicEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mPlayerForceFindDist_s, "PlayerForceFindDist");
    getStaticParam(&mRideHorseMaskPlayerFindDist_s, "RideHorseMaskPlayerFindDist");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

bool MimicEnemyNormal::isFinished() const {
    return ActionBase::isFinished() ||
           (isCurrentChild("プレイヤー発見") && getCurrentChild()->isFinished());
}

void MimicEnemyNormal::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("プレイヤー発見")) {
            if (getCurrentChild()->isFailed()) {
                sub_71005D8E9C(mActor);
                m37();
            } else {
                setFinished();
            }
            return;
        }
        if (isCurrentChild("待機")) {
            if (!sub_710039FFA8(false))
                m37();
            return;
        }
        if (isCurrentChild("擬態解除") || isCurrentChild("不審者発見")) {
            setFinished();
            return;
        }
    }
    if (getCurrentChild()->isChangeable()) {
        if (isCurrentChild("待機")) {
            if (sub_710039FFA8(false) || sub_71004A7894() || sub_71004A7BB4())
                return;
        }
        if (!isCurrentChild("擬態解除") && sub_71004A7D18()) {
            sub_71004A7DDC();
            return;
        }
    }
    if (isCurrentChild("プレイヤー発見") && sub_71005D8F28(mActor)) {
        auto* current = getCurrentChild();
        current->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    }
}

}  // namespace uking::ai
