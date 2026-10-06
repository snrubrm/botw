#include "Game/AI/Action/actionDropWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadVector.h>
#include "Game/Actor/actUnk_7102376d50.h"
#include "Game/AI/Action/actionDropWeaponUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

DropWeapon::DropWeapon(const InitArg& arg) : OnetimeStopASPlay(arg) {}

DropWeapon::~DropWeapon() = default;

bool DropWeapon::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void DropWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void DropWeapon::leave_() {
    OnetimeStopASPlay::leave_();
}

void DropWeapon::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mAngleOffsetY_s, "AngleOffsetY");
    getStaticParam(&mChemReset_s, "ChemReset");
}

void DropWeapon::calc_() {
    OnetimeStopASPlay::calc_();
    if (sub_71005DD780(mActor, 70, nullptr, 0, 0))
        sub_71000F8798();
}

// NON_MATCHING: an extra callee-saved register holds the address of velocity.y (the address is
// computed in both predecessors of the join); the original stores to [sp, #0x14] directly.
void DropWeapon::sub_71000F8798() {
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
    playerOrEnemyDropWeapon(actor, &velocity, *mWeaponIdx_s, true, false, &info, false);
}

}  // namespace uking::action
