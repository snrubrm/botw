#include "Game/Actor/Action/actionWindCutter.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

WindCutter::WindCutter(const InitArg& arg) : EmitAttackBase(arg) {}

WindCutter::~WindCutter() = default;

bool WindCutter::init_(sead::Heap* heap) {
    return EmitAttackBase::init_(heap);
}

// NON_MATCHING: operand order of two commutative fmuls (level * ScaleMult and scale.z * mult).
void WindCutter::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool is_level_one_scale_one = *mIsLevelOneScaleOne_s;
    const int level = *mAttackLevel_m;
    auto* actor = mActor;
    if (!is_level_one_scale_one || level >= 2) {
        const f32 mult = f32(*mLevelBaseScaleAdd_s) + f32(level > 0 ? level : 0) * *mLevelScaleMult_s;
        sead::Vector3f scale = actor->getScale();
        scale *= mult;
        actor->setScale(scale);
    }
    EmitAttackBase::enter_(params);
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor))
        bullet->_cf4 |= 1;
    _c0 = true;
}

void WindCutter::leave_() {
    EmitAttackBase::leave_();
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor))
        bullet->_cf4 &= ~1;
}

void WindCutter::loadParams_() {
    EmitAttackBase::loadParams_();
    getStaticParam(&mLevelAtkMult_s, "LevelAtkMult");
    getStaticParam(&mLevelBaseScaleAdd_s, "LevelBaseScaleAdd");
    getStaticParam(&mLevelRangeMult_s, "LevelRangeMult");
    getStaticParam(&mLevelScaleMult_s, "LevelScaleMult");
    getStaticParam(&mIsLevelOneScaleOne_s, "IsLevelOneScaleOne");
    getMapUnitParam(&mAttackLevel_m, "AttackLevel");
    getMapUnitParam(&mAttackDirType_m, "AttackDirType");
    getAITreeVariable(&mAttackAttrEventKill_a, "AttackAttrEventKill");
}

// NON_MATCHING: vector projection temporaries and half-size arithmetic use different registers and scheduling.
void WindCutter::calc_() {
    EmitAttackBase::calc_();
    if (_c0) {
        _c0 = false;
        return;
    }
    auto* terrain = ksys::tera::Terrain::instance();
    if (!terrain || !terrain->isGrassEnabled())
        return;
    auto* actor = mActor;
    sead::Vector3f position;
    actor->getMtx().getTranslation(position);
    f32 radius = _7c;
    if (auto* body = sub_71001055A4()) {
        sead::BoundBox3f bounds;
        body->getAabbInLocal(&bounds);
        sead::Vector3f half_size = (bounds.getMax() - bounds.getMin()) * 0.5f;
        const sead::Matrix33f rotation(actor->getMtx());
        half_size.x = half_size.dot(rotation.getRow(0));
        const f32 height = sead::Mathf::abs(rotation.getRow(1).dot(half_size));
        position.y += height;
        const f32 distance = height + height + 1.0f;
        if (!somePositionCalc(&position, position, -sead::Vector3f::ey, distance))
            position.y -= distance;
        radius = half_size.x + 3.0f;
    } else {
        radius *= 0.5f;
    }
    terrain->sub_710114DE4C()->sub_7101151064(&position, radius, 8.0f, true, true, true);
    terrain->sub_710114DE4C()->sub_7101150A7C(&position, radius + 1.0f, 0.0f);
}

int WindCutter::m39() {
    if (sead::DynamicCast<ksys::act::Bullet>(mActor))
        return *mAttackDirType_m;
    return EmitAttackBase::m39();
}

int WindCutter::m35() {
    return 1;
}

f32 WindCutter::m34() {
    return EmitAttackBase::m34() * sead::Mathi::max(*mAttackLevel_m, 0) * *mLevelRangeMult_s;
}

int WindCutter::m36() {
    int result = EmitAttackBase::m36();
    if (*mAttackAttrEventKill_a)
        result |= 0x40000000;
    return result;
}

int WindCutter::m37() {
    return *mAttackPower_m * sead::Mathi::max(*mAttackLevel_m, 0) * *mLevelAtkMult_s;
}

bool WindCutter::m33() {
    if (EmitAttackBase::m33())
        return true;
    auto* actor = mActor;
    return isLandedMaybe(actor, false) || isBgGroundHit(actor, false) ||
           sub_71007A4178(actor, false);
}

}  // namespace uking::action
