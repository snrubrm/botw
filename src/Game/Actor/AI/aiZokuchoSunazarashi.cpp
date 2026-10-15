#include "Game/Actor/AI/aiZokuchoSunazarashi.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actActorNameSearch.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <prim/seadDelegate.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Map/mapObject.h"
#include <cmath>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

static sead::FixedSafeString<64> sUnk_71025bd790("RemainsElectric");
static sead::FixedSafeString<64> sUnk_71025bd7e8("Npc_oasis033");

ZokuchoSunazarashi::ZokuchoSunazarashi(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ZokuchoSunazarashi::~ZokuchoSunazarashi() = default;

// NON_MATCHING: temporary SafeString, search record and delegate stack slots differ.
bool ZokuchoSunazarashi::init_(sead::Heap* heap) {
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    ksys::phys::HavokAI::instance()->sub_7100F82BCC(nav);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    if (auto* physics = mActor->getPhysics()) {
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer(0x27));
        physics->sub_7100FBAC4C(ksys::phys::ContactLayer(0x30));
        if (auto* bodies = physics->findBodyByName("Tgt")) {
            const s32 num = bodies->getRigidBodies().size();
            for (s32 i = 0; i < num; ++i) {
                if (auto* body = bodies->getRigidBody(i))
                    body->setFlag200();
            }
        }
        if (auto* cloth = physics->getClothSet())
            cloth->_70 |= 0x10000;
    }
    if (auto* manager = ksys::act::BaseProcMgr::instance()) {
        ksys::act::BaseProc* result = nullptr;
        ksys::act::ActorNearestSearch search("", mActor, &result, sead::Vector3f::zero);
        {
            sead::Delegate1<ksys::act::ActorNearestSearch, ksys::act::BaseProc*> callback(
                &search, &ksys::act::ActorNearestSearch::sub_7100EDC9E8);
            manager->forEachProc(sUnk_71025bd790, callback,
                                ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
        }
        if (result)
            _80.acquire(result, false);
        result = nullptr;
        {
            sead::Delegate1<ksys::act::ActorNearestSearch, ksys::act::BaseProc*> callback(
                &search, &ksys::act::ActorNearestSearch::sub_7100EDC9E8);
            manager->forEachProc(sUnk_71025bd7e8, callback,
                                ksys::act::BaseProcMgr::ProcFilter::Initializing |
                                    ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
        }
        if (result) {
            _70.acquire(result, false);
            if (!mActor->getConnectedCalcChild())
                mActor->setConnectedCalcChild(result, false);
        }
    }
    return true;
}

void ZokuchoSunazarashi::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_70.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        if (accessor.isStateSleep())
            accessor.wakeUp(ksys::act::BaseProc::SleepWakeReason(0));
    }
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.set(1);
    if (auto* controller = mActor->getCharacterController()) {
        controller->mFlags.set(0x10);
        controller->sub_7100F62DD0(0.0f);
    }
    if (auto* nav = mActor->m45()) {
        if (!nav->_18)
            ksys::phys::HavokAI::instance()->sub_7100F82DD8(nav);
    }
    _90 = false;
    _91 = false;
    _92 = false;
    m35();
}

