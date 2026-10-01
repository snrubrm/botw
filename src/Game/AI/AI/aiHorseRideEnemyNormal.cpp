#include "Game/AI/AI/aiHorseRideEnemyNormal.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

HorseRideEnemyNormal::HorseRideEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

HorseRideEnemyNormal::~HorseRideEnemyNormal() = default;

bool HorseRideEnemyNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void HorseRideEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void HorseRideEnemyNormal::leave_() {
    EnemyNormal::leave_();
}

void HorseRideEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mSightAwarenessScale_s, "SightAwarenessScale");
}

void HorseRideEnemyNormal::calc_() {
    EnemyNormal::calc_();
    if (isCurrentChild("プレイヤー発見")) {
        const sead::Vector3f& target_pos = sub_71005D9330(mActor);
        getCurrentChild()->setDynamicParam(target_pos, "TargetPos");
    }
}

}  // namespace uking::ai
