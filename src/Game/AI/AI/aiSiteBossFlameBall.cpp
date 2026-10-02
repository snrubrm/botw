#include "Game/AI/AI/aiSiteBossFlameBall.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

SiteBossFlameBall::SiteBossFlameBall(const InitArg& arg) : SiteBossChemicalProjectile(arg) {}

SiteBossFlameBall::~SiteBossFlameBall() = default;

bool SiteBossFlameBall::init_(sead::Heap* heap) {
    return SiteBossChemicalProjectile::init_(heap);
}

void SiteBossFlameBall::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossChemicalProjectile::enter_(params);
}

void SiteBossFlameBall::leave_() {
    SiteBossChemicalProjectile::leave_();
}

void SiteBossFlameBall::loadParams_() {
    SiteBossChemicalProjectile::loadParams_();
    getStaticParam(&mChemicalIndex_s, "ChemicalIndex");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveOffset_s, "MoveOffset");
    getStaticParam(&mCountOffset_s, "CountOffset");
    getStaticParam(&mIsInfluence_s, "IsInfluence");
    getMapUnitParam(&mCount_m, "Count");
    getMapUnitParam(&mPosOffset_m, "PosOffset");
}

sead::Vector3f SiteBossFlameBall::m35() {
    return *mPosOffset_m;
}

bool SiteBossFlameBall::m40() {
    if (_1c9)
        return false;
    auto* chemical = mActor->sub_71011D8A44(*mChemicalIndex_s);
    if (chemical && chemical->_b9[0] & 2)
        return true;
    return _d9;
}

bool SiteBossFlameBall::m41() {
    if (!_1c8 && sub_71007A2604(mActor))
        _1c8 = true;
    else if (_1c8)
        return true;
    return false;
}

u32 SiteBossFlameBall::m51() {
    return *mAtAttr_s;
}

}  // namespace uking::ai
