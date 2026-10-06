#include "Game/AI/AI/aiAssassinBattle.h"
#include <algorithm>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AssassinBattle::AssassinBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AssassinBattle::~AssassinBattle() = default;

bool AssassinBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

bool AssassinBattle::sub_7100312994() {
    const f32 tired_dist = *mTiredDist_s;
    const f32 area = *mTerritoryArea_m;
    const f32 base = area > 0.0f ? area : tired_dist;
    const f32 limit = base - *mNearTiredOffset_s;
    if (limit <= 0.0f)
        return false;
    auto* actor = mActor;
    const f32 x = actor->getMtx().m[0][3];
    const f32 z = actor->getMtx().m[2][3];
    sead::Vector3f home;
    actor->getHomePos(&home);
    sead::Vector3f to_home = home;
    to_home.x -= x;
    to_home.y = 0;
    to_home.z -= z;
    const f32 home_dist = to_home.normalize();
    sead::Vector3f to_player = sub_71005D9330(actor);
    to_player.x -= x;
    to_player.y = 0;
    to_player.z -= z;
    to_player.normalize();
    return home_dist > limit && to_home.dot(to_player) > 0.0f;
}

// NON_MATCHING: distance loads and signed range selection are scheduled differently.
void AssassinBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    const sead::Vector3f delta = sub_71005D9330(actor) - actor->getMtx().getTranslation();
    _9c = !(delta.x * delta.x + delta.z * delta.z >
            *mFirstAttackResetDist_s * *mFirstAttackResetDist_s);
    const int tired_time = *mTiredTime_s;
    const int scaled_time = int(float(tired_time) * 1.2f);
    _94 = std::min(tired_time, scaled_time);
    _98 = std::max(tired_time, scaled_time);
    _90 = _94 == _98 ? float(_94) :
                       float(sead::GlobalRandom::instance()->getS32Range(_94, _98));

    actor = mActor;
    if (sub_710072F8E4(actor, sub_71005D9330(actor), nullptr, 3.0f)) {
        const float range = *mBattleBaseDist_s + *mBattleDistOutDist_s;
        actor = mActor;
        const sead::Vector3f battle_delta = sub_71005D9330(actor) - actor->getMtx().getTranslation();
        if (battle_delta.x * battle_delta.x + battle_delta.z * battle_delta.z < range * range) {
            changeChild("通常戦闘", nullptr);
            _9e = false;
            return;
        }
    }
    if (!(*mWarpDist_s <= 0.0f)) {
        actor = mActor;
        const sead::Vector3f warp_delta = sub_71005D9330(actor) - actor->getMtx().getTranslation();
        if (warp_delta.x * warp_delta.x + warp_delta.z * warp_delta.z >
            *mWarpDist_s * *mWarpDist_s) {
            {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("転移", &pack);
            }
            _9e = false;
            return;
        }
    }
    sub_71003118F0();
    _9e = false;
}

void AssassinBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinBattle::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mWarpDist_s, "WarpDist");
    getStaticParam(&mBattleBaseDist_s, "BattleBaseDist");
    getStaticParam(&mFirstAttackResetDist_s, "FirstAttackResetDist");
    getStaticParam(&mBattleDistOutDist_s, "BattleDistOutDist");
    getStaticParam(&mFirstAttackAngle_s, "FirstAttackAngle");
    getStaticParam(&mTiredDist_s, "TiredDist");
    getStaticParam(&mFirstAttackDist_s, "FirstAttackDist");
    getStaticParam(&mNearTiredOffset_s, "NearTiredOffset");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

// 0x71003118f0
void AssassinBattle::sub_71003118F0() {
    if (sub_710072F8E4(mActor, sub_71005D9330(mActor), nullptr, 3.0f)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("直進接近", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("直進不能接近", &pack);
    }
}

}  // namespace uking::ai
