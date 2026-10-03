#include "Game/AI/Action/actionPlayerGlide.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGlide::PlayerGlide(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGlide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(15);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(25);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(1);
    auto* chemical = mActor->getChemicalStuff();
    chemical->_14c = *mWindScale_s;
    sead::Vector3f dir{mActor->getVelocity().x, 0.0f, mActor->getVelocity().z};
    dir.normalize();
    static_cast<ksys::act::Player*>(mActor)->_181c.x = dir.x * static_cast<ksys::act::Player*>(mActor)->_20bc.value;
    static_cast<ksys::act::Player*>(mActor)->_181c.z = dir.z * static_cast<ksys::act::Player*>(mActor)->_20bc.value;
    static_cast<ksys::act::Player*>(mActor)->_1804 = 0;
    static_cast<ksys::act::Player*>(mActor)->_1808 = 0;
    static_cast<ksys::act::Player*>(mActor)->_20c8 = *mLv2GlideSpeedMax_s;
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
