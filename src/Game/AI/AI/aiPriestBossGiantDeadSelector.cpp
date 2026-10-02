#include "Game/AI/AI/aiPriestBossGiantDeadSelector.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::ai {

PriestBossGiantDeadSelector::PriestBossGiantDeadSelector(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PriestBossGiantDeadSelector::~PriestBossGiantDeadSelector() = default;

bool PriestBossGiantDeadSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossGiantDeadSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.reset(Flag::Changeable);
    if (auto* body_set = mActor->getRigidBodyByName(sub_71007A24D0()->cstr()))
        body_set->removeFromWorld();
    if (*mPriestBossDownSideASPlaying_a)
        changeChild("ダウン状態");
    else
        changeChild("立ち状態");
}

void PriestBossGiantDeadSelector::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        setFinished();
}

void PriestBossGiantDeadSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossGiantDeadSelector::loadParams_() {
    getAITreeVariable(&mPriestBossDownSideASPlaying_a, "PriestBossDownSideASPlaying");
}

}  // namespace uking::ai
