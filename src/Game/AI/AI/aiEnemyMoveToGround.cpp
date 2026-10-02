#include "Game/AI/AI/aiEnemyMoveToGround.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyMoveToGround::EnemyMoveToGround(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyMoveToGround::~EnemyMoveToGround() = default;

bool EnemyMoveToGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyMoveToGround::enter_(ksys::act::ai::InlineParamPack* params) {
    _58.mTimer.reset(*mRetryTime_s);
    _50 = 2;
    if (sub_710039A2B8()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_70, "TargetPos", -1);
        changeChild("発見", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("未発見", &pack);
    }
}

void EnemyMoveToGround::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyMoveToGround::loadParams_() {
    getStaticParam(&mRetryTime_s, "RetryTime");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mSearchRadius_s, "SearchRadius");
}

}  // namespace uking::ai
