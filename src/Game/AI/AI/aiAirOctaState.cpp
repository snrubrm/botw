#include "Game/AI/AI/aiAirOctaState.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AirOctaState::AirOctaState(const InitArg& arg) : EnemyRoot(arg) {}

AirOctaState::~AirOctaState() {
    if (_218.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_218, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool AirOctaState::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap))
        return false;
    sub_710073FA90(&_238, mActor);
    return true;
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

void AirOctaState::sub_71002FD098(bool a1) {
    if (isCurrentChild("逃げる"))
        return;
    if (isCurrentChild("滝死亡"))
        return;

    mActor->m93(0, 0.0f);
    ksys::act::ai::InlineParamPack params;
    mActor->getASList()->x_2(66, 40, _278.isOnBit(3), false);
    params.addBool(a1, "IsSameChange", -1);
    changeChild("待機", &params);
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
