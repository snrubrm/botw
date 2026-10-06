#include "Game/AI/Action/actionPlayerMove.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"

namespace uking::action {

PlayerMove::PlayerMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerMove::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->_238 = 0;
        controller->sub_7100F5EEE0(*mActor->getParam()->getRes().mGParamList->getPlayer()->mMinForce);
    }
    static_cast<ksys::act::Player*>(mActor)->_c48.reset(0x100000);
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x100000);
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x80000000);
    static_cast<ksys::act::Player*>(mActor)->_2124 = 0.0f;
    static_cast<ksys::act::Player*>(mActor)->_212c = 0.0f;
    if (mActor->getASList()->x_1(1, 1) == "WaitUpper" || mActor->getASList()->x_1(1, 1) == "MoveUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    if (mActor->getASList()->x_1(1, 1) == "MoveUnsteadyUpper")
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    static_cast<ksys::act::Player*>(mActor)->sub_710086952C();
}

void PlayerMove::loadParams_() {
    getStaticParam(&mEnergyDash_s, "EnergyDash");
    getStaticParam(&mForceApplyPushAnm_s, "ForceApplyPushAnm");
    getStaticParam(&mEnergyDashTrig_s, "EnergyDashTrig");
    getStaticParam(&mPushContinueTime_s, "PushContinueTime");
    getStaticParam(&mPushStopDistY_s, "PushStopDistY");
    getStaticParam(&mInvalidFallFrame_s, "InvalidFallFrame");
}

void PlayerMove::calc_() {
    PlayerAction::calc_();
}

bool PlayerMove::isChangeable() const {
    return true;
}

}  // namespace uking::action
