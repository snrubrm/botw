#include "Game/AI/AI/aiLynelChaseBattleMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LynelChaseBattleMove::LynelChaseBattleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelChaseBattleMove::~LynelChaseBattleMove() = default;

bool LynelChaseBattleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelChaseBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = ksys::Timer(20.0f, 20.0f);
    const f32 x = mActor->getMtx()(0, 3);
    const f32 z = mActor->getMtx()(2, 3);
    const sead::Vector3f& target = sub_71005D9330(mActor);
    const f32 dx = x - target.x;
    const f32 dz = z - target.z;
    const f32 dist = sead::Mathf::sqrt(dx * dx + dz * dz);
    if (*mBaseDist_s + *mCloseStartDist_s < dist) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("近づき", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("追跡", &pack);
    }
}

void LynelChaseBattleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelChaseBattleMove::loadParams_() {
    getStaticParam(&mSlowDownDist_s, "SlowDownDist");
    getStaticParam(&mSpeedUpDist_s, "SpeedUpDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mCloseStartDist_s, "CloseStartDist");
}

}  // namespace uking::ai
