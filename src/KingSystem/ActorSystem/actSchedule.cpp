#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Resource/Actor/resResourceAISchedule.h"
#include "KingSystem/Quest/qstManager.h"
#include "KingSystem/Resource/resHandle.h"

namespace ksys::act {

// 0x71024d8ec0 (lane4 s85; placeholder name): the values of the DisplayDistanceMode schedule setting.
static const sead::SafeString sDisplayDistanceModes[] = {"None", "Auto"};

Schedule::Schedule(Actor* actor) : mActor(actor) {}

bool Schedule::allocRes(sead::Heap* heap) {
    mHeap = heap;
    if (!heap)
        return false;
    mResHandle = new (heap) res::Handle;
    return mResHandle != nullptr;
}

void Schedule::freeRes() {
    if (mHeap && mResHandle) {
        mResHandle->~Handle();
        mHeap->free(mResHandle);
        mResHandle = nullptr;
    }
}

void Schedule::reset() {
    _2f8 &= 2;
    sub_7100D192C0(nullptr, &sead::SafeString::cNullChar, false);
    if (auto* mgr = qst::Manager::instance())
        mgr->auto4(mActor);
    x_6(mActor);
    _2e8 = 0;
    _68 = sead::SafeString::cEmptyString;
    _78 = &sead::SafeString::cNullChar;
    _88 = sead::SafeString::cEmptyString;
    _98 = sead::SafeString::cEmptyString;
    _a8 = sead::SafeString::cEmptyString;
    _b8 = sead::SafeString::cEmptyString;
}

// NON_MATCHING: the original drops the "None" comparison of the DisplayDistanceMode search (its result does not
// matter) but keeps its cstr() calls; the stack slot of `mode` and the bool result of sub_7100EE3FA8 (and vs select)
// also differ.
void Schedule::sub_7100D192C0(const al::ByamlIter* iter, const char* name, bool value) {
    if (iter) {
        _d0 = *iter;
        _e0 = _d0;
        _126 = true;
        _2f4 = 1;
    } else if (auto* param = mActor->getParam()) {
        if (auto* schedule = param->getRes().mAISchedule) {
            al::ByamlIter root(schedule->getData());
            if (root.isValid()) {
                if (root.tryGetIterByKey(&_110, "DefaultTimeline")) {
                    _d0 = _110;
                    _e0 = _d0;
                }
                root.tryGetIterByKey(&_100, "ConditionalTimelines");
                _f0 = _100;
                const char* mode;
                if (root.tryGetStringByKey(&mode, "DisplayDistanceMode")) {
                    s32 mode_idx = 0;
                    for (s32 i = 1; i >= 0; --i) {
                        if (sDisplayDistanceModes[i] == mode) {
                            mode_idx = i;
                            break;
                        }
                    }
                    _2ec = mode_idx;
                }
            }
        }
    }

    sub_7100D1AAD8();
    _10 = name;
    _121 = 1;
    _122 = false;
    _123 = false;

    if (!_d0.isValid())
        return;
    al::ByamlIter trigger_events;
    if (!_d0.tryGetIterByKey(&trigger_events, "TriggerEvents"))
        return;
    al::ByamlIter entry;
    al::ByamlIter params;
    for (s32 i = 0; i < trigger_events.getSize(); ++i) {
        trigger_events.tryGetIterByIndex(&entry, i);
        if (!entry.isValid())
            continue;
        const char* trigger;
        if (!entry.tryGetStringByKey(&trigger, "Trigger"))
            continue;
        entry.tryGetIterByKey(&params, "Parameters");
        if (sead::SafeString(trigger) != "Near")
            continue;

        bool near = false;
        if (!value && mActor->isCalc() && sub_7100D1C27C(&params, _123)) {
            auto* player = ActorSystem::instance()->getPlayerLink();
            if (player && mActor) {
                ActorLinkConstDataAccess accessor(mActor);
                ActorLinkConstDataAccess player_accessor;
                player->getActorViaAccessor(&player_accessor);
                near = sub_7100EE3FA8(accessor, player_accessor, true, 0.0f);
            }
        }
        _123 = near;
        return;
    }
}

}  // namespace ksys::act
