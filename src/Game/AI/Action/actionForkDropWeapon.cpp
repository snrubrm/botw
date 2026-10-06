#include "Game/AI/Action/actionForkDropWeapon.h"
#include "Game/Actor/actUnk_7102376d50.h"
#include "Game/AI/Action/actionDropWeaponUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

ForkDropWeapon::ForkDropWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDropWeapon::~ForkDropWeapon() = default;

bool ForkDropWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkDropWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkDropWeapon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkDropWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mAngleOffsetY_s, "AngleOffsetY");
    getStaticParam(&mChemReset_s, "ChemReset");
}

void ForkDropWeapon::calc_() {
    ksys::act::ai::Action::calc_();
}

// NON_MATCHING: an extra callee-saved register holds the address of velocity.y (same as
// DropWeapon::sub_71000F8798).
void ForkDropWeapon::sub_710014CE28() {
    auto* actor = mActor;
    sead::Vector3f velocity;
    if (*mWeaponDropSpeedXZ_s <= sead::Mathf::epsilon() &&
        *mWeaponDropSpeedXZ_s >= -sead::Mathf::epsilon()) {
        velocity.x = 0.0f;
        velocity.z = 0.0f;
    } else {
        const auto& mtx = actor->getMtx();
        velocity.set(-mtx.m[0][2], 0.0f, -mtx.m[2][2]);
        setVectorLength(&velocity, *mWeaponDropSpeedXZ_s);
    }
    velocity.y = *mWeaponDropSpeedY_s;
    ksys::util::sub_71011EF010(&velocity, *mAngleOffsetY_s);
    uking::act::Unk_7102376d50 info;
    info.mFlags.change(2, *mChemReset_s);
    if (*mWeaponIdx_s >= 0)
        playerOrEnemyDropWeapon(actor, &velocity, *mWeaponIdx_s, true, false, &info, false);
    else
        sub_71005D8748(actor, velocity, true, false, &info, false);
}

}  // namespace uking::action
