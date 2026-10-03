#include "Game/AI/AI/aiAssassinFieldShooterBattleBase.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

AssassinFieldShooterBattleBase::AssassinFieldShooterBattleBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinFieldShooterBattleBase::~AssassinFieldShooterBattleBase() = default;

bool AssassinFieldShooterBattleBase::init_(sead::Heap* heap) {
    const s32 tired_time = *mTiredTime_s;
    const s32 tired_time2 = tired_time * 1.2f;
    _74 = sead::Mathi::min(tired_time, tired_time2);
    _78 = sead::Mathi::max(tired_time, tired_time2);
    return true;
}

void AssassinFieldShooterBattleBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1) &&
        !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) && mActor) {
        const f32 intensity = *mIntervalIntensity_s;
        const s32 time = static_cast<act::Enemy*>(mActor)->_f28.sub_7100001AA4(intensity);
        if (time >= 0) {
            if (auto* enemy = static_cast<act::Enemy*>(mActor))
                enemy->_e68 = ksys::Timer(time, time);
        }
    }

    _70 = _74 == _78 ? _74 : sead::GlobalRandom::instance()->getS32Range(_74, _78);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("待機", &pack);
}

// NON_MATCHING: block layout (the original puts the `_70 <= 0` result block after the tail and
// returns through one epilogue at the end)
bool AssassinFieldShooterBattleBase::sub_7100322560() {
    bool result;
    if (_70 <= 0) {
        result = true;
    } else {
        auto* mgr = ksys::map::AutoPlacementMgr::instance();
        bool non_auto_placement = false;
        if (mgr) {
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            if (mgr->isNonAutoPlacement(pos, true))
                non_auto_placement = true;
            else if (mgr->isNonAutoPlacement(sub_71005D9330(mActor), true))
                non_auto_placement = true;
        }
        if (non_auto_placement) {
            result = true;
        } else if (*mTerritoryDist_s < 0) {
            result = false;
        } else {
            sead::Vector3f home;
            mActor->getHomePos(&home);
            const sead::Vector3f& target = sub_71005D9330(mActor);
            const f32 dx = target.x - home.x;
            const f32 dz = target.z - home.z;
            result = sead::Mathf::sqrt(dx * dx + dz * dz) > *mTerritoryDist_s;
        }
    }
    return result;
}

// NON_MATCHING: the original stores the weapon request type (_0 = 2) before its zero tail field
// (_40); everything else matches
void AssassinFieldShooterBattleBase::calc_() {
    auto* child = getCurrentChild();

    f32* delay = &_70;
    {
        sead::Vector3f from = sub_71005D9330(mActor);
        from.y += 0.1f;
        const sead::Vector3f down = -sead::Vector3f::ey;
        if (somePositionCalc(&from, from, down, *mTiredGrHeight_s + 0.1f))
            *delay = _74 == _78 ? _74 : sead::GlobalRandom::instance()->getS32Range(_74, _78);
        else
            ksys::Timer::update(delay, -1.0f);
    }

    auto* actor = mActor;
    if (!sub_71005D83C8(actor, *mWeaponIdx_s) && !sub_71005D8324(actor, *mWeaponIdx_s))
        sub_71005D787C(actor, *mWeaponIdx_s, act::Unk_71002eda38(2));

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("戦闘攻撃")) {
            if (mActor) {
                const s32 time = static_cast<act::Enemy*>(mActor)->_f28.sub_7100001AA4(
                    *mIntervalIntensity_s);
                if (time >= 0 && mActor)
                    static_cast<act::Enemy*>(mActor)->_e68 = ksys::Timer(time, time);
            }
            sub_71005D787C(actor, *mWeaponIdx_s, act::Unk_71002eda38(2));
        }
        if (sub_7100322560()) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("諦め", &params);
        } else {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("待機", &params);
        }
        return;
    }

    if (child->isChangeable()) {
        if (isCurrentChild("待機") && sub_7100322560()) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("諦め", &params);
            return;
        }
        if (!isCurrentChild("戦闘攻撃") && m34()) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("戦闘攻撃", &params);
            return;
        }
    }
    child->setDynamicParam(sub_71005D9330(actor), "TargetPos");
}

bool AssassinFieldShooterBattleBase::m34() {
    if (sub_710032276C())
        return true;
    return sub_71003228DC();
}

bool AssassinFieldShooterBattleBase::sub_710032276C() {
    auto* actor = mActor;
    const sead::Vector3f& target_pos = sub_71005D9330(actor);
    const f32 target_x = target_pos.x;
    const f32 target_z = target_pos.z;
    const f32 actor_x = actor->getMtx().m[0][3];
    const f32 actor_z = actor->getMtx().m[2][3];

    sead::Vector3f from = sub_71005D9330(mActor);
    from.y += 0.1f;
    const sead::Vector3f down = -sead::Vector3f::ey;
    if (!somePositionCalc(&from, from, down, *mTiredGrHeight_s + 0.1f))
        return false;

    const f32 dx = target_x - actor_x;
    const f32 dz = target_z - actor_z;
    const f32 dist_sq = dx * dx + dz * dz;
    if (dist_sq > *mWarpDistFar_s * *mWarpDistFar_s)
        return true;
    return dist_sq < *mWarpDistNear_s * *mWarpDistNear_s;
}

bool AssassinFieldShooterBattleBase::sub_71003228DC() {
    if (!sub_71005D8324(mActor, *mWeaponIdx_s))
        return false;
    auto* enemy = static_cast<act::Enemy*>(mActor);
    if (!enemy)
        return false;
    return enemy->_e68.value <= sead::Mathf::epsilon();
}

void AssassinFieldShooterBattleBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinFieldShooterBattleBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mWarpDistNear_s, "WarpDistNear");
    getStaticParam(&mWarpDistFar_s, "WarpDistFar");
    getStaticParam(&mTerritoryDist_s, "TerritoryDist");
    getStaticParam(&mTiredGrHeight_s, "TiredGrHeight");
    getStaticParam(&mIntervalIntensity_s, "IntervalIntensity");
}

}  // namespace uking::ai
