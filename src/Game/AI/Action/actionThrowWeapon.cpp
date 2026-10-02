#include "Game/AI/Action/actionThrowWeapon.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

ThrowWeapon::ThrowWeapon(const InitArg& arg) : ActionWithAS(arg) {}

ThrowWeapon::~ThrowWeapon() = default;

void ThrowWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void ThrowWeapon::leave_() {
    ActionWithAS::leave_();
}

void ThrowWeapon::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeedMin_s, "SpeedMin");
    getStaticParam(&mSpeedMax_s, "SpeedMax");
    getStaticParam(&mThrowAng_s, "ThrowAng");
    getStaticParam(&mThrowBoomerangAng_s, "ThrowBoomerangAng");
    getStaticParam(&mThrowBoomerangSpeedMax_s, "ThrowBoomerangSpeedMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsForceDead_s, "IsForceDead");
}

void ThrowWeapon::calc_() {
    ActionWithAS::calc_();
}

void ThrowWeapon::m32(sead::Vector3f* pos, uking::act::Enemy* enemy, int weapon_idx) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&enemy->_c38[weapon_idx], &accessor);
    accessor.getActorMtx().getTranslation(*pos);
}

void ThrowWeapon::m33() {
    playAS("Throw", false, 0, 0, -1.0f);
}

}  // namespace uking::action
