#include "Game/gameStasisMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "Game/gameRuneMgr.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/System/Timer.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(StasisMgr)

// NON_MATCHING: the original zero-fills mEffects with one memset (a trivially constructible handle);
// our xlink2::Handle has a user-provided constructor, so each handle is stored separately.
StasisMgr::StasisMgr() {
    ksys::act::ActorSystem::instance()->setStasisMessageSender(this);
}

StasisMgr::~StasisMgr() {
    ksys::act::ActorSystem::instance()->setStasisMessageSender(nullptr);
}

// NON_MATCHING: the free entry search and the first-entry test compile differently (loop shape).
s32 StasisMgr::m0(ksys::act::Actor* actor, const ksys::Message* message) {
    gsys::Model* model = actor->getModel();
    ksys::act::Actor* player = nullptr;
    if (act::PlayerInfo::instance())
        player = act::PlayerInfo::instance()->getPlayer();

    if (message->getType() == 0x3000004) {
        if (actor->getActorFlags2().isOff(ksys::act::Actor::ActorFlag2::_40))
            return 0;

        for (auto& entry : mEntries) {
            if (!entry.link.hasProcById(actor))
                continue;
            if (model)
                entry.damage.sub_71006DA8E4(model);
            entry.link.reset();
            entry._2a8.mELink.kill();
            if (&entry.link == &mEntries[0].link) {
                sub_7100680368(true);
                if (actor->isCalc())
                    actor->setFlag(ksys::act::Actor::ActorFlag::_9);
                if (!message->getUserData())
                    RuneMgr::instance()->setHandled();
            }
        }

        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_40);
        if (player) {
            actor->setField718(player->getParam()
                                   ->getRes()
                                   .mGParamList->getPlayer()
                                   ->mStopTimerCancelDeleteWaitTime.ref());
        }
        if (!model)
            return 1;
        Unk_710260af28::instance()->sub_7100F1D9B4(model, 0.0f, false);
        actor->sub_71011D0228(8);

    } else if (message->getType() == 0x3000003) {
        if (!player)
            return 0;
        if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
            return 0;

        if (!_42) {
            sub_7100680AC8(&mEntries[0], actor);
            _42 = true;
            _41 = true;
            _4c = 0;
            actor->setFlag(ksys::act::Actor::ActorFlag::_9);
            RuneMgr::instance()->setHandled();
        } else {
            Entry* free_entry = nullptr;
            for (auto& entry : mEntries) {
                if (!entry.link.hasProc()) {
                    free_entry = &entry;
                    break;
                }
            }
            if (!free_entry)
                return 0;
            sub_7100680AC8(free_entry, actor);
        }

        f32 time;
        if (ksys::act::hasStopTimerShortTag(actor)) {
            time = player->getParam()->getRes().mGParamList->getPlayer()->mStopTimerShortTime.ref();
        } else if (ksys::act::hasStopTimerMiddleTag(actor)) {
            time = player->getParam()->getRes().mGParamList->getPlayer()->mStopTimerMiddleTime.ref();
        } else {
            time = player->getParam()->getRes().mGParamList->getPlayer()->mStopTimerLongTime.ref();
        }
        const s32 frames = s32(std::max(static_cast<f32>(s32(time)), 1.0f));
        const f32 duration = static_cast<f32>(frames);
        if (_48 <= 0.0f || _48 > duration) {
            _48 = duration;
            _50 = frames;
            _54 = 1.0f / duration;
        }

        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_40);
        if (model) {
            Unk_710260af28::instance()->sub_7100F1D9B4(model, 0.01f, false);
            if (ksys::act::canBeStasised(actor, false))
                actor->sub_71011D0204(8);
            actor->sub_71011D0228(0x10);
        }
        mTransceiver.sendMessageOnProcessingThread(*actor->getMesTransceiverId(),
                                                   ksys::MessageType(0x8000002), nullptr, true);
        if (auto* object = actor->getMapObject()) {
            if (auto* link_data = object->getLinkData()) {
                sub_7100681368(&link_data->mLinksToSelf, ksys::MessageType(0x3000003), true);
                sub_7100681368(&link_data->mLinksCs, ksys::MessageType(0x3000003), true);
            }
        }
        return 1;

    } else if (message->getType() == 0x3000005) {
        if (_3348.indexOf(actor) >= 0)
            return 0;
        if (!_3348.pushBack(actor))
            return 0;
        if (ksys::act::canBeStasised(actor, false))
            actor->sub_71011D0204(0x10);
        return 1;

    } else if (message->getType() == 0x3000006) {
        if (_3558.indexOf(actor) >= 0)
            return 0;
        if (!_3558.pushBack(actor))
            return 0;

    } else {
        return 0;
    }

    actor->sub_71011D0228(0x10);
    return 1;
}

