#include "Game/AI/AI/aiHorseRideEnemyNormal.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HorseRideEnemyNormal::HorseRideEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

HorseRideEnemyNormal::~HorseRideEnemyNormal() = default;

bool HorseRideEnemyNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void HorseRideEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
    _3b0 = mTerritoryArea_s;
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EC14(0, *mSightAwarenessScale_s);
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

void HorseRideEnemyNormal::m41() {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EBE0(1.0f);
        awareness->sub_7100D7EC14(0, *mSightAwarenessScale_s);
    }
}

void HorseRideEnemyNormal::m42() {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EBE0(*mEnlargeAwnRatio_s);
        awareness->sub_7100D7EC14(0, sead::Mathf::max(*mEnlargeAwnRatio_s, *mSightAwarenessScale_s));
    }
}

}  // namespace uking::ai
