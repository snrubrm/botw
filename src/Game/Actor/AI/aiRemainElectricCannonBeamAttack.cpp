#include "Game/Actor/AI/aiRemainElectricCannonBeamAttack.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71007302CC.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/ActorSystem/actActorNameSearch.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"

namespace uking::ai {

static sead::FixedSafeString<64> sUnk_71025bbc78("Npc_oasis033");
static sead::FixedSafeString<64> sUnk_71025bbcd0("Animal_SunazarashiSP_B");

RemainElectricCannonBeamAttack::RemainElectricCannonBeamAttack(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RemainElectricCannonBeamAttack::~RemainElectricCannonBeamAttack() {
    if (_38.hasProc())
        _38.reset();
    if (_48.hasProc())
        _48.reset();
}

bool RemainElectricCannonBeamAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainElectricCannonBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710053E864();
    if (_38.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_38, &accessor);
        _58.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000085), nullptr,
                        true);
    }
    changeChild("溜め");
    mFlags.set(Flag::Changeable);
}

// NON_MATCHING: search record and delegate stack slots differ.
void RemainElectricCannonBeamAttack::sub_710053E864() {
    auto* mgr = ksys::act::BaseProcMgr::instance();
    if (!mgr)
        return;
    if (!_38.hasProc()) {
        ksys::act::BaseProc* result = nullptr;
        ksys::act::ActorNearestSearch search("", mActor, &result, sead::Vector3f::zero);
        sead::Delegate1<ksys::act::ActorNearestSearch, ksys::act::BaseProc*> callback(
            &search, &ksys::act::ActorNearestSearch::sub_7100EDC9E8);
        mgr->forEachProc(sUnk_71025bbc78, callback,
                         ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
        if (result)
            _38.acquire(result, false);
    }
    if (!_48.hasProc()) {
        ksys::act::BaseProc* result = nullptr;
        ksys::act::ActorNearestSearch search("", mActor, &result, sead::Vector3f::zero);
        sead::Delegate1<ksys::act::ActorNearestSearch, ksys::act::BaseProc*> callback(
            &search, &ksys::act::ActorNearestSearch::sub_7100EDC9E8);
        mgr->forEachProc(sUnk_71025bbcd0, callback,
                         ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
        if (result)
            _48.acquire(result, false);
    }
}

// NON_MATCHING: global and player pointer load scheduling and saved registers.
void RemainElectricCannonBeamAttack::calc_() {
    sub_710053E864();
    auto* child = getCurrentChild();
    if (!child)
        return;
    if (isCurrentChild("発射") && _38.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_38, &accessor);
        sead::Vector3f position;
        accessor.getActorMtx().getTranslation(position);
        child->setDynamicParam(position, "SafePos");
    } else if (isCurrentChild("予兆")) {
        auto* player_info = uking::act::PlayerInfo::instance();
        f32 radius = 0;
        auto* global = ksys::act::GlobalParameter::instance();
        if (global && global->getGlobalParam())
            radius = global->getGlobalParam()->mGerudoQueenSafetyAreaRadius.ref();
        bool protected_player = false;
        if (_38.hasProc() && player_info && player_info->getPlayerLink().hasProc()) {
            ksys::act::acc::PlayerBase player;
            ksys::act::acquireActor(&player_info->getPlayerLink(), &player);
            const bool riding = player.isRidingSandSeal();
            protected_player = sub_71007303F0(&player_info->getPlayerLink(), &_38,
                                            riding ? radius + 0.25f : radius);
        }
        child->setDynamicParam(protected_player, "WillBeProtected");
    }
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("溜め"))
            sub_710053EC4C();
        else if (isCurrentChild("予兆"))
            sub_710053EE28();
        else if (isCurrentChild("発射"))
            setFinished();
    }
}

// NON_MATCHING: global and player pointer load scheduling.
void RemainElectricCannonBeamAttack::sub_710053EC4C() {
    if (_38.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_38, &accessor);
        _58.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000086),
                        nullptr, true);
    }
    auto* player_info = uking::act::PlayerInfo::instance();
    f32 radius = 0;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam())
        radius = global->getGlobalParam()->mGerudoQueenSafetyAreaRadius.ref();
    bool protected_player = false;
    if (_38.hasProc() && player_info && player_info->getPlayerLink().hasProc()) {
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&player_info->getPlayerLink(), &player);
        const bool riding = player.isRidingSandSeal();
        protected_player = sub_71007303F0(&player_info->getPlayerLink(), &_38,
                                        riding ? radius + 0.25f : radius);
    }
    ksys::act::ai::InlineParamPack params;
    params.addBool(protected_player, "WillBeProtected", -1);
    changeChild("予兆", &params);
}

// NON_MATCHING: position snapshots, vector arithmetic and saved registers differ.
void RemainElectricCannonBeamAttack::sub_710053EE28() {
    sead::Vector3f player_position = sead::Vector3f::zero;
    if (auto* info = uking::act::PlayerInfo::instance()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&info->getPlayerLink(), &accessor);
        if (accessor.hasProc())
            accessor.getActorMtx().getTranslation(player_position);
    }
    sead::Vector3f safe_position = sead::Vector3f::zero;
    if (_38.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_38, &accessor);
        if (accessor.hasProc())
            accessor.getActorMtx().getTranslation(safe_position);
    }
    sead::Vector3f target_position = sead::Vector3f::zero;
    auto* player_info = uking::act::PlayerInfo::instance();
    f32 radius = 0;
    auto* global = ksys::act::GlobalParameter::instance();
    if (global && global->getGlobalParam())
        radius = global->getGlobalParam()->mGerudoQueenSafetyAreaRadius.ref();
    bool protected_player = false;
    if (_38.hasProc() && player_info && player_info->getPlayerLink().hasProc()) {
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&player_info->getPlayerLink(), &player);
        const bool riding = player.isRidingSandSeal();
        protected_player = sub_71007303F0(&player_info->getPlayerLink(), &_38,
                                        riding ? radius + 0.25f : radius);
    }
    if (protected_player) {
        target_position = safe_position;
        sead::Vector3f direction = mActor->getMtx().getTranslation() - safe_position;
        direction.normalize();
        target_position += radius * direction;
    } else {
        target_position = player_position;
    }
    if (_38.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_38, &accessor);
        if (protected_player)
            _58.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000087),
                            nullptr, true);
    }
    ksys::act::ai::InlineParamPack params;
    params.addBool(protected_player, "IsProtected", -1);
    params.addVec3(target_position, "TargetPos", -1);
    params.addVec3(safe_position, "SafePos", -1);
    changeChild("発射", &params);
}

void RemainElectricCannonBeamAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainElectricCannonBeamAttack::loadParams_() {}

}  // namespace uking::ai
