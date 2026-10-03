#include "Game/AI/AI/aiAssassinFieldShooterBattleBase.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

AssassinFieldShooterBattleBase::AssassinFieldShooterBattleBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinFieldShooterBattleBase::~AssassinFieldShooterBattleBase() = default;

bool AssassinFieldShooterBattleBase::init_(sead::Heap* heap) {
    const s32 tired_time = *mTiredTime_s;
    const s32 tired_time2 = tired_time * 1.2f;
    _74 = sead::Mathi::min(tired_time, tired_time2);
    _78 = sead::Mathi::max(tired_time, tired_time2);
    return true;
}

void AssassinFieldShooterBattleBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1) &&
        !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) && mActor) {
        const f32 intensity = *mIntervalIntensity_s;
        const s32 time = static_cast<act::Enemy*>(mActor)->_f28.sub_7100001AA4(intensity);
        if (time >= 0) {
            if (auto* enemy = static_cast<act::Enemy*>(mActor))
                enemy->_e68 = ksys::Timer(time, time);
        }
    }

    _70 = _74 == _78 ? _74 : sead::GlobalRandom::instance()->getS32Range(_74, _78);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("待機", &pack);
}

void AssassinFieldShooterBattleBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinFieldShooterBattleBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mWarpDistNear_s, "WarpDistNear");
    getStaticParam(&mWarpDistFar_s, "WarpDistFar");
    getStaticParam(&mTerritoryDist_s, "TerritoryDist");
    getStaticParam(&mTiredGrHeight_s, "TiredGrHeight");
    getStaticParam(&mIntervalIntensity_s, "IntervalIntensity");
}

}  // namespace uking::ai
