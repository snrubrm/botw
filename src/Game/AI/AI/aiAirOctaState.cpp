#include "Game/AI/AI/aiAirOctaState.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"

namespace uking::ai {

AirOctaState::AirOctaState(const InitArg& arg) : EnemyRoot(arg) {}

AirOctaState::~AirOctaState() = default;

bool AirOctaState::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void AirOctaState::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void AirOctaState::leave_() {
    sub_71002FDF9C();
    EnemyRoot::leave_();
}

void AirOctaState::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mRopeGravityFactor_s, "RopeGravityFactor");
    getStaticParam(&mBalloonMassRatio_s, "BalloonMassRatio");
    getStaticParam(&mWindForceScale_s, "WindForceScale");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

void AirOctaState::m37() {
    if (isCurrentChild("逃げる")) {
        auto* damage_manager = sub_710072BA90(mActor);
        if (damage_manager && damage_manager->getField54() == 20)
            return;
    }
    changeChild("リアクション");
}

void AirOctaState::m38() {
    sub_71002FD098(false);
}

void AirOctaState::m39() {}

}  // namespace uking::ai