// NON_MATCHING: value lifetimes, vector arithmetic scheduling and stack slots differ.
void ZokuchoSunazarashi::sub_7100610CD8() {
    if (mActor->get1a0())
        return;
    if (auto* object = mActor->getMapObject()) {
        if (object->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
            return;
    }

    sead::Vector3f target = mActor->getMtx().getTranslation();
    ksys::act::acc::PlayerBase player;
    sead::Vector3f player_pos = sead::Vector3f::zero;
    if (act::PlayerInfo::instance() && _80.hasProc()) {
        ksys::act::acquireActor(&act::PlayerInfo::instance()->getPlayerLink(), &player);
        ksys::act::ActorLinkConstDataAccess remains;
        ksys::act::acquireActor(&_80, &remains);
        if (player.hasProc() && remains.hasProc()) {
            player_pos = player.getActorMtx().getTranslation();
            if (player.isRidingSandSeal()) {
                const sead::Vector3f remains_pos = remains.getActorMtx().getTranslation();
                sead::Vector3f direction = remains_pos - player_pos;
                direction.normalize();
                target = player_pos + direction * *mMoveTargetDist_s;
                if (sead::Vector2f(target.x - remains_pos.x, target.z - remains_pos.z).length() <
                    *mStayAwayDist_s) {
                    target = remains_pos - direction * *mStayAwayDist_s;
                }
                if (_90) {
                    if (auto* nav = mActor->m45())
                        nav->sub_7100F75F8C(target);
                    _a0.reset(15.0f);
                    _90 = false;
                    if (_70.hasProc()) {
                        ksys::act::ActorLinkConstDataAccess accessor;
                        ksys::act::acquireActor(&_70, &accessor);
                        _b0.sendMessage(*accessor.getMessageTransceiverId(),
                                        ksys::MessageType(0x8000089), nullptr, true);
                    }
                } else if (sead::Vector2f(player_pos.x - remains_pos.x,
                                         player_pos.z - remains_pos.z).length() >
                           *mPlayerLostDis_s) {
                    ksys::act::ActorLinkConstDataAccess seal;
                    player.getSandSealActor(&seal);
                    if (seal.hasProc()) {
                        const auto& mtx = seal.getActorMtx();
                        const sead::Vector3f front = {mtx.m[0][2], mtx.m[1][2], mtx.m[2][2]};
                        const f32 angle = std::atan2(direction.cross(front).length(),
                                                    direction.dot(front));
                        if (angle < *mLeadPlayerAngle_s && !_91) {
                            _91 = true;
                            ksys::act::ActorLinkConstDataAccess accessor;
                            ksys::act::acquireActor(&_70, &accessor);
                            _b0.sendMessage(*accessor.getMessageTransceiverId(),
                                            ksys::MessageType(0x800008b), nullptr, true);
                        } else if (angle > *mLeadPlayerAngle_s * 2.0f && _91) {
                            _91 = false;
                        }
                        const f32 reverse_angle = std::atan2(front.cross(direction).length(),
                                                            (-direction).dot(front));
                        if (reverse_angle < *mLeadPlayerAngle_s && !_92) {
                            _92 = true;
                            ksys::act::ActorLinkConstDataAccess accessor;
                            ksys::act::acquireActor(&_70, &accessor);
                            _b0.sendMessage(*accessor.getMessageTransceiverId(),
                                            ksys::MessageType(0x800008c), nullptr, true);
                        } else if (reverse_angle > *mLeadPlayerAngle_s * 2.0f && _92) {
                            _92 = false;
                        }
                    }
                }
            } else {
                if (!_90) {
                    _94 = player_pos;
                    if (auto* nav = mActor->m45())
                        nav->sub_7100F75F8C(_94);
                    _a0.reset(15.0f);
                    _90 = true;
                    if (_70.hasProc()) {
                        ksys::act::ActorLinkConstDataAccess accessor;
                        ksys::act::acquireActor(&_70, &accessor);
                        _b0.sendMessage(*accessor.getMessageTransceiverId(),
                                        ksys::MessageType(0x800008a), nullptr, true);
                    }
                }
                target = _94;
            }
        }
        bool nav_failed = false;
        if (auto* nav = mActor->m45()) {
            auto lock = sead::makeScopedLock(nav->_1e0);
            nav_failed = nav->_294 == 3;
        }
        if (nav_failed || !mActor->getASList()->sub_710115ED5C(66, 10)) {
            target = player_pos;
            if (auto* nav = mActor->m45())
                nav->sub_7100F75F8C(target);
            _a0.reset(15.0f);
        }
    }

    const sead::Vector3f actor_pos = mActor->getMtx().getTranslation();
    const f32 distance = sead::Vector2f(target.x - actor_pos.x, target.z - actor_pos.z).length();
    if ((isCurrentChild("移動") || isCurrentChild("ナビメッシュ移動")) &&
        *mStopMoveDist_s > distance && _90) {
        m34();
    } else if (isCurrentChild("停止")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            m35();
    } else {
        m36(distance, target);
    }
}

void ZokuchoSunazarashi::leave_() {
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(0.0f);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        controller->sub_7100F62DD0(1.0f);
    }
    if (auto* nav = mActor->m45())
        nav->inlineReset();
    if (_70.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        _b0.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000090), nullptr,
                        false);
    }
}

void ZokuchoSunazarashi::loadParams_() {
    getStaticParam(&mPlayerLostDis_s, "PlayerLostDis");
    getStaticParam(&mLeadPlayerAngle_s, "LeadPlayerAngle");
    getStaticParam(&mMoveTargetDist_s, "MoveTargetDist");
    getStaticParam(&mStopMoveDist_s, "StopMoveDist");
    getStaticParam(&mStayAwayDist_s, "StayAwayDist");
}

void ZokuchoSunazarashi::m34() {
    if (isCurrentChild("停止"))
        return;
    if (auto* nav = mActor->m45())
        nav->inlineReset();
    changeChild("停止");
    if (_70.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        _b0.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800008d), nullptr,
                        true);
    }
}

void ZokuchoSunazarashi::m35() {
    if (isCurrentChild("待機"))
        return;
    changeChild("待機");
    if (_70.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_70, &accessor);
        _b0.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800008e), nullptr,
                        true);
    }
}

void ZokuchoSunazarashi::m36(f32 distance, const sead::Vector3f& target) {
    auto* nav = mActor->m45();
    if (!nav)
        return;

    u8 state;
    {
        auto lock = sead::makeScopedLock(nav->_1e0);
        state = nav->_294;
    }
    if (isCurrentChild("ナビメッシュ移動")) {
        const sead::Vector3f nav_target = nav->_1a0;
        switch (state) {
        case 1:
            getCurrentChild()->setDynamicParam(nav_target, "TargetPos");
            break;
        case 2: {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target, "TargetPos", -1);
            changeChild("移動", &pack);
            return;
        }
        }
    } else if (isCurrentChild("移動")) {
        if (state == 1) {
            const sead::Vector3f nav_target = nav->_1a0;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(nav_target, "TargetPos", -1);
            changeChild("ナビメッシュ移動", &pack);
            return;
        }
        getCurrentChild()->setDynamicParam(target, "TargetPos");
    } else {
        if (!(distance > *mStopMoveDist_s * 1.5f))
            return;
        if (!(nav->_220 & 0x41000)) {
            if (auto* character = mActor->m45())
                character->sub_7100F75F8C(target);
            _a0.reset(15.0f);
        }
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(target, "TargetPos", -1);
        changeChild("移動", &pack);
        if (_70.hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&_70, &accessor);
            _b0.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800008f),
                           nullptr, true);
        }
        return;
    }

    if (!(_a0.value <= sead::Mathf::epsilon())) {
        _a0.update();
        if (_a0.value <= sead::Mathf::epsilon()) {
            if (auto* character = mActor->m45())
                character->sub_7100F75F8C(target);
            _a0.reset(15.0f);
        }
    }
}

}  // namespace uking::ai
