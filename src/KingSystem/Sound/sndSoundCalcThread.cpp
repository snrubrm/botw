#include "KingSystem/Sound/sndSoundCalcThread.h"
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
