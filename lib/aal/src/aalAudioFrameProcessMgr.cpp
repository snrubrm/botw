#include "aal/aalAudioFrameProcessMgr.h"
#include <nn/atk/detail/driver/SoundThread.h>
#include <prim/seadScopedLock.h>

namespace aal {

AudioFrameProcessMgr* AudioFrameProcessMgr::sInstance = nullptr;

// 0x7100b7c0c0
AudioFrameProcessMgr::AudioFrameProcessMgr() : mIsCallbackRegistered(false) {
    mProcesses.initOffset(IAudioFrameProcess::getListNodeOffset());
    sInstance = this;
}

// 0x7100b7c108
AudioFrameProcessMgr::~AudioFrameProcessMgr() {
    {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        mProcesses.clear();
        if (mIsCallbackRegistered)
            nn::atk::detail::driver::SoundThread::GetInstance().ClearSoundFrameUserCallback();
    }
    sInstance = nullptr;
}

// 0x7100b7c160
bool AudioFrameProcessMgr::addProcess(IAudioFrameProcess* process) {
    if (mProcesses.isNodeLinked(process))
        return false;

    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (!mIsCallbackRegistered) {
        nn::atk::detail::driver::SoundThread::GetInstance().RegisterSoundFrameUserCallback(
            audioFrameCallback_, reinterpret_cast<unsigned long>(this));
    }
    mProcesses.pushBack(process);
    return true;
}

// 0x7100b7c200
void AudioFrameProcessMgr::removeProcess(IAudioFrameProcess* process) {
    if (!mProcesses.isNodeLinked(process))
        return;

    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    mProcesses.erase(process);
    if (mProcesses.size() == 0 && mIsCallbackRegistered)
        nn::atk::detail::driver::SoundThread::GetInstance().ClearSoundFrameUserCallback();
}

// 0x7100b7c28c
void AudioFrameProcessMgr::audioFrameCallback_(unsigned long arg) {
    auto* mgr = reinterpret_cast<AudioFrameProcessMgr*>(arg);
    if (!mgr)
        return;

    sead::ScopedLock<sead::CriticalSection> lock(&mgr->mCS);
    for (IAudioFrameProcess& process : mgr->mProcesses)
        process.process();
}

}  // namespace aal
