#include "Game/AI/AI/aiBirdDead.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

BirdDead::BirdDead(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BirdDead::~BirdDead() = default;

bool BirdDead::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BirdDead::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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
