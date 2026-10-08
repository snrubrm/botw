#include "Game/AI/Action/actionLynelRodeo.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

LynelRodeo::LynelRodeo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LynelRodeo::~LynelRodeo() = default;

bool LynelRodeo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LynelRodeo::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    mFlags.set(Flag::Changeable);
    auto* rideable = actor->getHorseOptionsMaybe();
    if (!rideable) {
        setFailed();
        return;
    }
    rideable->_18.sub_7100E787A0();
    actor->getASList()->x_6(1, 0, 0.0f);
    rideable->_18.sub_7100E786F0(act::sUnk_71026031d0);
}

void LynelRodeo::leave_() {
    auto* actor = mActor;
    if (auto* rideable = actor->getHorseOptionsMaybe())
        rideable->_18.sub_7100E770C4(false);
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F5EDE0(0.0f);
        controller->sub_7100F5EDD8(1.0f);
    }
}

void LynelRodeo::loadParams_() {
    getStaticParam(&mForwardSpeed_s, "ForwardSpeed");
    getStaticParam(&mSideSpeed_s, "SideSpeed");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mTurnCheckAngleStep_s, "TurnCheckAngleStep");
}

// NON_MATCHING: the original tail-calls setFinished / setFailed from single blocks; ours emits `bl` + shared epilogue for them.
void LynelRodeo::calc_() {
    auto* actor = mActor;
    auto* rideable = actor->getHorseOptionsMaybe();
    if (!rideable) {
        setFailed();
        return;
    }
    const act::Unk_7100e8b2b8::Unk8 state(rideable->act::Unk_7100e8b2b8::_8.load() & 0xff);
    if (int(state) == 0) {
        setFailed();
        return;
    }
    auto* as_list = actor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }
    auto* controller = actor->getCharacterController();
    if (!controller)
        return;
    act::sub_7100E7F698(rideable, as_list, controller);
    if (rideable->_279 < 0)
        setFinished();
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
