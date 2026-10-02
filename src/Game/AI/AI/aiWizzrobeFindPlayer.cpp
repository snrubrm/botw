#include "Game/AI/AI/aiWizzrobeFindPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

WizzrobeFindPlayer::WizzrobeFindPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeFindPlayer::~WizzrobeFindPlayer() = default;

bool WizzrobeFindPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    *mIsWizzrobeInBattleAreaFlag_a = true;
    auto* actor = mActor;
    sub_71005D7444(actor, sub_71005D960C(actor), true, true);
    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000))
        wizzrobeFindPlayer();
    else
        sub_71005FDD14();
}

void WizzrobeFindPlayer::leave_() {
    auto* actor = mActor;
    actor->m93(0, 0);
    sub_71005DB3EC(actor);
    sub_71005D74E8(actor);
    *mIsWizzrobeInBattleAreaFlag_a = true;
}

void WizzrobeFindPlayer::loadParams_() {
    getStaticParam(&mHomeTerritoryWidth_s, "HomeTerritoryWidth");
    getStaticParam(&mHomeTerritoryHeight_s, "HomeTerritoryHeight");
    getStaticParam(&mBattleTerritoryWidth_s, "BattleTerritoryWidth");
    getAITreeVariable(&mIsWizzrobeInBattleAreaFlag_a, "IsWizzrobeInBattleAreaFlag");
}

void WizzrobeFindPlayer::calc_() {
    auto* actor = mActor;
    sub_71005DB068(actor, sub_71005D960C(actor));
    auto* child = getCurrentChild();
    *mIsWizzrobeInBattleAreaFlag_a = sub_71005FDF08();

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("気づき")) {
            wizzrobeFindPlayer();
        } else if (isCurrentChild("戦闘")) {
            if (child->isFinished())
                wizzrobeFindPlayer();
            else
                setFailed();
        }
    }
    wizzrobeFindPlayer_0();
}

void WizzrobeFindPlayer::wizzrobeFindPlayer() {
    auto* actor = mActor;
    actor->m93(0, 0);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(actor), "TargetPos", -1);
    changeChild("戦闘", &params);
}

void WizzrobeFindPlayer::sub_71005FDD14() {
    mActor->m93(4, 0);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("気づき", &params);
}

// NON_MATCHING: scheduling (the original squares the width before adding dx*dx + dz*dz in the first
// width check)
bool WizzrobeFindPlayer::sub_71005FDF08() {
    auto* actor = mActor;
    if (!sub_71005D8F28(actor))
        return false;

    const auto& target = sub_71005D9330(actor);
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    if (auto* mgr = ksys::map::AutoPlacementMgr::instance()) {
        if (mgr->isNonAutoPlacement(target, true))
            return false;
    }

    sead::Vector3f home;
    actor->getHomePos(&home);

    const f32 height = *mHomeTerritoryHeight_s;
    if (height > 0) {
        if (sead::Mathf::abs(home.y - pos.y) > height)
            return false;
        if (sead::Mathf::abs(home.y - target.y) > height)
            return false;
    }

    const f32 width = *mHomeTerritoryWidth_s;
    if (width > 0) {
        const f32 dx = home.x - target.x;
        const f32 dz = home.z - target.z;
        if (dx * dx + dz * dz > width * width)
            return false;
        const f32 dx2 = home.x - pos.x;
        const f32 dz2 = home.z - pos.z;
        if (dx2 * dx2 + dz2 * dz2 > width * width)
            return false;
    }

    const f32 battle_width = *mBattleTerritoryWidth_s;
    if (battle_width > 0) {
        const f32 dx = pos.x - target.x;
        const f32 dz = pos.z - target.z;
        if (dx * dx + dz * dz > battle_width * battle_width)
            return false;
    }

    return true;
}

void WizzrobeFindPlayer::wizzrobeFindPlayer_0() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (!child)
        return;

    if (isCurrentChild("戦闘")) {
        const sead::Vector3f pos = sub_71005D960C(actor);
        sub_71005DB068(actor, pos);
        child->setDynamicParam(sub_71005D9330(actor), "TargetPos");
    } else {
        const sead::Vector3f pos = sub_71005D98D8(actor);
        sub_71005DB068(actor, pos);
        child->setDynamicParam(pos, "TargetPos");
    }
}

}  // namespace uking::ai
