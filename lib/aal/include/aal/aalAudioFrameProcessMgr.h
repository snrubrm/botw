#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <thread/seadCriticalSection.h>

namespace aal {

/// A process that is run every audio frame by the AudioFrameProcessMgr.
class IAudioFrameProcess {
public:
    virtual ~IAudioFrameProcess() = default;
    // The native FinalOutputMeasure callback names this slot.
    virtual void audioFrameProcess_() = 0;

    static constexpr s32 getListNodeOffset() { return 8; }

private:
    sead::ListNode mListNode;
};

/// Runs the registered processes in the audio frame callback of the sound thread (the callback is
/// registered when the first process is added).
class AudioFrameProcessMgr {
public:
    AudioFrameProcessMgr();
    ~AudioFrameProcessMgr();

    /// Returns false if the process is already registered.
    bool addProcess(IAudioFrameProcess* process);
    void removeProcess(IAudioFrameProcess* process);

private:
    static void audioFrameCallback_(unsigned long arg);

    static AudioFrameProcessMgr* sInstance;

    sead::OffsetList<IAudioFrameProcess> mProcesses;
    sead::CriticalSection mCS;
    bool mIsCallbackRegistered;
};

}  // namespace aal
