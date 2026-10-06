#include "Game/AI/Action/actionGanonStunRecover.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

GanonStunRecover::GanonStunRecover(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonStunRecover::~GanonStunRecover() = default;

bool GanonStunRecover::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonStunRecover::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("Down_End", false, 0, 0, -1.0f);
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        boss->stunEnd();
        const auto* life = boss->getLife();
        if (!life || *life != 0)
            boss->_14e8.setBit(3);
        else
            setFinished();
    }
    _1c = false;
}

void GanonStunRecover::leave_() {
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        boss->stunEnd();
        boss->_14e8.resetBit(3);
    }
}

void GanonStunRecover::loadParams_() {}

void GanonStunRecover::calc_() {
    if (!mActor->getCharacterController()) {
        setFailed();
        return;
    }
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (!boss) {
        setFailed();
        return;
    }
    const auto* life = mActor->getLife();
    if (!life || *life != 0) {
        if (boss->_14e8.isOnBit(1)) {
            if (_1c)
                playAS("DownWaitMaterial", false, 1, 0, -1.0f);
            _1c = isFinishedAS(1, 0);
        }
        if (!isFinishedAS(0, 0))
            return;
        setRootAiFlag(ksys::act::ai::RootAiFlag(0));
        boss->_14f8._30.resetBit(4);
        boss->_14e8.resetBit(3);
        playAS("Wait_Battle_Material", false, 1, 0, -1.0f);
    }
    setFinished();
}

}  // namespace uking::action
