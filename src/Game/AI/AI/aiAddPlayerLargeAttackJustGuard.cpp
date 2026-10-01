#include "Game/AI/AI/aiAddPlayerLargeAttackJustGuard.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AddPlayerLargeAttackJustGuard::AddPlayerLargeAttackJustGuard(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

bool AddPlayerLargeAttackJustGuard::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool AddPlayerLargeAttackJustGuard::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool AddPlayerLargeAttackJustGuard::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool AddPlayerLargeAttackJustGuard::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddPlayerLargeAttackJustGuard::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("行動");
}

void AddPlayerLargeAttackJustGuard::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10000000);
}

void AddPlayerLargeAttackJustGuard::loadParams_() {}

}  // namespace uking::ai