void StasisMgr::sub_710067F9A8() {
    _40 = 0;
    _41 = false;
    _42 = false;
    _43 = 0;
    _44 = 0;
    _48 = 0;
    _4c = 0;
    _54 = 1.0f;
    _58 = 1.0f;
    for (auto& entry : mEntries) {
        entry.link.reset();
        entry._2a8.mELink.kill();
        entry.damage.sub_71006D99F4();
    }
    for (auto& effect : mEffects)
        effect.kill();
    _32e0.reset();
}

// NON_MATCHING: _44 timer address and the 0x300000b message store are scheduled differently.
void StasisMgr::updateStasisCountdownStuff() {
    auto* event_mgr = ksys::evt::Manager::instance();
    bool event_holds_timer = false;
    if (event_mgr->hasActiveEvent() && event_mgr->sub_7100DB222C())
        event_holds_timer = event_mgr->sub_7100DB222C()->byte3FlagIsSet();

    if (!mEntries[0].link.hasProcInCalcState()) {
        if (std::max(_44 * _58, 0.0f) > 0.0f)
            ksys::Timer::update(&_44, -1.0f);
        if (_42)
            sub_7100680368(false);
        return;
    }

    for (auto& entry : mEntries) {
        if (!entry.link.hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&entry.link, &accessor);
        auto* object = accessor.getMapObject();
        if (object && object->checkCreateOrDeleteLinkObjRevival())
            entry._2a8.mELink.kill();
        else
            sub_710067FFBC(&entry);
    }

    const f32 prev_time = _48;
    f32 time = prev_time;
    if (!event_holds_timer) {
        ksys::Timer::update(&_48, -1.0f);
        time = _48;
    }

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&mEntries[0].link, &accessor);
    if (time <= 0.0f) {
        // The original passes 1 as the message user data.
        mTransceiver.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000004),
                                 reinterpret_cast<void*>(1), true);
        return;
    }
    if (!(time < 264.0f) || s32(prev_time) == _50)
        return;

    f32 offset, interval;
    if (time < 48.0f) {
        interval = 6.0f;
        offset = 3.0f;
    } else {
        offset = time < 144.0f ? 6.0f : 12.0f;
        interval = time < 144.0f ? 12.0f : 24.0f;
    }

    ksys::MessageType type = ksys::MessageType(-1);
    const s32 tick = s32(prev_time / interval);
    if (tick == s32(time / interval)) {
        if (!_41 || !(offset + interval * tick + 0.0f > time))
            return;
        _41 = false;
        type = ksys::MessageType(0x300000b);
    } else {
        if (_41)
            return;
        sead::Vector3f pos;
        sub_7100D36F90(&pos, accessor);
        ksys::snd::sub_710105DF10("BitaLock_CountDown1").setPosition(pos);
        _41 = true;
        type = ksys::MessageType(0x300000a);
    }

    for (auto& entry : mEntries) {
        if (!entry.link.hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess target;
        ksys::act::acquireActor(&entry.link, &target);
        mTransceiver.sendMessage(*target.getMessageTransceiverId(), type, nullptr, true);
    }
}

// NON_MATCHING: the alpha update at the end is missing (no xlink2 setter yet).
void StasisMgr::sub_710067FFBC(Entry* entry) {
    const bool first_active = entry->_2a8.sub_7101241B6C();
    const bool second_active = entry->_2c8.isActive();
    if (!first_active && !second_active)
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&entry->link, &accessor);
    if (!accessor.hasProc())
        return;

    if (first_active) {
        sead::Vector3f pos;
        accessor.sub_7100D11D14(&pos);
        sead::Vector3f dir = entry->damage._27c;
        dir.normalize();
        const f32 power = entry->damage.sub_71006D9B30(accessor);
        if (entry->_2a8.mELink.isActive()) {
            const sead::Vector3f ref = std::abs(dir.dot(sead::Vector3f::ey)) > 0.999f ?
                                           sead::Vector3f::ex :
                                           sead::Vector3f::ey;
            sead::Vector3f x;
            x.setCross(ref, dir);
            x.normalize();
            sead::Vector3f y;
            y.setCross(dir, x);
            y.normalize();
            const sead::Matrix34f mtx{x.x, y.x, dir.x, pos.x, x.y, y.y, dir.y, pos.y,
                                      x.z, y.z, dir.z, pos.z};
            entry->_2a8.mELink.setMatrix(mtx, {power * 1.5f + 1.0f, 1.0f, power * 19.0f + 1.0f});
        }
    }

    if (second_active) {
        sead::Matrix34f mtx;
        accessor.sub_7100D11E54(&mtx);
        entry->_2c8.setMatrix(mtx);
    }

    // TODO: the original then sets the ELink event's delay emit colour alpha (0 while the actor has
    // flag 18, else 1) and flag1 bit 1; lib/xlink2 has no public setter for it yet (libwork request).
    accessor.checkFlag18();
}

