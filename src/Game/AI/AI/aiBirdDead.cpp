#include "Game/AI/AI/aiBirdDead.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::ai {

BirdDead::BirdDead(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BirdDead::~BirdDead() = default;

bool BirdDead::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BirdDead::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    _40 = controller->get110();
    if (controller->sub_7100F5F14C()) {
        controller->sub_7100F5F458(ksys::act::MotionType(0));
        changeChild("通常死亡", params);
        return;
    }

    if (int(controller->sub_7100F5F0E4()) != 1)
        controller->sub_7100F5F458(ksys::act::MotionType(1));
    controller->sub_7100F5EEB8(*mGravityScale_s);
    changeChild("空中死亡", params);
}

void BirdDead::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        setFinished();
    else
        child->isChangeable();
}

void BirdDead::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5EEB8(_40);
}

void BirdDead::loadParams_() {
    getStaticParam(&mGravityScale_s, "GravityScale");
}

}  // namespace uking::ai
