#include "Game/AI/aiUnk_7100711020.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNest.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

Unk_7100711020::Unk_7100711020(ksys::act::Actor* actor)
    : mActor(actor), _28(actor, 0x8000010), _80(actor, 0x800000f), _d0(actor, 0x8000008) {}

Unk_7100711020::~Unk_7100711020() {
    if (_10.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_10, &accessor);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x300000f),
                            nullptr, false);
    }
}

void Unk_7100711020::sub_7100711450() {
    _10c = ksys::Timer(0, 0, 1.0f);
    _100 = ksys::Timer(0, 0, 1.0f);
    _118 = ksys::Timer(0, 0, 1.0f);
    _d = false;
    _8 = std::numeric_limits<f32>::infinity();
    _20 = 0;
    if (_10.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_10, &accessor);
        accessor.wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void Unk_7100711020::sub_7100711BDC() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000);
    if (_10.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_10, &accessor);
        _28.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
    }
}

void Unk_7100711020::sub_7100711B14(bool update_pos) {
    if (update_pos) {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        sead::ScopedLock<sead::JobQueueLock> lock(&_28._18.mLock);
        _28._18._2c = pos;
    }
    if (_10.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_10, &accessor);
        _28.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
    }
}

// NON_MATCHING: stack layout only (the original places the loop's accessor above `best` and the
// filter, as if it came from an inline helper)
void Unk_7100711020::sub_7100711C5C() {
    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return;

    ksys::act::BaseProcLink best;
    Unk_71024514c0 filter{actor};
    ksys::act::Unk_7100d78e50* best_entry = nullptr;
    f32 best_dist = std::numeric_limits<f32>::max();
    while (auto* sensor = awareness->_260[3]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
        if (!entry)
            break;

        auto& link = entry->_0.mLink;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (link.hasProc() && _10 == link)
            continue;
        if (!sub_71005E116C(&link))
            continue;
        if (entry->_a8 < best_dist) {
            best = link;
            best_dist = entry->_a8;
            best_entry = entry;
        }
    }

    if (best.hasProc() && best_entry) {
        sub_7100711E0C(best, 2, 3, &best_entry->_88, &best_entry->_58);
        _100.value = 0;
        _100.previous_value = 0;
        if (_10.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&_10, &accessor);
            _80.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
        }
    }
}

void Unk_7100711020::sub_7100711E0C(const ksys::act::BaseProcLink& target, s32 a, s32 b,
                                    const sead::Vector3f* pos, const sead::Matrix34f* mtx) {
    auto* actor = mActor;
    _20 = a;
    const sead::Vector3f own_pos = actor->getMtx().getTranslation();
    sub_71005D8DE8(actor, target, mtx, nullptr);
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_80._18.mLock);
        _80._18._0 = target;
        _80._18._10.acquire(actor, false);
        _80._18._20 = b;
        _80._18._24 = a;
        _80._18._28 = *pos;
    }
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_28._18.mLock);
        _28._18._0 = target;
        _28._18._10.acquire(actor, false);
        _28._18._20 = *pos;
        _28._18._2c = own_pos;
    }
}

bool Unk_7100711020::sub_7100711298(sead::Heap* heap, const sead::SafeString& name,
                                    bool has_map_object) {
    if (has_map_object) {
        sead::SafeString actor_name;
        if (name.isEmpty())
            actor_name = mActor->getParam()->getRes().mGParamList->getNest()->mCreateActor.ref();
        else
            actor_name = name;

        ksys::act::InstParamPack pack;
        ksys::act::ActorCreator::setCreatePriorityState1(pack, mActor);
        pack->addMatrix(mActor->getMtx());
        auto* actor = ksys::act::ActorCreator::instance()->createActor(
            actor_name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack,
            true, false);
        if (!actor)
            return false;

        _10.acquire(actor, false);
        _118 = ksys::Timer(0, 0, 1.0f);
        if (_20 != 0)
            _80.sub_710070DBB0(*actor->getMessageTransceiver().getId(), true);
        if (_d)
            _28.sub_710070DBB0(*actor->getMessageTransceiver().getId(), true);
        auto* owner = mActor;
        sub_7100738C88(actor, owner);
        sub_7100738D28(actor, owner);
    }
    return true;
}

