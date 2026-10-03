#include "Game/AI/Action/actionPlayerSuperJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"

namespace uking::action {

PlayerSuperJump::PlayerSuperJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSuperJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x1000);
    static_cast<ksys::act::Player*>(mActor)->_cfc.reset(0x1);
    static_cast<ksys::act::Player*>(mActor)->_1cbe = 0;
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ParaEquipOn", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);

    auto* proc = static_cast<ksys::act::Player*>(mActor)->_2c28.getProc(nullptr, nullptr);
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
        actor->wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
        sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x8000024), nullptr);
    }

    static_cast<ksys::act::Player*>(mActor)->_1800 = static_cast<ksys::act::Player*>(mActor)->_1770.y;
    auto* chemical = mActor->getChemicalStuff();
    chemical->_14c = *mWindScale_s;

    static_cast<ksys::act::Player*>(mActor)->_1cc8 -= 1;
    if (static_cast<ksys::act::Player*>(mActor)->_1cc8 < 1) {
        player = static_cast<ksys::act::Player*>(mActor);
        const f32 time = mActor->getParam()->getRes().mGParamList->getPlayer()->mWindSupportReuseTime.ref() * 30.0f;
        player->_1dfc = -1.0f;
        player->_1df4 = time;
        player->_1df8 = time;
        static_cast<ksys::act::Player*>(mActor)->_1cc8 =
            mActor->getParam()->getRes().mGParamList->getPlayer()->mSupportWindNum.ref();
    }
}

void PlayerSuperJump::leave_() {
    auto* proc = static_cast<ksys::act::Player*>(mActor)->_2c28.getProc(nullptr, nullptr);
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
        actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    mActor->getChemicalStuff()->_14c = 1.0f;
}

void PlayerSuperJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mWindScale_s, "WindScale");
}

void PlayerSuperJump::calc_() {
    if (mActor->getASList()->x_1(0, 0) == "ParaEquipOn") {
        if (mActor->getASList()->x_4(0, 0))
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ParashawlGlide", true,
                                                                               -1.0f);
    } else {
        if (mActor->getVelocity().y <= 0.01f)
            setFinished();
        if (*mJumpHeight_s < static_cast<ksys::act::Player*>(mActor)->_1770.y -
                                 static_cast<ksys::act::Player*>(mActor)->_1800)
            setFinished();
    }
}

bool PlayerSuperJump::isChangeable() const {
    return false;
}

}  // namespace uking::action
