#include "KingSystem/Sound/sndSoundCalcThread.h"
#include "Game/gameStatisticsMgr.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include <aal/aalEmitter.h>
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Physics/System/physSystem.h"
#include <prim/seadNamable.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

SoundCalcThread2::SoundCalcThread2(sead::Heap* heap)
    : Thread("SoundCalcThread", heap, Thread::cDefaultPriority,
             sead::MessageQueue::BlockType::NonBlocking, 0x7fffffff, 0x8000, 0x20),
      _fc(false) {}

void SoundCalcThread2::calc_(sead::MessageQueue::Element msg) {
    if (!_fc) {
        if (auto* system = phys::System::instance()) {
            sead::INamable name("SoundCalcThread");
            system->runJobsMaybe(&name);
            _fc = true;
        }
    }
    Thread::sleep(sead::TickSpan::makeFromSeconds(1) * (1.0f / 30.0f));
    SoundMgr::instance()->calc();
}

}  // namespace ksys::snd

Unk_710251b5c0::~Unk_710251b5c0() = default;

ksys::snd::Unk_71025a36b0::~Unk_71025a36b0() = default;

namespace ksys::snd {

KSYS_VISIBILITY_HIDDEN sead::SafeString sMaterialStaticBars = "M_Mt_Static.bars";

Unk_71025a36b0::Unk_71025a36b0() = default;

// NON_MATCHING: static bars name and manager access have different register allocation.
void Unk_71025a36b0::sub_71012C911C() {
    if (!mHandle.isSuccess() && SoundMgr::instance())
        SoundMgr::instance()->_60->sub_710105844C(&mHandle, sMaterialStaticBars, true, false);
}

void Unk_71025a36b0::sub_71012CBB90() {
    mHandle.requestUnload();
    for (s32 i = 0; i < mEntryCount; ++i) {
        auto& entry = mEntries[i];
        if (entry.mState != 0) {
            entry.mHandle.requestUnload();
            entry.mState = 0;
            entry.mPriority = 0;
            mEntries[i].mFlags |= 1;
        }
    }
    mActiveEntries.clear();
    mEnabled = false;
}

// NON_MATCHING: queue clearing remains scalar rather than unrolling four entries.
void Unk_71025a36b0::sub_71012CABB4() {
    for (s32 i = 0; i < mEntryCount; ++i) {
        auto& entry = mEntries[i];
        entry.mHandle.requestUnload();
        entry.mState = 0;
        entry.mPriority = 0;
    }
    mActiveEntries.clear();
    mQueueWrite = 0;
    mQueueRead = 0;
    if (mQueueEntries) {
        for (s32 i = 0; i < mQueueCapacity; ++i)
            mQueueEntries[i] = nullptr;
    }
    mCurrentEntry = nullptr;
}

// NON_MATCHING: queue submission and the entry traversal are scheduled differently.
void Unk_71025a36b0::sub_71012CBC3C() {
    if (!mHandle.isSuccess() && SoundMgr::instance())
        SoundMgr::instance()->_60->sub_710105844C(&mHandle, sMaterialStaticBars, true, false);
    for (s32 i = 0; i < mEntryCount; ++i) {
        auto& entry = mEntries[i];
        if (entry.mFlags & 1) {
            if (!(entry.mFlags & 2)) {
                if (entry.mState == 0)
                    entry.mState = 1;
                for (;;) {
                    const u32 write = mQueueWrite.load();
                    if (s32(write - mQueueRead.load()) >= mQueueCapacity)
                        break;
                    if (mQueueWrite.compareExchange(write, write + 1)) {
                        mQueueEntries[s32((mQueueCapacity - 1U) & write)] = &entry;
                        break;
                    }
                }
            }
            mEntries[i].mFlags &= ~1;
        }
    }
    mEnabled = true;
}

}  // namespace ksys::snd