void StasisMgr::sub_7100680368(bool on_processing_thread) {
    for (auto& entry : mEntries) {
        if (entry.link.hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&entry.link, &accessor);
            if (on_processing_thread) {
                mTransceiver.sendMessageOnProcessingThread(*accessor.getMessageTransceiverId(),
                                                           ksys::MessageType(0x3000004),
                                                           nullptr, true);
            } else {
                mTransceiver.sendMessage(*accessor.getMessageTransceiverId(),
                                         ksys::MessageType(0x3000004), nullptr, true);
            }
        }
        entry._2a8.mELink.kill();
    }

    if (auto* info = act::PlayerInfo::instance()) {
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&info->getPlayerLink(), &player);
        f32 time = player.getStopTimerReloadTime();
        if (time <= 1.0f)
            time = 1.0f;
        _58 = 1.0f / time;
        const f32 progress = _42 ? std::max(_48 * _54, 0.0f) : 0.0f;
        time *= 1.0f - progress;
        if (time <= 1.0f)
            time = 1.0f;
        _44 = time;
    }
    _41 = false;
    _42 = false;
    _48 = 0;
}

// NON_MATCHING: same logic, different block layout of the target branches.
void StasisMgr::sub_7100680660(act::PlayerBase* player) {
    updateStasisCountdownStuff();
    _43 = 0;

    bool keep_target = false;
    if (auto* rune_mgr = RuneMgr::instance()) {
        if (!_40) {
            if (!(std::max(_44 * _58, 0.0f) > 0.0f) &&
                rune_mgr->checkIsSelectedRuneAndCanUse(3, player) && (rune_mgr->_90 & 0x10)) {
                _40 = 1;
            }
        } else {
            ksys::act::Actor* target = nullptr;
            if (rune_mgr->sub_710067525C() && !(std::max(_44 * _58, 0.0f) > 0.0f)) {
                target = rune_mgr->sub_71006752AC();
                if (target && ksys::act::canBeStasised(target, false)) {
                    if (_32e0.hasProcById(target)) {
                        keep_target = true;
                    } else {
                        ksys::act::ActorLinkConstDataAccess accessor;
                        ksys::act::acquireActor(&_32e0, &accessor);
                        _3558.clear();
                        mTransceiver.sendMessage(*accessor.getMessageTransceiverId(),
                                                 ksys::MessageType(0x3000006), nullptr, true);
                        _32e0.reset();

                        bool can_link = !_42;
                        if (!can_link) {
                            for (auto& entry : mEntries) {
                                if (entry.link.hasProcById(target)) {
                                    can_link = true;
                                    break;
                                }
                            }
                        }
                        if (can_link) {
                            _32e0.acquire(target, false);
                            _3348.clear();
                            keep_target = true;
                            mTransceiver.sendMessage(*target->getMesTransceiverId(),
                                                     ksys::MessageType(0x3000005), nullptr, true);
                        } else {
                            target = nullptr;
                            _43 = 1;
                        }
                    }
                }
            }
            if (!(rune_mgr->_90 & 0x10)) {
                _40 = 0;
            } else if (target && (rune_mgr->_94 & 4)) {
                _40 = 0;
                sub_7100680920(target);
            }
        }
    }
    if (keep_target)
        return;

    if (_32e0.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_32e0, &accessor);
        _3558.clear();
        mTransceiver.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000006),
                                 nullptr, true);
        _32e0.reset();
    }
}

void StasisMgr::sub_7100680920(ksys::act::Actor* actor) {
    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40)) {
        if (_42) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&mEntries[0].link, &accessor);
            mTransceiver.sendMessage(*accessor.getMessageTransceiverId(),
                                     ksys::MessageType(0x3000004), nullptr, true);
        }
    } else if (!_42 && ksys::act::canBeStasised(actor, false)) {
        mTransceiver.sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x3000003),
                                 nullptr, true);
    }
}

