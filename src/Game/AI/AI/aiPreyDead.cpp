#include "Game/AI/AI/aiPreyDead.h"
#include "Game/Actor/actRideable.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PreyDead::PreyDead(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyDead::~PreyDead() = default;

bool PreyDead::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyDead::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710072BB28(mActor);

    if (auto* controller = mActor->getCharacterController())
        controller->_a0.getTranslation(_9c);

    ksys::act::disableAllAttClients(mActor);

    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->Unk_7100e8b2b8::_8 = 0x200;

    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
    _90.reset(-1.0f, -1.0f);

    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "IsEnableThrowOffAttack", -1);
    changeChild("倒れ中", &pack);
}

void PreyDead::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F605C8(_9c);
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->Unk_7100e8b2b8::_8.setBitOff(9);
}

void PreyDead::loadParams_() {
    getStaticParam(&mSendRadius_s, "SendRadius");
    getStaticParam(&mIsEmitForceEscapeSignal_s, "IsEmitForceEscapeSignal");
}

bool PreyDead::isChangeable() const {
    return isCurrentChild("停止");
}

}  // namespace uking::ai
