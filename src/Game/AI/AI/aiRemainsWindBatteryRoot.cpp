#include "Game/AI/AI/aiRemainsWindBatteryRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

RemainsWindBatteryRoot::RemainsWindBatteryRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsWindBatteryRoot::~RemainsWindBatteryRoot() = default;

bool RemainsWindBatteryRoot::init_(sead::Heap* heap) {
    auto* actor = mActor;
    if (actor->getModel()) {
        _48.search(actor->getModel(), "Head");
        _80.search(actor->getModel(), "Neck");
    }
    return true;
}

void RemainsWindBatteryRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        if (actor->getConstraints().size() == 0)
            body->changeMotionType(ksys::phys::MotionType::Fixed);
    }
    if (auto* awareness = actor->getAwareness())
        awareness->enable();
    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, "MaterialDefault", 0, 1, true);
    changeChild("待機");
    _38 = 3;
    _40 = false;
    _3c = 0;
}

void RemainsWindBatteryRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWindBatteryRoot::loadParams_() {}

}  // namespace uking::ai
