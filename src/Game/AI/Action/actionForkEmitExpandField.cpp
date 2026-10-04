#include "Game/AI/Action/actionForkEmitExpandField.h"
#include <algorithm>
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

ForkEmitExpandField::ForkEmitExpandField(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkEmitExpandField::~ForkEmitExpandField() = default;

bool ForkEmitExpandField::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkEmitExpandField::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkEmitExpandField::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkEmitExpandField::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mCutGrassType_s, "CutGrassType");
    getStaticParam(&mAtTarget_s, "AtTarget");
    getStaticParam(&mScale_s, "Scale");
    getStaticParam(&mActorPowerScale_s, "ActorPowerScale");
    getStaticParam(&mIsUseAtCollision_s, "IsUseAtCollision");
    getStaticParam(&mPartsKey_s, "PartsKey");
    getStaticParam(&mXLinkKey_s, "XLinkKey");
    getStaticParam(&mAtDirType_s, "AtDirType");
}

void ForkEmitExpandField::calc_() {
    ksys::act::ai::Action::calc_();
}

ksys::act::BaseProcLink& ForkEmitExpandField::m32() {
    if (auto* parts = mActor->m101())
        return parts->getActorPartsActor(mPartsKey_s);
    return ksys::act::sUnk_71026505e0;
}

void ForkEmitExpandField::sub_710014E780(const sead::Matrix34f* mtx) {
    const f32 scale = *mScale_s;
    const sead::Vector3f scale_vec{scale, scale, scale};
    auto& link = m32();
    if (!link.hasProc())
        return;
    ksys::act::acc::Bullet bullet;
    ksys::act::acquireActor(&link, &bullet);
    bullet.setIsUseAtCollision(*mIsUseAtCollision_s, mActor);
    static const s32 sAttackAttr[4] = {0, 1, 2, 4};
    static const s32 sAttackType[4] = {0x2000, 0x10, 0x8000, 0x800};
    const s32 intensity = *mAttackIntensity_s;
    bullet.setAttackAttr(u32(intensity) <= 3 ? sAttackAttr[intensity] : 0, mActor);
    const s32 type = *mAttackType_s;
    bullet.setAttackType(u32(type) <= 3 ? sAttackType[type] : 0x8000, mActor);
    const s32 power = *mAttackPower_s;
    const f32 power_scale = *mActorPowerScale_s;
    bullet.setAttackPower(
        s32(power_scale * std::max(static_cast<ksys::act::PlayerOrEnemy*>(mActor)->getEnemyAtkPower(), 1)) + power,
        mActor);
    bullet.setCutGrassType(*mCutGrassType_s, mActor);
    bullet.setXLinkKey(mXLinkKey_s, mActor);
    bullet.setAttackTarget(*mAtTarget_s, mActor);
    bullet.setAttackDirType(sub_71007A3A8C(&mAtDirType_s), mActor);
    if (bullet.isStateSleep())
        bullet.setProperties(*mtx, nullptr, nullptr, &scale_vec, false, false, -1);
}

}  // namespace uking::action
