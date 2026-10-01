#include "Game/AI/AI/aiRemainsElectricRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

RemainsElectricRoot::RemainsElectricRoot(const InitArg& arg) : RemainsRoot(arg) {}

RemainsElectricRoot::~RemainsElectricRoot() = default;

bool RemainsElectricRoot::init_(sead::Heap* heap) {
    return RemainsRoot::init_(heap);
}

void RemainsElectricRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsRoot::enter_(params);
}

void RemainsElectricRoot::calc_() {
    RemainsRoot::calc_();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        m36();
    ksys::world::Manager::instance()->setCameraDistForRemainsElectric(
        mActor->getMtx().getTranslation());
}

void RemainsElectricRoot::leave_() {
    RemainsRoot::leave_();
}

void RemainsElectricRoot::loadParams_() {
    RemainsRoot::loadParams_();
}

void RemainsElectricRoot::m35(bool x) {
    RemainsRoot::m35(x);
}

}  // namespace uking::ai
