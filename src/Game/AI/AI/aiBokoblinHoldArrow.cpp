#include "Game/AI/AI/aiBokoblinHoldArrow.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

BokoblinHoldArrow::BokoblinHoldArrow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void BokoblinHoldArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("溜め", &pack);
}

void BokoblinHoldArrow::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("溜め")) {
            if (getCurrentChild()->isFailed()) {
                setFailed();
                return;
            }
        } else if (isCurrentChild("発射")) {
            setFinished();
            return;
        }
    }

    if (isCurrentChild("溜め") && getCurrentChild()->isChangeable()) {
        auto* actor = mActor;
        if (!sead::IsDerivedFrom<act::Enemy>(actor))
            return;
        auto* enemy = static_cast<act::Enemy*>(actor);
        if (enemy->_e68.value <= sead::Mathf::epsilon() || sub_71005DFBE4(enemy, 999.0f, 1.7453293f)) {
            sead::Vector3f pos = *mTargetPos_d;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(pos, "TargetPos", -1);
            changeChild("発射", &pack);
        }
    }
}

bool BokoblinHoldArrow::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void BokoblinHoldArrow::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool BokoblinHoldArrow::isFinished() const {
    return ActionBase::isFinished() || (getCurrentChild()->isFinished() && isCurrentChild("発射"));
}

}  // namespace uking::ai
