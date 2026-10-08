#include "Game/AI/Action/actionEat.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"

namespace uking::action {

Eat::Eat(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Eat::~Eat() = default;

void Eat::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    m32();
}

void Eat::leave_() {
    if (auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
        child->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    ActionWithPosAngReduce::leave_();
}

void Eat::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mIsHeal_s, "IsHeal");
}

void Eat::calc_() {
    ActionWithPosAngReduce::calc_();
    if (!isFinishedAS(0, 0))
        return;
    if (auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild())) {
        child->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        if (*mIsHeal_s) {
            if (mActor->getLifeRecoverInfo())
                mActor->getLifeRecoverInfo()->sub_7100D68AD4();
            auto* actor = mActor;
            const s32 max_life = actor->getMaxLife();
            if (s32* life = actor->getLife())
                *life = max_life;
        }
        setFinished();
        return;
    }
    setFailed();
}

void Eat::m32() {
    playAS("Eat", false, 0, 0, -1.0f);
}

}  // namespace uking::action
