#include "Game/AI/AI/aiPlayerCaught.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PlayerCaught::PlayerCaught(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerCaught::isChangeable() const {
    return false;
}

bool PlayerCaught::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerCaught::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    auto* actor = mActor;
    sub_7100738C88(actor, sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent()));
    if (hasPendingChildChange())
        changeChild(mPendingChildIdx);
    else
        changeChild("掴まれる");
}

void PlayerCaught::leave_() {
    ksys::act::ai::Ai::leave_();
}

}  // namespace uking::ai
