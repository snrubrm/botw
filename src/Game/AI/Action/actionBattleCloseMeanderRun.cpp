#include "Game/AI/Action/actionBattleCloseMeanderRun.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

BattleCloseMeanderRun::BattleCloseMeanderRun(const InitArg& arg) : BattleCloseMoveAction(arg) {}

BattleCloseMeanderRun::~BattleCloseMeanderRun() = default;

// NON_MATCHING: scheduling only (the original stores _d4.y = 0 before the first subtraction)
void BattleCloseMeanderRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
    m40();
    _c0 = 0.0f;
    if (sead::GlobalRandom::instance()->getBool())
        _c0 = sead::Mathf::pi();
    _c4 = 0.0f;
    _c8 = 0.0f;
    _cc = 0.0f;
    _d0 = 0.3f;
    mActor->getMtx().getTranslation(_e0);
    _d4 = sead::Vector3f(mParams.mTargetPos_d->x - _e0.x, 0.0f, mParams.mTargetPos_d->z - _e0.z);
    _d4.normalize();
    _ec = _e0;
    _f8 = false;
    _f9 = false;
    _fa = true;
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

f32 BattleCloseMeanderRun::m35() {
    return _fa ? _cc : *mParams.mSpeed_s;
}

void BattleCloseMeanderRun::m40() {
    playAS("Run", true, 0, 0, -1.0f);
}

}  // namespace uking::action
