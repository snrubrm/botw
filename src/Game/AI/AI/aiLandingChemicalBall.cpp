#include "Game/AI/AI/aiLandingChemicalBall.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

LandingChemicalBall::LandingChemicalBall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LandingChemicalBall::~LandingChemicalBall() = default;

bool LandingChemicalBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LandingChemicalBall::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* chemical = mActor->sub_71011D8A44(0))
        chemical->sub_7100D91098(true);
    changeChild("着弾前");
}

void LandingChemicalBall::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LandingChemicalBall::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mCutGrassType_s, "CutGrassType");
    getStaticParam(&mScale_s, "Scale");
    getStaticParam(&mIsUseAtCollision_s, "IsUseAtCollision");
    getStaticParam(&mCheckColConInfo_s, "CheckColConInfo");
    getStaticParam(&mExpandActorName_s, "ExpandActorName");
}

}  // namespace uking::ai
