#include "Game/AI/Action/actionLynelRodeo.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

LynelRodeo::LynelRodeo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LynelRodeo::~LynelRodeo() = default;

bool LynelRodeo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LynelRodeo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
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

void LynelRodeo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
