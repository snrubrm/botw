#include "Game/Actor/AI/aiNPCChasePlayerBlueFire.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/AutoPlacement/AutoPlacementMgr.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

NPCChasePlayerBlueFire::NPCChasePlayerBlueFire(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCChasePlayerBlueFire::~NPCChasePlayerBlueFire() = default;

bool NPCChasePlayerBlueFire::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCChasePlayerBlueFire::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "IsPathRest", -1);
    changeChild("Wander", &pack);
}

void NPCChasePlayerBlueFire::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCChasePlayerBlueFire::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mLeaveDist_s, "LeaveDist");
    getStaticParam(&mLostDist_s, "LostDist");
}

// NON_MATCHING: the original builds the translation copy in a vector register (ld1 lane + 8/4-byte
// stores) and keeps &pack in a different register
void NPCChasePlayerBlueFire::sub_71004C34AC() {
    sead::Vector3f pos;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        const auto& mtx = player.hasProc() ? player.getActorMtx() : mActor->getMtx();
        pos = mtx.getTranslation();
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("追跡", &pack);
}

// NON_MATCHING: the original builds the translation copy in a vector register (ld1 lane + 8/4-byte
// stores) and keeps &pack in a different register
void NPCChasePlayerBlueFire::sub_71004C35CC() {
    sead::Vector3f pos;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        const auto& mtx = player.hasProc() ? player.getActorMtx() : mActor->getMtx();
        pos = mtx.getTranslation();
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addBool(false, "TerrorOccurring", -1);
    changeChild("接近待機", &pack);
}

// NON_MATCHING: the original builds the translation copy in a vector register (ld1 lane + 8/4-byte
// stores) and keeps &pack in a different register
void NPCChasePlayerBlueFire::sub_71004C370C() {
    sead::Vector3f pos;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        const auto& mtx = player.hasProc() ? player.getActorMtx() : mActor->getMtx();
        pos = mtx.getTranslation();
    }
    const f32 time = *mLostTimer_s;
    _58.mTimer = ksys::Timer(time, time);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addBool(false, "TerrorOccurring", -1);
    changeChild("見失い", &pack);
}

// 0x71004c32a4
// NON_MATCHING: accessor lifetime and the two sensor traversals allocate registers differently.
bool NPCChasePlayerBlueFire::sub_71004C32A4() {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;
    Unk_7102451678 filter;
    const ksys::act::BaseProcLink* link = nullptr;
    for (auto* sensor = awareness->_260[0]; sensor; sensor = awareness->_260[1]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
        if (!entry)
            break;
        if (entry->_a8 < *mLostDist_s)
            link = &entry->_0.mLink;
    }
    ksys::act::ActorLinkConstDataAccess actor;
    if (!link || !ksys::act::acquireActor(link, &actor) || !actor.isPlayerProfile())
        return false;
    const sead::Vector3f position = actor.getActorMtx().getTranslation();
    auto* weapon = ksys::act::ActorSystem::instance()->getPlayerLink()->m273();
    if (!weapon)
        return false;
    auto* chemical = weapon->getChemicalStuff();
    if (!chemical || chemical->_c0 != 2 || (chemical->_c & 0x100000) == 0)
        return false;
    auto* placement = AutoPlacementMgr::instance();
    if (!placement || !placement->auto0(position, 0))
        return false;
    if (!((position - mActor->getMtx().getTranslation()).length() < *mLostDist_s))
        return false;
    return placement->sub_7100659230(position) < 0.1f;
}

// 0x71004c2e68
// NON_MATCHING: player-position copies and child-state branch scheduling differ.
void NPCChasePlayerBlueFire::calc_() {
    auto* child = getCurrentChild();
    if (isCurrentChild("Wander")) {
        if (sub_71004C32A4())
            sub_71004C34AC();
        return;
    }
    const sead::Vector2f origin{mActor->getMtx().m[0][3], mActor->getMtx().m[2][3]};
    sead::Vector3f player_position;
    sead::Vector3f position;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        const auto& mtx = player.hasProc() ? player.getActorMtx() : mActor->getMtx();
        player_position = mtx.getTranslation();
        position = player_position;
    }
    bool can_chase = false;
    auto* weapon = ksys::act::ActorSystem::instance()->getPlayerLink()->m273();
    if (weapon) {
        auto* chemical = weapon->getChemicalStuff();
        if (chemical && chemical->_c0 == 2 && (chemical->_c & 0x100000) != 0) {
            auto* placement = AutoPlacementMgr::instance();
            if (placement && placement->auto0(position, 0) &&
                (position - mActor->getMtx().getTranslation()).length() < *mLostDist_s &&
                placement->sub_7100659230(position) < 0.1f)
                can_chase = true;
        }
    }
    if (can_chase) {
        if (isCurrentChild("接近待機")) {
            if ((sead::Vector2f{position.x, position.z} - origin).length() > *mLeaveDist_s) {
                sub_71004C34AC();
                return;
            }
        } else if (isCurrentChild("追跡")) {
            if ((sead::Vector2f{position.x, position.z} - origin).length() < *mNearDist_s) {
                sub_71004C35CC();
                return;
            }
            if (isCurrentChild("追跡") && (child->isFinished() || child->isFailed())) {
                sub_71004C34AC();
                return;
            }
        } else {
            sub_71004C34AC();
            return;
        }
    } else {
        if (!isCurrentChild("見失い")) {
            sub_71004C370C();
            return;
        }
        _58.sub_7100D3BCE4();
        if (_58.mTimer.value <= sead::Mathf::epsilon()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addBool(false, "IsPathRest", -1);
            changeChild("Wander", &pack);
            return;
        }
    }
    // Native 4C316C discards the result after updating the child's dynamic target.
    child->setDynamicParam(isCurrentChild("追跡") ? position : player_position, "TargetPos");
}

}  // namespace uking::ai