void Unk_7100711020::sub_71007114DC() {
    auto* actor = mActor;
    _118.update();
    sub_71007116E0();
    if (_10.hasProc())
        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    else
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000);

    if (sub_71005D8F28(actor)) {
        const auto& target_pos = sub_71005D9330(actor);
        if ((actor->getMtx().getTranslation() - target_pos).length() > _8) {
            if (_10.hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&_10, &accessor);
                _d0.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
            }
            sub_71005D8E9C(actor);
        } else if (_100.value > 10.0f) {
            _100.value = 0;
            _100.previous_value = 0;
            if (_10.hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&_10, &accessor);
                _80.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
            }
        } else {
            _100.update();
        }
    } else if (_20 >= 2) {
        _20 = 0;
        if (_10.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&_10, &accessor);
            _d0.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
        }
    }

    if (_d) {
        if (_10c.value > 10.0f)
            sub_7100711B14(true);
        else
            _10c.update();
    }
}

// NON_MATCHING: stack layout only (the loop's accessor sits above `best_link` and the filter, as in
// sub_7100711C5C)
void Unk_7100711020::sub_71007116E0() {
    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return;

    u32 best_kind = _20;
    ksys::act::BaseProcLink best_link;
    Unk_7102451470 filter{actor};
    s32 best_sensor = -1;
    ksys::act::Unk_7100d78e50* best_entry = nullptr;
    f32 best_dist = std::numeric_limits<f32>::max();
    bool best_is_not_living = true;
    for (s32 i = 0; i < 4; ++i) {
        while (auto* sensor = awareness->_260[i]) {
            auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
            if (!entry)
                break;

            auto& link = entry->_0.mLink;
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (link.hasProc() && _10 == link)
                continue;
            if (!sub_71005E116C(&link))
                continue;

            u32 kind = entry->_a0;
            const bool is_not_living = ksys::act::isNotLivingCreature(&link);
            if (!best_is_not_living && is_not_living)
                continue;
            if (is_not_living)
                kind = 1;
            if (_20 == 1 || _20 == 2 || is_not_living || ksys::act::isPlayerProfile(&link)) {
                if (best_kind < kind || (best_kind == kind && entry->_a8 < best_dist) ||
                    (best_is_not_living && !is_not_living)) {
                    best_link = link;
                    best_dist = entry->_a8;
                    best_sensor = i;
                    best_kind = kind;
                    best_entry = entry;
                    best_is_not_living = is_not_living;
                }
            }
        }
    }

    if (!best_link.hasProc() || !best_entry)
        return;

    auto* target = sub_71005D9050(actor);
    if (target && best_kind == _20 && *target == best_link)
        return;

    _20 = best_kind;
    if (best_is_not_living) {
        sead::ScopedLock<sead::JobQueueLock> lock(&_80._18.mLock);
        _80._18._0.acquire(nullptr, false);
        _80._18._10.acquire(actor, false);
        _80._18._20 = best_sensor;
        _80._18._24 = best_kind;
        _80._18._28 = best_entry->_88;
    } else {
        const sead::Vector3f own_pos = actor->getMtx().getTranslation();
        sub_71005D8DE8(actor, best_link, &best_entry->_58, nullptr);
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_80._18.mLock);
            _80._18._0 = best_link;
            _80._18._10.acquire(actor, false);
            _80._18._20 = best_sensor;
            _80._18._24 = _20;
            _80._18._28 = best_entry->_88;
        }
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_28._18.mLock);
            _28._18._0 = best_link;
            _28._18._10.acquire(actor, false);
            _28._18._20 = best_entry->_88;
            _28._18._2c = own_pos;
        }
    }
    _100.value = 0;
    _100.previous_value = 0;
    if (_10.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_10, &accessor);
        _80.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
    }
}
