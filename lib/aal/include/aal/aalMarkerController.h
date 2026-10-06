#pragma once

#include <basis/seadTypes.h>

namespace aal {

class SoundSource;

/// Tracks the markers of the asset of a sound (and calls the marker callback). TODO: incomplete; the members that
/// the constructor / setup / reset initialise are modeled (names of the unknown ones start with an underscore).
class MarkerController {
public:
    struct MarkerCallbackInfo;
    using MarkerCallback = void (*)(const MarkerCallbackInfo& info, void* user_data);

    MarkerController();

    /// 0x7100b9f8ac: also marks the sound source (a marker callback needs the playing state to be tracked).
    void setMarkerCallback(MarkerCallback callback, s32 param, void* user_data);

    void setup(SoundSource* sound_source);
    void reset();

private:
    SoundSource* mSoundSource;
    void* _8;
    MarkerCallback mCallback;
    s32 mCallbackParam;
    void* mCallbackUserData;
    s32 _28;
    s32 _2c;
};
static_assert(sizeof(MarkerController) == 0x30, "aal::MarkerController size mismatch");

}  // namespace aal
