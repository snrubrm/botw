#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <nn/atk/SoundDataManager.h>
#include <nn/atk/SoundArchive.h>
#include <nn/atk/SoundHeap.h>
#include "aal/aalMemoryPool.h"
#include <nn/atk/SoundArchivePlayer.h>
#include <nn/audio.h>
#include "aal/aalDeviceType.h"
#include "aal/aalOutputMode.h"

namespace aal {

/// The connection to nn::atk when it is not used through the sead audio manager.
/// Native C2/D2 construct and destroy the embedded SDK objects; allocation records remain opaque.
class SDKFoundation : public sead::hostio::Node {
public:
    // BA032C constructs this 0x68-byte argument; BA05EC reads its fields when
    // setting up SoundSystem and opening the sound archive.
    struct InitializeArg {
        InitializeArg();
        u32 _0;
        u8 _4[4];
        u64 _8;
        u64 _10;
        u32 _18;
        u8 _1c[4];
        u64 _20;
        f32 _28;
        u8 _2c[4];
        u64 _30;
        u32 _38;
        u8 _3c[4];
        u8 _40[8];
        const char* mArchivePath;
        u64 _50;
        u32 _58;
        u32 _5c;
        u32 _60;
        u32 _64;
    };
    static_assert(sizeof(InitializeArg) == 0x68);

    SDKFoundation();
    ~SDKFoundation();
    void finalize();  // 0x7100ba04fc, declared only.

    /// 0x7100ba0c20: updates the sound archive player once the sound library is up.
    void calc();
    /// 0x7100ba0c6c (declared only)
    void setOutputMode(OutputMode mode, DeviceType device);
    /// 0x7100ba0ca8 / 0x7100ba0cd0 / 0x7100ba0cfc (declared only)
    void setTVOutputVolume(f32 volume);
    void setBuildInSpeakerOutputVolume(f32 volume);
    void setStereoJackOutputVolume(f32 volume);

private:
    bool mIsInitialized;
    sead::Heap* mHeap;
    InitializeArg mInitializeArg;
    nn::atk::SoundDataManager mSoundDataManager;
    nn::atk::FsSoundArchive mSoundArchive;
    nn::atk::SoundArchivePlayer mSoundArchivePlayer;
    nn::atk::SoundHeap mSoundHeap;
    // The allocation records in BA05EC are not yet fully modelled.
    u8 _bd8[0x80] = {};
    MemoryPool mMemoryPool;
};
static_assert(sizeof(SDKFoundation) == 0xcc0);

}  // namespace aal