namespace ksys::snd {

// Native 251B528..530: material-grid update cadence, entry lifetime and active limit.
KSYS_VISIBILITY_HIDDEN s32 sMaterialUpdateInterval = 3;
KSYS_VISIBILITY_HIDDEN s32 sMaterialEntryLifetime = 6;
KSYS_VISIBILITY_HIDDEN s32 sMaterialEntryLimit = 6;
KSYS_VISIBILITY_HIDDEN sead::SafeString sMaterialBarsPrefix = "Mt_";

// NON_MATCHING: request/name temporaries and resource status tests use different scheduling.
void Unk_71025a36b0::sub_71012CB3A0(Entry* entry) {
    if (entry->mFlags & 2)
        return;
    if (entry->mState == 1) {
        sead::FixedSafeString<32> name;
        name.format("M_%s%s.bars", sMaterialBarsPrefix.cstr(), entry->mName.cstr());
        if (!SoundMgr::instance()->_60->requestLoadBars(&entry->mHandle, name,
                                                       mUseAudioArena, true, 0x23f000, nullptr)) {
            entry->mFlags |= 2;
            entry->mState = 0;
        } else {
            entry->mState = 2;
        }
    } else if (entry->mState == 2) {
        if (entry->mHandle.isReadyOrNeedsParse()) {
            if (!entry->mHandle.parseResource(nullptr))
                return;
            auto* bars = sead::DynamicCast<ResourceBars>(entry->mHandle.getResource());
            const bool success = entry->mHandle.isSuccess();
            if (success && bars) {
                sead::FixedSafeString<32> name;
                name.format("M_%s%s.bars", sMaterialBarsPrefix.cstr(), entry->mName.cstr());
                bars->sub_7101057588(name);
                entry->mState = 3;
            } else {
                entry->mState = 0;
                if (entry->mHandle.getStatus() != res::Handle::Status::_3)
                    entry->mFlags |= 2;
            }
        } else if (entry->mHandle.isSuccess()) {
            entry->mState = 3;
        }
    }
}

// NON_MATCHING: asset-name construction and atomic queue submission are scheduled differently.
bool Unk_71025a36b0::sub_71012CB95C(aal::AssetInfo* info, Entry* entry,
                                   const sead::SafeString& asset_name, bool use_static_bars) {
    auto* handle = use_static_bars ? &mHandle : &entry->mHandle;
    if (!handle->isSuccess())
        return false;
    auto* bars = sead::DynamicCast<ResourceBars>(handle->getResource());
    if (!bars)
        return false;
    sead::FixedSafeString<64> name;
    name.format("%s%s_%s", sMaterialBarsPrefix.cstr(), entry->mName.cstr(), asset_name.cstr());
    if (!aal::Emitter::searchAssetInfo(info, bars, name, false))
        return false;
    if (!(entry->mFlags & 2)) {
        if (entry->mState == 0)
            entry->mState = 1;
        for (;;) {
            const u32 write = mQueueWrite.load();
            if (s32(write - mQueueRead.load()) >= mQueueCapacity)
                break;
            if (mQueueWrite.compareExchange(write, write + 1)) {
                mQueueEntries[s32((mQueueCapacity - 1U) & write)] = entry;
                break;
            }
        }
    }
    entry->mPriority = sMaterialEntryLifetime;
    return true;
}

// NON_MATCHING: queue traversal, duplicate detection and list eviction use different scheduling.
void Unk_71025a36b0::sub_71012CACD4() {
    if (!mEnabled)
        return;
    if (mFrameCount % sMaterialUpdateInterval == 0)
        sub_71012CB14C();
    ++mFrameCount;
    for (auto& entry : mActiveEntries) {
        if (entry.mPriority >= 0)
            --entry.mPriority;
    }
    sead::SafeArray<Entry*, 16> newly_queued;
    s64 num_new = 0;
    while (s32(mQueueWrite.load() - mQueueRead.load()) > 0) {
        const u32 read = mQueueRead.load();
        const s32 index = (mQueueCapacity - 1U) & read;
        auto* entry = mQueueEntries[index];
        if (!entry)
            break;
        mQueueRead = read + 1;
        mQueueEntries[index] = nullptr;
        // The native consumer consumes and clears this semantic -1 pointer marker.
        if (entry == reinterpret_cast<Entry*>(-1))
            continue;
        if (mActiveEntries.isNodeLinked(entry)) {
            entry->mPriority = sMaterialEntryLifetime;
            mActiveEntries.erase(entry);
            mActiveEntries.pushBack(entry);
        } else {
            bool duplicate = false;
            for (s64 i = 0; i < num_new; ++i) {
                if (newly_queued[i] == entry) {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate)
                newly_queued[num_new++] = entry;
        }
    }
    s32 available = sMaterialEntryLimit - mActiveEntries.size();
    for (const auto& entry : mActiveEntries) {
        if (entry.mPriority < 0)
            ++available;
    }
    for (s64 i = 0; i < num_new; ++i) {
        auto* entry = newly_queued[i];
        if (available < 1) {
            entry->mState = 0;
        } else {
            entry->mPriority = sMaterialEntryLifetime;
            mActiveEntries.pushBack(entry);
        }
        --available;
    }
    for (auto& entry : mActiveEntries.robustRange()) {
        if (mActiveEntries.size() <= sMaterialEntryLimit)
            break;
        if (entry.mPriority < 0) {
            entry.mHandle.requestUnload();
            entry.mState = 0;
            entry.mPriority = 0;
            mActiveEntries.erase(&entry);
        }
    }
    for (auto& entry : mActiveEntries.robustRange()) {
        if (mActiveEntries.size() <= sMaterialEntryLimit)
            break;
        entry.mHandle.requestUnload();
        entry.mState = 0;
        entry.mPriority = 0;
        mActiveEntries.erase(&entry);
    }
    s32 best_priority = -2;
    for (auto& entry : mActiveEntries) {
        if (entry.mState == 1 || entry.mState == 2)
            sub_71012CB3A0(&entry);
        if (entry.mState == 3 && best_priority < entry.mPriority) {
            mCurrentEntry = &entry;
            best_priority = entry.mPriority;
        }
    }
    if (best_priority == -2)
        mCurrentEntry = nullptr;
}

KSYS_VISIBILITY_HIDDEN s32 sMaterialGridRadius = 1;

// NON_MATCHING: material-mask aggregation and atomic submission use different scheduling.
bool Unk_71025a36b0::sub_71012CB14C() {
    auto* link = act::ActorSystem::instance()->getPlayerLink();
    if (link) {
        auto* player = link->getPlayer();
        auto* statistics = uking::StatisticsMgr::instance();
        if (player) {
            const s32 cell_x = s32(player->getMtx()(0, 3) / 5.0f);
            const s32 cell_z = s32(player->getMtx()(2, 3) / 5.0f);
            if (mGridCell.y != cell_z || mGridCell.x != cell_x) {
                const f32 height = player->getMtx()(1, 3);
                auto* stats = statistics->getStatsPointer("material_map");
                u64 materials = 0;
                for (s32 x = -sMaterialGridRadius; x <= sMaterialGridRadius; ++x) {
                    for (s32 z = -sMaterialGridRadius; z <= sMaterialGridRadius; ++z) {
                        const sead::Vector3f position(f32(cell_x) * 5.0f + 2.5f + f32(x) * 5.0f,
                                                       height,
                                                       f32(cell_z) * 5.0f + 2.5f + f32(z) * 5.0f);
                        u32 values[2];
                        if (statistics->sub_7100E33EA0(values, 2, stats, &position) == 2)
                            materials |= u64(values[0]) | (u64(values[1]) << 32);
                    }
                }
                for (s32 i = 0; i < mEntryCount; ++i) {
                    auto& entry = mEntries[i];
                    if (entry.mMaterialIndex >= 0 &&
                        ((u64(1) << (u32(entry.mMaterialIndex) & 63)) & materials) != 0 &&
                        entry.mState == 0 && !(entry.mFlags & 2)) {
                        entry.mState = 1;
                        for (;;) {
                            const u32 write = mQueueWrite.load();
                            if (s32(write - mQueueRead.load()) >= mQueueCapacity)
                                break;
                            if (mQueueWrite.compareExchange(write, write + 1)) {
                                mQueueEntries[s32((mQueueCapacity - 1U) & write)] = &entry;
                                break;
                            }
                        }
                    }
                }
                mGridCell.x = cell_x;
                mGridCell.y = cell_z;
            }
        }
    }
    return true;
}

}  // namespace ksys::snd
