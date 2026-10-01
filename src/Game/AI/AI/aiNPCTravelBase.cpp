#include "Game/AI/AI/aiNPCTravelBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

NPCTravelBase::NPCTravelBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCTravelBase::~NPCTravelBase() = default;

bool NPCTravelBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCTravelBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = ksys::Timer(16, 16);
}

void NPCTravelBase::calc_() {
    if (_68.value <= sead::Mathf::epsilon())
        return;
    _68.update();
}

void NPCTravelBase::leave_() {
    if (_68.value <= sead::Mathf::epsilon())
        mActor->setFlag(ksys::act::Actor::ActorFlag::_34, false);
}

void NPCTravelBase::loadParams_() {}

}  // namespace uking::ai
