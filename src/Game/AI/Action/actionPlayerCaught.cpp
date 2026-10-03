#include "Game/AI/Action/actionPlayerCaught.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

PlayerCaught::PlayerCaught(const InitArg& arg) : PlayerAction(arg) {}

PlayerCaught::~PlayerCaught() = default;

void PlayerCaught::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCaught::leave_() {
    mActor->resetConnectedCalcParent(false);
    mActor->sub_71011DA834(&_20);
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FC012C(nullptr);
    static_cast<ksys::act::Player*>(mActor)->someFloatCalc(2.0f, sead::Vector3f(0.0f, 1.0f, 0.0f));
}

void PlayerCaught::calc_() {
    PlayerAction::calc_();
}

bool PlayerCaught::isChangeable() const {
    return false;
}

}  // namespace uking::action
