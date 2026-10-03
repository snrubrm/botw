#include "Game/AI/Action/actionPlayerCaught.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

PlayerCaught::PlayerCaught(const InitArg& arg) : PlayerAction(arg) {}

PlayerCaught::~PlayerCaught() = default;

void PlayerCaught::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(26);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimWait", true, -1.0f);
    auto* actor = mActor;
    _20.x(sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent()));
    _20._28 = sub_71005DC5AC(actor).cstr();
    _20._30 = "Skl_Root";
    _20._38 = -1;
    _20._40 = sub_71005DC57C(actor);
    mActor->sub_71011DA824(&_20);
    mActor->x_22(sead::Vector3f::zero, sead::Vector3f::zero);
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FC01B0();
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
