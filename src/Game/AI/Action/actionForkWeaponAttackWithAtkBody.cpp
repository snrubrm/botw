#include "Game/AI/Action/actionForkWeaponAttackWithAtkBody.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkWeaponAttackWithAtkBody::ForkWeaponAttackWithAtkBody(const InitArg& arg)
    : ForkWeaponAttack(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkWeaponAttackWithAtkBody::~ForkWeaponAttackWithAtkBody() {
    ;
}

bool ForkWeaponAttackWithAtkBody::init_(sead::Heap* heap) {
    return ForkWeaponAttack::init_(heap);
}

void ForkWeaponAttackWithAtkBody::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkWeaponAttack::enter_(params);
}

void ForkWeaponAttackWithAtkBody::leave_() {
    ForkWeaponAttack::leave_();
}

void ForkWeaponAttackWithAtkBody::loadParams_() {
    ForkWeaponAttack::loadParams_();
    getStaticParam(&mAtkBodyName_s, "AtkBodyName");
}

void ForkWeaponAttackWithAtkBody::calc_() {
    ForkWeaponAttack::calc_();
}

// NON_MATCHING: existing byte flag interfaces use narrower temporary stores than the original caller.
void ForkWeaponAttackWithAtkBody::m32(int weapon_idx, const sead::SafeString& name, bool x, f32 y) {
    ForkWeaponAttackBase::m32(weapon_idx, name, x, y);
    auto* actor = mActor;
    auto* weapon = sub_71005D83E8(actor, m36());
    if (!weapon)
        return;
    auto* sensor = getActorAttackSensor(mActor);
    const u32 type = weapon->sub_71002ECB78();
    const u32 flags = sub_7100146FA0();
    const u32 attributes = weapon->getFlags(flags);
    const s32 power = weapon->getEffectiveAttackPower(mActor);
    const sead::BitFlag8 impulse_flags(4);
    const s32 impulse = weapon->sub_71002ECAFC(impulse_flags);
    const sead::BitFlag8 guard_flags(4);
    const s32 guard = weapon->sub_71002ECB3C(guard_flags);
    sensor->activateAttackSensor(type, attributes, power, impulse, 0.0f, guard, 1,
                                sub_71007A3A8C(&name), false, 1, -1);
    sub_71007A2C30(mActor, mAtkBodyName_s, nullptr);
}

void ForkWeaponAttackWithAtkBody::m33() {
    ForkWeaponAttack::m33();
    sub_71007A2D7C(mActor, mAtkBodyName_s);
}

}  // namespace uking::action
