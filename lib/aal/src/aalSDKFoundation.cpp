#include "aal/aalSDKFoundation.h"
#include <nn/atk/detail/Util.h>
#include <nn/atk/SoundSystem.h>
#include <nn/atk/detail/driver/HardwareManager.h>

namespace aal {

SDKFoundation::InitializeArg::InitializeArg()
    : _0(4), _8(0x4000), _10(0x20000), _18(3), _20(0x4000), _28(1.0f), _30(0),
      _38(5), _40{}, mArchivePath(nullptr), _50(0), _58(1), _5c(32000), _60(96),
      _64(0x20000) {}

// NON_MATCHING: the native fixed string setup repeats its empty-character store.
SDKFoundation::SDKFoundation() : mIsInitialized(false), mHeap(nullptr) {}

SDKFoundation::~SDKFoundation() {
    finalize();
}


static nn::audio::AudioDeviceName sDeviceNames[3];

// 0x7100ba0c20
void SDKFoundation::calc() {
    if (mIsInitialized && nn::atk::SoundSystem::IsInitialized() && mSoundArchivePlayer.IsAvailable())
        mSoundArchivePlayer.Update();
}

// 0x7100ba0c6c
void SDKFoundation::setOutputMode(OutputMode mode, DeviceType device) {
    const u32 value = mode;
    const nn::atk::OutputMode atk_mode = nn::atk::OutputMode(value < 3 ? value : 1);
    const u32 device_value = device;
    (void)device_value;
    nn::atk::detail::Util::Singleton<nn::atk::detail::driver::HardwareManager>::GetInstance().SetOutputMode(
        atk_mode, nn::atk::OutputDevice(0));
}

// 0x7100ba0ca8
void SDKFoundation::setTVOutputVolume(f32 volume) {
    if (volume >= 0.0f && volume <= 128.0f)
        nn::audio::SetAudioDeviceOutputVolume(&sDeviceNames[0], volume);
}

// 0x7100ba0cfc
void SDKFoundation::setStereoJackOutputVolume(f32 volume) {
    if (volume >= 0.0f && volume <= 128.0f)
        nn::audio::SetAudioDeviceOutputVolume(&sDeviceNames[1], volume);
}

// 0x7100ba0cd0
void SDKFoundation::setBuildInSpeakerOutputVolume(f32 volume) {
    if (volume >= 0.0f && volume <= 128.0f)
        nn::audio::SetAudioDeviceOutputVolume(&sDeviceNames[2], volume);
}

}  // namespace aal
