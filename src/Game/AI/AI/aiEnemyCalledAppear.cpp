#include "Game/AI/AI/aiEnemyCalledAppear.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyCalledAppear::EnemyCalledAppear(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyCalledAppear::~EnemyCalledAppear() = default;

bool EnemyCalledAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyCalledAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EBE0(1.5f);
        awareness->enable();
    }
    m34();
}

void EnemyCalledAppear::m34() {
    changeChild("出現");
}

void EnemyCalledAppear::leave_() {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EBE0(1.0f);
        awareness->disable();
    }
}

void EnemyCalledAppear::loadParams_() {}

bool EnemyCalledAppear::m35() {
    return false;
}

}  // namespace uking::ai
