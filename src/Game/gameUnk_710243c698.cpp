#include "Game/gameUnk_710243c698.h"
#include <cmath>
#include <limits>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Utils/Thread/MessageAck.h"

namespace uking {

Unk_710243c698::Unk_710243c698() = default;

// NON_MATCHING: the original inlines ~Unk_7102381468 (vtable store, link reset); ours calls the
// out-of-line copy (defining it inline makes the Unk_7102381468 vtable reference D2, see the header).
Unk_710243c698::~Unk_710243c698() = default;

void Unk_710243c698::sub_710067E2B4() {
    for (auto& entry : mEntries) {
        entry.bomb.reset();
        entry.flags.makeAllZero();
    }
    _d0._18 = this;
}

// NON_MATCHING: stack layout (the original reuses the matrix copy's slot for the isFadingOut accessors).
void Unk_710243c698::sub_710067E2F8() {
    for (s32 i = 0; i < 3; ++i) {
        auto& entry = mEntries[i];
        if (!entry.flags.isOn(2) && entry.bomb.hasProc() && !isFadingOut(entry.bomb)) {
            _d0.sub_710070DCC0(&entry.bomb, true);
        } else if (!entry.bomb.hasProc() || isFadingOut(entry.bomb)) {
            entry.flags.makeAllZero();
            entry.bomb.reset();
        }

        if (entry.flags.isOn(4) && entry.bomb.hasProc() && !isFadingOut(entry.bomb)) {
            sub_710067E55C(i);
            continue;
        }

        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&entry.bomb, &accessor);
        if (accessor.isStateSleep()) {
            if (entry._10.hasProc()) {
                ksys::act::ActorLinkConstDataAccess carrier;
                ksys::act::acquireActor(&entry._10, &carrier);
                const sead::Matrix34f mtx = carrier.getActorMtx();
                accessor.sub_7100D14D40(mtx);
            } else if (entry.flags.isOn(0x10)) {
                sub_710067E838(i);
            }
        }
    }
}

// NON_MATCHING: the original negates the result before the join (ours after it).
bool Unk_710243c698::sub_710067E4E0(s32 idx) {
    auto& entry = mEntries[idx];
    return entry.bomb.hasProc() && !isFadingOut(entry.bomb);
}

bool Unk_710243c698::sub_710067E55C(s32 idx) {
    auto& entry = mEntries[idx];
    if (!entry.bomb.hasProc() || isFadingOut(entry.bomb))
        return false;

    entry.flags.set(4);
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&entry.bomb, &accessor);
    if (accessor.isStateSleep()) {
        sead::Matrix34f mtx;
        if (entry._10.hasProc()) {
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_f0._18.mLock);
                _f0._18.mLink = entry.bomb;
            }
            _f0.sub_710070DCC0(&entry._10, true);
            ksys::act::ActorLinkConstDataAccess carrier;
            ksys::act::acquireActor(&entry._10, &carrier);
            mtx = carrier.getActorMtx();
            if (carrier.getProfile() == "Sandworm")
                carrier.sub_7100D119A8(&mtx, "Spine_1");
        } else if (!accessor.sub_7100D112FC(&mtx)) {
            mtx = accessor.getActorMtx();
        }
        accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 7, -1);
    }
    mTransceiver.sendMessage(*getTransceiverId(entry.bomb), ksys::MessageType(0x800000a), nullptr, true);
    return true;
}

void Unk_710243c698::sub_710067E838(s32 idx) {
    auto& entry = mEntries[idx];
    if (!entry.bomb.hasProc() || isFadingOut(entry.bomb))
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(&entry.bomb, &accessor) || accessor.isStateCalc()) {
        mTransceiver.sendMessage(*getTransceiverId(entry.bomb), ksys::MessageType(0x8000004), nullptr,
                                 true);
    } else {
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        entry.bomb.reset();
        entry.flags.makeAllZero();
        entry._10.reset();
    }
}

