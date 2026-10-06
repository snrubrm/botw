#include "Game/AI/AI/aiEnemyNoiseTarget.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

void EnemyNoiseTarget::sub_710039B064() {
    _d8 = false;
    if (auto* holder = sub_71005E2BCC(mActor)) {
        holder->_8 = -1;
        holder->_c = 0;
    }
    _bc = _ac;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_ac, "TargetPos", -1);
    changeChild("到達不能", &pack);
}

bool EnemyNoiseTarget::sub_710039B164() {
    const s32 weapon_idx = *mNoShieldEquipWpIdx_s;
    if (weapon_idx >= 0 && sub_71005D83E8(mActor, weapon_idx))
        return false;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy || !enemy->_f54.isOnBit(4))
        return false;
    if (sub_71005DBB60(mActor, *mWeaponIdx_s))
        return false;
    return sub_71005DB96C(mActor) < 0;
}

bool EnemyNoiseTarget::sub_710039B240(ksys::act::BaseProcLink* out) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && !enemy->sub_7100016284(*mShieldIdx_s) && !enemy->sub_71000161A4(*mShieldIdx_s)) {
        auto& link = enemy->_c38[*mShieldIdx_s];
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (link.hasProcInCalcState() && !accessor.sub_7100D13448(-1)) {
            if (out)
                out->acquire(sead::DynamicCast<act::Weapon>(link.getProc(nullptr, nullptr)), false);
            return true;
        }
    }
    return false;
}

void EnemyNoiseTarget::sub_710039B400() {
    ksys::act::ai::InlineParamPack pack;
    pack.acquireActor(sead::DynamicCast<ksys::act::Actor>(_c8.getProc(nullptr, nullptr)),
                      "TargetWeapon", -1);
    changeChild("盾拾い", &pack);
}

EnemyNoiseTarget::EnemyNoiseTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNoiseTarget::~EnemyNoiseTarget() = default;

bool EnemyNoiseTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyNoiseTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyNoiseTarget::leave_() {
    if (auto* unit = sub_71005E2BCC(mActor)) {
        unit->_8 = -1;
        unit->_c = 0;
    }
}

void EnemyNoiseTarget::loadParams_() {
    getStaticParam(&mLostTime_s, "LostTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRerouteTimeMin_s, "RerouteTimeMin");
    getStaticParam(&mRerouteTimeMax_s, "RerouteTimeMax");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mShieldIdx_s, "ShieldIdx");
    getStaticParam(&mSearchShieldDist_s, "SearchShieldDist");
    getStaticParam(&mNoShieldSearchDist_s, "NoShieldSearchDist");
    getStaticParam(&mUnReachableToRepathDist_s, "UnReachableToRepathDist");
    getStaticParam(&mNoShieldEquipWpIdx_s, "NoShieldEquipWpIdx");
    getStaticParam(&mTooFarPathDist_s, "TooFarPathDist");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

}  // namespace uking::ai
