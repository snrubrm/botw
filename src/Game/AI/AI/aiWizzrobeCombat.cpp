#include "Game/AI/AI/aiWizzrobeCombat.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

WizzrobeCombat::WizzrobeCombat(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeCombat::~WizzrobeCombat() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (mSummonBufferSize_s) {
            sead::FixedSafeString<64> name;
            for (s32 i = 0; i < *mSummonBufferSize_s; ++i) {
                name.format("%s_%d", mSummonBufferKey_s.cstr(), i);
                enemy->sub_7100D3CFEC(name);
            }
        }
    }
}

bool WizzrobeCombat::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeCombat::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WizzrobeCombat::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WizzrobeCombat::loadParams_() {
    getStaticParam(&mWeatherMagicRate_s, "WeatherMagicRate");
    getStaticParam(&mSummonRate_s, "SummonRate");
    getStaticParam(&mSummonBufferSize_s, "SummonBufferSize");
    getStaticParam(&mMaxHeightLevel_s, "MaxHeightLevel");
    getStaticParam(&mSummonCount_s, "SummonCount");
    getStaticParam(&mAttackLength_s, "AttackLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getStaticParam(&mSummonBufferKey_s, "SummonBufferKey");
    getStaticParam(&mTargetOffset_s, "TargetOffset");
    getAITreeVariable(&mSummonCount_a, "SummonCount");
    getAITreeVariable(&mIsWizzrobeInBattleAreaFlag_a, "IsWizzrobeInBattleAreaFlag");
}

bool WizzrobeCombat::isChangeable() const {
    if (ksys::act::ai::Ai::isChangeable())
        return true;
    auto* child = getCurrentChild();
    if (child->isFinished())
        return true;
    return child->isFailed();
}

}  // namespace uking::ai
