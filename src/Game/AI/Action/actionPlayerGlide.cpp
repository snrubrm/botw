#include "Game/AI/Action/actionPlayerGlide.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGlide::PlayerGlide(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGlide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGlide::leave_() {
    mActor->getChemicalStuff()->_14c = 1.0f;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F60458();
}

void PlayerGlide::loadParams_() {
    getStaticParam(&mGlideSpeedMax_s, "GlideSpeedMax");
    getStaticParam(&mLv2GlideSpeedMax_s, "Lv2GlideSpeedMax");
    getStaticParam(&mGlideBodyFrontX_s, "GlideBodyFrontX");
    getStaticParam(&mGlideBodyBackX_s, "GlideBodyBackX");
    getStaticParam(&mGlideBodySideZ_s, "GlideBodySideZ");
    getStaticParam(&mGlideRotMax_s, "GlideRotMax");
    getStaticParam(&mGlideRotMin_s, "GlideRotMin");
    getStaticParam(&mGlideRotRate_s, "GlideRotRate");
    getStaticParam(&mWindScale_s, "WindScale");
    getStaticParam(&mOverSpeedDec_s, "OverSpeedDec");
    getStaticParam(&mGlideRotSpeed_s, "GlideRotSpeed");
    getStaticParam(&mGlideNoSideAngle_s, "GlideNoSideAngle");
}

void PlayerGlide::calc_() {
    PlayerAction::calc_();
}

bool PlayerGlide::isChangeable() const {
    return true;
}

bool PlayerGlide::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround();
}

}  // namespace uking::action
