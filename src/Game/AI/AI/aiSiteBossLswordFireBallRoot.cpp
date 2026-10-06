#include "Game/AI/AI/aiSiteBossLswordFireBallRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

SiteBossLswordFireBallRoot::SiteBossLswordFireBallRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossLswordFireBallRoot::~SiteBossLswordFireBallRoot() = default;

bool SiteBossLswordFireBallRoot::init_(sead::Heap* heap) {
    if (auto* model = mActor->getModel())
        _e8.search(model, "Eyeball");
    else
        _e8.getKey().reset();
    return true;
}

void SiteBossLswordFireBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("準備");
    _d8 = *mTargetPos_d;
    _98 = false;

    s32 rate_a;
    s32 rate_b;
    switch (_9c) {
    case 0:
        rate_a = 43;
        rate_b = 43;
        break;
    case 1:
        rate_a = 13;
        rate_b = 43;
        break;
    default:
        rate_a = 43;
        rate_b = 13;
        break;
    }

    const u32 r = sead::GlobalRandom::instance()->getU32(100);
    if (r < rate_a)
        _9c = 1;
    else
        _9c = r < rate_a + rate_b ? 2 : 0;
    _a0 = 0;
    _a4 = 0;
}

void SiteBossLswordFireBallRoot::leave_() {
    if (_98 && !isActorGoingBackToRootAi())
        return;

    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss)
        return;

    for (s32 i = 0; i < 20; ++i)
        boss->_1560.sub_710066CC64(i);

    if (mThrowActorName_d.isEmpty())
        return;

    if (!boss->_1128.getActorPartsActor(mThrowActorName_d).hasProc())
        return;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&boss->_1128.getActorPartsActor(mThrowActorName_d), &accessor);
    if (accessor.isStateCalc())
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void SiteBossLswordFireBallRoot::loadParams_() {
    getStaticParam(&mPredictPosRate_s, "PredictPosRate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mYOffset_s, "YOffset");
    getStaticParam(&mIsThrowChildDevice_s, "IsThrowChildDevice");
    getStaticParam(&mIsNeedCreateChildDevice_s, "IsNeedCreateChildDevice");
    getStaticParam(&mBindPosOffset_s, "BindPosOffset");
    getDynamicParam(&mThrowActorName_d, "ThrowActorName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

// 0x710057c100
void SiteBossLswordFireBallRoot::sub_710057C100(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(*mIsThrowChildDevice_s, "IsThrowChildDevice", -1);
    pack.addVec3(pos, "TargetPos", -1);
    pack.addActor(*mTargetActor_d, "TargetActor", -1);
    pack.addString(mThrowActorName_d, "PartsName", -1);
    changeChild("投げる", &pack);
}

}  // namespace uking::ai
