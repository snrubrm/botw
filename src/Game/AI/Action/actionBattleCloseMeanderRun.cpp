#include "Game/AI/Action/actionBattleCloseMeanderRun.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

BattleCloseMeanderRun::BattleCloseMeanderRun(const InitArg& arg) : BattleCloseMoveAction(arg) {}

BattleCloseMeanderRun::~BattleCloseMeanderRun() = default;

void BattleCloseMeanderRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
}

void BattleCloseMeanderRun::loadParams_() {
    BattleCloseMoveActionBase::loadParams_();
    getStaticParam(&mMeanderWidth_s, "MeanderWidth");
    getStaticParam(&mMeanderSpeed_s, "MeanderSpeed");
    getStaticParam(&mJumpUpSpeedReduceRatio_s, "JumpUpSpeedReduceRatio");
}

void BattleCloseMeanderRun::calc_() {
    BattleCloseMoveAction::calc_();
    if (*mJumpUpSpeedReduceRatio_s < 1.0f) {
        if (auto* controller = mActor->getCharacterController())
            sub_710073852C(controller, *mJumpUpSpeedReduceRatio_s);
    }
}

}  // namespace uking::action
