#include "Game/Actor/Action/actionForkNoWeaponAttackParamWeapon.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_71005D6D10.h"

namespace uking::action {

ForkNoWeaponAttackParamWeapon::ForkNoWeaponAttackParamWeapon(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkNoWeaponAttackParamWeapon::~ForkNoWeaponAttackParamWeapon() = default;

bool ForkNoWeaponAttackParamWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkNoWeaponAttackParamWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkNoWeaponAttackParamWeapon::leave_() {
    sub_71007A2D34(
        mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtkBodyName_s.cstr()));
}

void ForkNoWeaponAttackParamWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mAtkBodyName_s, "AtkBodyName");
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
}

void ForkNoWeaponAttackParamWeapon::calc_() {
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, *mTargetBone_s, *mSeqBank_s)) {
        auto* weapon = sub_71005D83E8(mActor, *mWeaponIdx_s);
        if (!weapon)
            return;
        u32 flags = 0;
        const s32 intensity = *mAttackIntensity_s;
        if (intensity == 3)
            flags = 4;
        else if (intensity == 2)
            flags = 2;
        else if (intensity == 1)
            flags = 1;
        auto* sensor = getActorAttackSensor(mActor);
        const u32 type = weapon->sub_71002ECB78();
        const u32 attributes = weapon->getFlags(flags);
        const s32 power = weapon->getEffectiveAttackPower(mActor);
        const s32 impulse = weapon->sub_71002ECAFC(flags);
        const s32 guard = weapon->sub_71002ECB3C(flags);
        sensor->activateAttackSensor(type, attributes, power, impulse, 0.0f, guard, 1,
                                     sub_71007A3A8C(&query.name), false, 1, -1);
        auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtkBodyName_s.cstr());
        sub_71007A2B64(body, nullptr);
    } else if (sub_71005DD74C(mActor, nullptr, *mTargetBone_s, *mSeqBank_s)) {
        auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtkBodyName_s.cstr());
        sub_71007A2D34(body);
    }
}

}  // namespace uking::action
