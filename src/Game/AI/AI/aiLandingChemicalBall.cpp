#include "Game/AI/AI/aiLandingChemicalBall.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::ai {

LandingChemicalBall::LandingChemicalBall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LandingChemicalBall::~LandingChemicalBall() = default;

bool LandingChemicalBall::init_(sead::Heap* heap) {
    if (!sub_71005D6D10() && !mExpandActorName_s.isEmpty() && !sub_71004737B0())
        return false;
    return true;
}

void LandingChemicalBall::calc_() {
    if (isCurrentChild("着弾前") && sub_7100473B2C()) {
        if (_80) {
            const f32 scale = *mScale_s;
            const sead::Vector3f scale_vec{scale, scale, scale};
            _80->setProperties(0, mActor->getMtx(), nullptr, nullptr, &scale_vec, false, 0, -1);
            _80 = nullptr;
        }
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool LandingChemicalBall::sub_7100473B2C() {
    if (isBgGroundHit(mActor, false))
        return true;
    if (isLandedMaybe(mActor, false))
        return true;
    if (mActor->get68f())
        return true;
    if (*mCheckColConInfo_s) {
        if (auto* body = mActor->getMainBody()) {
            if (auto* col = body->getCollisionInfo()) {
                if (col->getCollidingBodies().size() != 0)
                    return true;
            }
            if (auto* info = body->getContactPointInfo()) {
                if (info->getNumContactPoints() != 0 && !info->begin().isEnd())
                    return true;
            }
        }
    }
    return false;
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
