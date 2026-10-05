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

}  // namespace uking::ai