ksys::act::Actor* Unk_710243c698::doSpawnRemoteBomb(s32 idx, const sead::Matrix34f& mtx, s32 type,
                                                    bool a4) {
    auto& entry = mEntries[idx];
    if (entry.bomb.hasProc() && !isFadingOut(entry.bomb))
        return nullptr;

    const bool lv2 = ksys::gdt::getFlag_IsGet_Obj_RemoteBombLv2();
    ksys::act::Actor* actor;
    if (type == 2 && act::DamageInfoMgr::enableBoomerangRemoteBombs()) {
        if (lv2)
            actor = ksys::act::ActorCreator::instance()->createActor(
                "RemoteBombBoomerang2", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, a4, false);
        else
            actor = ksys::act::ActorCreator::instance()->createActor(
                "RemoteBombBoomerang", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, a4, false);
    } else if (lv2) {
        if (type == 1)
            actor = ksys::act::ActorCreator::instance()->createActor(
                "RemoteBombCube2", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, a4, false);
        else
            actor = ksys::act::ActorCreator::instance()->createActor(
                "RemoteBomb2", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, a4, false);
    } else {
        if (type == 1)
            actor = ksys::act::ActorCreator::instance()->createActor(
                "RemoteBombCube", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, a4, false);
        else
            actor = ksys::act::ActorCreator::instance()->createActor(
                "RemoteBomb", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, a4, false);
    }
    if (!actor)
        return nullptr;

    actor->setMatrix(mtx, nullptr);
    if (auto* root_ai = actor->getRootAi())
        root_ai->setI(5);
    entry.bomb.acquire(actor, false);
    entry.flags.makeAllZero();
    entry._10.reset();
    return actor;
}

f32 Unk_710243c698::sub_710067EB24(s32 idx, const sead::Vector3f& pos) {
    auto& entry = mEntries[idx];
    if (entry.bomb.hasProc() && !isFadingOut(entry.bomb)) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&entry.bomb, &accessor);
        return (accessor.getActorMtx().getTranslation() - pos).length();
    }
    return std::numeric_limits<f32>::max();
}

f32 Unk_710243c698::sub_710067EC28(s32 idx, const sead::Vector3f& pos) {
    auto& entry = mEntries[idx];
    if (entry.bomb.hasProc() && !isFadingOut(entry.bomb)) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&entry.bomb, &accessor);
        const sead::Vector3f dir = accessor.getActorMtx().getTranslation() - pos;
        return sead::Mathf::rad2deg(std::atan2(dir.x, dir.z));
    }
    return 0.0f;
}

void Unk_710243c698::sub_710067ED08(ksys::act::BaseProc* proc, s32 bit, bool on) {
    for (auto& entry : mEntries) {
        if (entry.bomb.hasProcById(proc))
            entry.flags.changeBit(bit, on);
    }
}

void Unk_710243c698::sub_710067EDDC(ksys::act::BaseProc* proc, const ksys::act::BaseProcLink& link) {
    for (auto& entry : mEntries) {
        if (entry.bomb.hasProcById(proc)) {
            entry._10 = link;
            entry.flags.set(0x10);
        }
    }
}

void Unk_710243c698::sub_710067EE7C(ksys::act::BaseProc* proc) {
    for (auto& entry : mEntries) {
        if (entry.bomb.hasProcById(proc)) {
            entry._10.reset();
            entry.flags.reset(0x10);
        }
    }
}

void Unk_710243c698::handleAck(const ksys::MessageAck& ack) {
    if (ack.getType() != 0x800003c)
        return;
    s32 i = 0;
    for (; i < 3; ++i) {
        const auto& dest = ack.getDestination();
        const auto* id = getTransceiverId(mEntries[i].bomb);
        if (dest.queue_id == id->queue_id && dest.id == id->id)
            break;
    }
    if (i == 3)
        return;
    mEntries[i].flags.change(2, ack.isDestinationValid() && ack.isSuccess());
}

}  // namespace uking
