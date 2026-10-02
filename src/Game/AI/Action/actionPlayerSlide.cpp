#include "Game/AI/Action/actionPlayerSlide.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/gameUnk_710246d058.h"

namespace uking::action {

PlayerSlide::PlayerSlide(const InitArg& arg) : PlayerAction(arg) {}

PlayerSlide::~PlayerSlide() = default;

void PlayerSlide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSlide::leave_() {
    PlayerAction::leave_();
}

bool PlayerSlide::isChangeable() const {
    if (_1c)
        return true;
    return static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(2);
}

void PlayerSlide::loadParams_() {
    getStaticParam(&mUpKeyInvalidTime_s, "UpKeyInvalidTime");
    getStaticParam(&mFrontSlideMaxSpeedF_s, "FrontSlideMaxSpeedF");
    getStaticParam(&mBackSlideMaxSpeedF_s, "BackSlideMaxSpeedF");
    getStaticParam(&mLimitAngleDegStart_s, "LimitAngleDegStart");
    getStaticParam(&mMaxSlipSpeed_s, "MaxSlipSpeed");
    getStaticParam(&mSlipSpeedAdd_s, "SlipSpeedAdd");
    getStaticParam(&mSlipSpeedDec_s, "SlipSpeedDec");
    getStaticParam(&mEffectContTime_s, "EffectContTime");
}

void PlayerSlide::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
