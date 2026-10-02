#include "Game/AI/AI/aiBeeSwarmNormal.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

BeeSwarmNormal::BeeSwarmNormal(const InitArg& arg) : EnemyNormal(arg) {}

BeeSwarmNormal::~BeeSwarmNormal() = default;

bool BeeSwarmNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void BeeSwarmNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void BeeSwarmNormal::leave_() {
    if (auto* awareness = mActor->getAwareness())
        awareness->enable();
    EnemyNormal::leave_();
}

void BeeSwarmNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

bool BeeSwarmNormal::handleMessage_(const ksys::Message& message) {
    const bool had_message = _3d8._30;
    if (_3d8.m2(message)) {
        _450 = _3d8._38._2c;
        if (!had_message)
            sub_71005D8DE8(mActor, _3d8._38._0, nullptr, nullptr);
        return true;
    }
    return EnemyNormal::handleMessage_(message);
}

}  // namespace uking::ai
