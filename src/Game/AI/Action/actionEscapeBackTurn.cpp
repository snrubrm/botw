#include "Game/AI/Action/actionEscapeBackTurn.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

EscapeBackTurn::EscapeBackTurn(const InitArg& arg) : ActionEx(arg) {}

EscapeBackTurn::~EscapeBackTurn() = default;

void EscapeBackTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("BackTurn", false, 0, 0, -1.0f);
    _80 = 0;
    sub_7100113950();
}

void EscapeBackTurn::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
}

void EscapeBackTurn::loadParams_() {}

void EscapeBackTurn::calc_() {
    ActionEx::calc_();
}

bool EscapeBackTurn::isChangeable() const {
    return false;
}

}  // namespace uking::action
