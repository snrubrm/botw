#include "Game/Actor/AI/aiTowingPlayer.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/System/SeadController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

TowingPlayer::TowingPlayer(const InitArg& arg) : Towing(arg) {}

TowingPlayer::~TowingPlayer() = default;

bool TowingPlayer::init_(sead::Heap* heap) {
    return Towing::init_(heap);
}

void TowingPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    _75 = false;
    _158 = ksys::Timer(*mCheckPlayerStateDef_s, *mCheckPlayerStateDef_s);
    _164 = ksys::Timer(*mInterruptDef_s, *mInterruptDef_s);
    if (auto* set = mActor->getPhysics()->findBodyByName("Atk")) {
        if (auto* body = set->getRigidBodies()[0])
            body->setContactLayer(ksys::phys::ContactLayer(0x27));
    }
    if (auto* attention = mActor->getAttention())
        attention->disableAllClients();
    Towing::enter_(params);
}

// 0x71005cceec
// NON_MATCHING: stack slot of `side`; the original evaluates the stick dead-zone test with two csets and an and.
void TowingPlayer::calc_() {
    ksys::act::acc::PlayerBase player;
    ksys::act::acquireActor(&act::PlayerInfo::instance()->getPlayerLink(), &player);
    if (!player.hasProc()) {
        Towing::calc_();
        return;
    }

    auto* as_list = mActor->sub_71011C9A88();
    if (!as_list || as_list->sub_710115ED5C(0x42, 10)) {
        _164 = ksys::Timer(*mInterruptDef_s, *mInterruptDef_s);
    } else {
        _164.update();
        if (_164.value <= sead::Mathf::epsilon() && !_75) {
            _f0.sub_710070DCC0(&act::PlayerInfo::getSomeProcLink(), true);
            _75 = true;
        }
    }

    if (!(_158.value <= sead::Mathf::epsilon()))
        _158.update();
    if (_158.value <= sead::Mathf::epsilon() && !player.isRidingSandSeal() && !_75)
        _75 = true;

    if (_75) {
        _48.set(0.0f, 0.0f);
        Towing::calc_();
        return;
    }

    auto* controller = ksys::SeadController::getInstance();
    if (player.isRidingSandSeal())
        _48 = controller->getLeftStick();

    f32 distance = *mParams.mSandCheckLength_s;
    s32 side = 0;
    sub_71005CC5C0(&distance, &side);
    if (side == 1) {
        if ((_48.x <= 0.1f && _48.x >= -0.1f) || distance <= 5.0f)
            _48.x = 1.5f;
        if (distance <= 7.5f)
            _48.y = -1.0f;
    } else if (side == 2) {
        if ((_48.x <= 0.1f && _48.x >= -0.1f) || distance <= 5.0f)
            _48.x = -1.5f;
        if (distance <= 7.5f)
            _48.y = -1.0f;
    }

    if (distance < *mParams.mSandCheckLength_s) {
        _48.y = -1.0f;
        _38 = distance > 5.0f ? 4 : 5;
    } else if (controller->isTrig(1) && sub_71005CC384()) {
        _38 = 1;
    } else if (_48.y < -0.5f) {
        _38 = 4;
    } else if (_38 == 5) {
        _38 = 0;
    } else if (_38 == 4) {
        if (_3c > *mParams.mStandardSpeed_s)
            _38 = 3;
        else
            _38 = 0;
    }

    ksys::MessageType type{};
    if (sub_71005CC384()) {
        type = ksys::MessageType(0x8000027);
        ksys::act::ActorLinkConstDataAccess accessor;
        if (act::PlayerInfo::instance() &&
            ksys::act::acquireActor(&act::PlayerInfo::instance()->getPlayerLink(), &accessor)) {
            _108.sendMessage(*accessor.getMessageTransceiverId(), type, nullptr, true);
        }
    }
    sub_71005CD23C();
    Towing::calc_();
}

// 0x71005cd23c
void TowingPlayer::sub_71005CD23C() {
    ksys::act::acc::PlayerBase player;
    ksys::act::acquireActor(&act::PlayerInfo::instance()->getPlayerLink(), &player);
    if (player.hasProc() && !player.isRidingSandSeal())
        return;

    auto type = ksys::MessageType(mActor->getName().include("SP") ? 0x8800003 : 0x8800002);
    ksys::act::acc::Camera camera;
    sub_710092DAE8(&camera);
    if (!camera.hasProc())
        return;
    camera.setSunazarashiTurnParam(_44);
    _108.sendMessage(*camera.getMessageTransceiverId(), type, nullptr, true);
    if (_38 == 1 || sub_71005CC40C()) {
        type = ksys::MessageType(0x8800004);
        _108.sendMessage(*camera.getMessageTransceiverId(), type, nullptr, true);
    }
}

void TowingPlayer::leave_() {
    if (auto* set = mActor->getPhysics()->findBodyByName("Atk")) {
        if (auto* body = set->getRigidBodies()[0])
            body->setContactLayer(ksys::phys::ContactLayer(0x35));
    }

    if (mActor->getRootAi()->getNewChildIdx() == 0)
        return;

    if (!_75)
        _d8.sub_710070DCC0(&uking::act::PlayerInfo::getSomeProcLink(), true);
    if (auto* attention = mActor->getAttention()) {
        attention->enableAllClients();
        ksys::act::disableAttClient(mActor, "Hang");
    }
    Towing::leave_();
}

void TowingPlayer::loadParams_() {
    Towing::loadParams_();
    getStaticParam(&mInterruptDef_s, "InterruptDef");
    getStaticParam(&mCheckPlayerStateDef_s, "CheckPlayerStateDef");
}

void TowingPlayer::m38() {}

}  // namespace uking::ai