xlink2::HandleELink* StasisMgr::m4(ksys::act::Actor* actor) {
    for (auto it = mEntries.begin(); it != mEntries.end(); ++it) {
        if (it->link.hasProcById(actor))
            return &it->_2c8;
    }
    return nullptr;
}

void StasisMgr::sub_7100680AC8(Entry* entry, ksys::act::BaseProc* proc) {
    entry->link.acquire(proc, false);
    entry->damage.sub_71006D99F4();
    entry->_2a8.mELink.kill();
}

s32 StasisMgr::m2(const sead::Matrix34f& mtx) {
    s32 index = 0;
    for (auto& effect : mEffects) {
        if (!effect.isActive()) {
            effect = ksys::eft::searchAndEmitELink(ksys::act::Reaction::instance()->_30,
                                                   "BitaLocked_Trace");
            return m3(mtx, index);
        }
        ++index;
    }
    return -1;
}

s32 StasisMgr::m3(const sead::Matrix34f& mtx, s32 index) {
    auto& handle = mEffects[index];
    if (!handle.isActive())
        return -1;
    handle.setMatrix(mtx);
    return index;
}

void StasisMgr::sendMessage(ksys::act::Actor* actor, ksys::MessageType type,
                            bool on_processing_thread) {
    if (on_processing_thread)
        mTransceiver.sendMessageOnProcessingThread(*actor->getMesTransceiverId(), type, nullptr,
                                                   true);
    else
        mTransceiver.sendMessage(*actor->getMesTransceiverId(), type, nullptr, true);
}

// NON_MATCHING: regalloc; the original masks the ActorFlag2 byte before the shift.
void StasisMgr::sub_7100681368(ksys::map::ObjectLinkArray* links, ksys::MessageType type,
                               bool flag) {
    for (auto& link : links->links) {
        using LinkType = ksys::map::MapLinkDefType;
        const auto link_type = link.type;
        if (link_type < LinkType::FixedCs || link_type > LinkType::RackAndPinionCs ||
            link_type == LinkType::PulleyCs || link_type == LinkType::CogWheelCs) {
            continue;
        }
        auto* object = link.other_obj;
        if (!object)
            continue;
        auto* actor = object->tryGetActor(false);
        if (!actor)
            continue;
        if (type != 0x3000005 && type != 0x3000006 &&
            actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40) == flag) {
            continue;
        }
        if (actor->getProfile() == "Rope")
            continue;

        ksys::phys::RigidBody* body = actor->getMainBody();
        if (!body) {
            auto* controller = actor->getCharacterController();
            if (!controller)
                continue;
            body = controller->sub_7100F61A34();
            if (!body)
                continue;
        }
        if (body->getMotionType() != ksys::phys::MotionType::Dynamic)
            continue;
        mTransceiver.sendMessageOnProcessingThread(
            *object->tryGetActor(false)->getMesTransceiverId(), type, nullptr, true);
    }
}

void StasisMgr::sub_71006815FC(ksys::act::Actor* actor, act::DamageManagerUnk220* damage) {
    s32 index = 0;
    for (; index < mEntries.size(); ++index) {
        if (&mEntries[index].damage == damage)
            break;
    }
    if (index == mEntries.size())
        return;
    Entry& entry = mEntries[index];

    auto* reaction_actor = ksys::act::Reaction::instance()->_30;
    if (actor->getDamageMgr()) {
        auto* user = reaction_actor->getXLink()->_48;
        const f32 ratio = actor->getDamageMgr()->getStasisBlowPowerRatio();
        if (user)
            user->setPropertyValue(4, ratio);
    }
    entry.mCS.lock();
    entry._2a8.mELink.kill();
    xlinkSearchAndEmit(reaction_actor, "BitaLocked_Vector", 0, &entry._2a8);
    entry.mCS.unlock();
    sub_710067FFBC(&entry);
}

f32 StasisMgr::sub_7100681570() const {
    return std::max(_44 * _58, 0.0f);
}

act::DamageManagerUnk220* StasisMgr::sub_7100681588(ksys::act::Actor* actor) {
    for (auto it = mEntries.begin(); it != mEntries.end(); ++it) {
        if (it->link.hasProcById(actor))
            return &it->damage;
    }
    return nullptr;
}

f32 StasisMgr::sub_7100681B90() {
    return 2.0f;
}

s32 StasisMgr::sub_7100681B98() {
    return 1;
}

f32 StasisMgr::sub_7100681BA0() {
    return 0.7f;
}

}  // namespace uking
