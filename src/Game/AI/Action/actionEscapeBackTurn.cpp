#include "Game/AI/Action/actionEscapeBackTurn.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"
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

void EscapeBackTurn::sub_7100113950() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    const sead::Vector3f up = getUpDir(controller->get70());
    sead::Vector3f velocity;
    velocity.set(mActor->getVelocity());
    ksys::util::sub_71011EFA00(&velocity, velocity, up);
    const f32 length = velocity.normalize();
    _1c.value = length;
    _1c.prev_value = length;
    sub_710072C1B4(controller, velocity);
}

}  // namespace uking::action
