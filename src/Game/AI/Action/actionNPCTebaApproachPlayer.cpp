#include "Game/AI/Action/actionNPCTebaApproachPlayer.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

NPCTebaApproachPlayer::NPCTebaApproachPlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTebaApproachPlayer::~NPCTebaApproachPlayer() = default;

bool NPCTebaApproachPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCTebaApproachPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* cc = mActor->getCharacterController();
    if (!cc) {
        setFailed();
        return;
    }

    cc->sub_7100F5F458(ksys::act::MotionType::Hover);
    _a0.x();
    _60.value = 0;
    _60.prev_value = 0;
    sub_710073FA90(&_78, mActor);
    _6c.set(-1, -1, -1);
    _5c = 0;
    playAS("Teba_BattleFly", true, 0, 0, -1.0f);
}

void NPCTebaApproachPlayer::leave_() {
    if (mActor->get1a0() ||
        (mActor->getMapObject() &&
         mActor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000)))
        _a0.x();
}

void NPCTebaApproachPlayer::loadParams_() {
    getStaticParam(&mParams.mUpdateTargetFrame_s, "UpdateTargetFrame");
    getStaticParam(&mParams.mPlayerMaxHeight_s, "PlayerMaxHeight");
    getStaticParam(&mParams.mMaxMoveSpeed_s, "MaxMoveSpeed");
    getStaticParam(&mParams.mTurnSpeed_s, "TurnSpeed");
    getStaticParam(&mParams.mTurnRadius_s, "TurnRadius");
    getStaticParam(&mParams.mReduceMaxSpeedChasePlayer_s, "ReduceMaxSpeedChasePlayer");
}

bool NPCTebaApproachPlayer::handleMessage_(const ksys::Message* message) {
    if (_a0._30)
        return false;
    return _a0.m2(*message);
}

void NPCTebaApproachPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
