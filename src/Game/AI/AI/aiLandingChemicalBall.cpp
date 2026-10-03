#include "Game/AI/AI/aiLandingChemicalBall.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::ai {

bool LandingChemicalBall::sub_71004737B0() {
    ksys::act::InstParamPack pack;
    pack->add(*mIsUseAtCollision_s, "IsUseAtCollision");

    s32 attr;
    switch (*mAttackIntensity_s) {
    case 0:
        attr = 0;
        break;
    case 1:
        attr = 1;
        break;
    case 2:
        attr = 2;
        break;
    case 3:
        attr = 4;
        break;
    default:
        attr = 0;
        break;
    }
    pack->add(attr, "AttackAttr");

    s32 type;
    switch (*mAttackType_s) {
    case 0:
        type = 0x2000;
        break;
    case 1:
        type = 0x10;
        break;
    case 3:
        type = 0x800;
        break;
    default:
        type = 0x8000;
        break;
    }
    pack->add(type, "AttackType");

    pack->add(*mAttackPower_s, "AttackPower");
    pack->add(10.0f, "ScaleTime");
    pack->add(*mCutGrassType_s, "CutGrassType");

    auto* proc = ksys::act::ActorCreator::instance()->createActor(
        mExpandActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack,
        true, false);
    if (!proc)
        return false;
    auto* bullet = sead::DynamicCast<ksys::act::Bullet>(proc);
    if (!bullet) {
        proc->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        return false;
    }
    _80 = bullet;
    return true;
}

LandingChemicalBall::LandingChemicalBall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LandingChemicalBall::~LandingChemicalBall() {
    if (_80) {
        _80->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        _80 = nullptr;
    }
}

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
