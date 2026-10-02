#include "Game/AI/AI/aiEnemyRoamViewItem.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyRoamViewItem::EnemyRoamViewItem(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRoamViewItem::~EnemyRoamViewItem() = default;

bool EnemyRoamViewItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRoamViewItem::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsChanged_d) {
        ksys::act::ai::InlineParamPack pack;
        pack.addActor(*mTargetActor_d, "TargetActor", -1);
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("変化感知", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addActor(*mTargetActor_d, "TargetActor", -1);
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("行動", &pack);
    }
}

void EnemyRoamViewItem::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRoamViewItem::loadParams_() {
    getDynamicParam(&mIsChanged_d, "IsChanged");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool EnemyRoamViewItem::isFinished() const {
    return isCurrentChild("行動") && getCurrentChild()->isFinished();
}

void EnemyRoamViewItem::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("変化感知")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addActor(*mTargetActor_d, "TargetActor", -1);
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("行動", &pack);
        }
    } else {
        child->isChangeable();
    }
}

bool EnemyRoamViewItem::m34() {
    if (isCurrentChild("行動"))
        return getCurrentChild()->isFailed();
    return false;
}

}  // namespace uking::ai
