#include "Game/AI/AI/aiTowingPlayer.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
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

void TowingPlayer::leave_() {
    if (auto* set = mActor->getPhysics()->findBodyByName("Atk")) {
        if (auto* body = set->getRigidBodies()[0])
            body->setContactLayer(ksys::phys::ContactLayer(0x35));
    }

    if (mActor->getRootAi()->getNewChildIdx() == 0)
        return;

    if (!_75)
        _d8.sub_710070DCC0(&ksys::act::PlayerInfo::getSomeProcLink(), true);
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
