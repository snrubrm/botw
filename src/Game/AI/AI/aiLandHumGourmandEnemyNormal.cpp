#include "Game/AI/AI/aiLandHumGourmandEnemyNormal.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actUnk_71002dccbc.h"

namespace uking::ai {

LandHumGourmandEnemyNormal::LandHumGourmandEnemyNormal(const InitArg& arg)
    : LandHumEnemyNormal(arg) {}

LandHumGourmandEnemyNormal::~LandHumGourmandEnemyNormal() = default;

bool LandHumGourmandEnemyNormal::init_(sead::Heap* heap) {
    if (!sead::IsDerivedFrom<act::Enemy>(mActor))
        return false;
    *static_cast<Unk_7102370e70**>(mTargetBaitActorLink_a) = &_440;
    return LandHumEnemyNormal::init_(heap);
}

void LandHumGourmandEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyNormal::enter_(params);
    sub_7100472538();
    _418 = ksys::Timer(0, 0);
}

void LandHumGourmandEnemyNormal::calc_() {
    LandHumEnemyNormal::calc_();
}

void LandHumGourmandEnemyNormal::leave_() {
    LandHumEnemyNormal::leave_();
}

void LandHumGourmandEnemyNormal::loadParams_() {
    LandHumEnemyNormal::loadParams_();
    getStaticParam(&mRefindBaitTime_s, "RefindBaitTime");
    getStaticParam(&mEatArea_s, "EatArea");
    getStaticParam(&mEatNavType_s, "EatNavType");
    getAITreeVariable(&mTargetBaitActorLink_a, "TargetBaitActorLink");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

void LandHumGourmandEnemyNormal::m35() {
    if (*mIsTrgChangeUnderWaterState_a) {
        m36();
        return;
    }
    EnemyNormal::m35();
}

s32 LandHumGourmandEnemyNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 1, 11, 2, 3, 9, 4, 5, 6, 7, 8, 10};
    return sTable[idx];
}

void LandHumGourmandEnemyNormal::sub_7100472538() {
    auto* link =
        sead::DynamicCast<Unk_7102370e70>(*static_cast<Unk_71025afb58**>(mTargetBaitActorLink_a));
    if (!link)
        return;
    auto& bait = link->mLink;
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DC8A0(bait, 0x10);
    bait.reset();
}

}  // namespace uking::ai
