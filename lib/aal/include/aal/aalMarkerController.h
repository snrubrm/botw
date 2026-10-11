#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include "aal/aalAssetInfo.h"

namespace aal {

class SoundSource;
class MarkerInfo;

/// Tracks the markers of the asset of a sound (and calls the marker callback). TODO: incomplete; the members that
/// the constructor / setup / reset initialise are modeled (names of the unknown ones start with an underscore).
class MarkerController {
public:
    struct MarkerCallbackInfo {
        SoundSource* sound_source;
        s32 type;
        u32 id;
        const char* name;
        s32 sample_position;
        u32 duration;
        s32 offset;
        bool initial;
    };
    static_assert(sizeof(MarkerCallbackInfo) == 0x28, "MarkerCallbackInfo size");
    using MarkerCallback = void (*)(const MarkerCallbackInfo& info, void* user_data);

    MarkerController();

    /// 0x7100b9f8ac: also marks the sound source (a marker callback needs the playing state to be tracked).
    void setMarkerCallback(MarkerCallback callback, s32 param, void* user_data);

    /// 0x7100b9f43c: calls the marker callback for the markers that the sound has passed (arguments:
    /// the playing sample position and the number of loops).
    void calcMarker(s32 sample_position, s32 loop_count);
    s32 getMarkerSamplePos(const sead::SafeString& name) const;

    void setup(SoundSource* sound_source);
    void reset();

private:
    void checkMarkerInfo_(const MarkerInfo& info, s32 previous_position, s32 position,
                          const AssetInfo::LoopInfo& loop_info, bool initial);

    SoundSource* mSoundSource;
    const MarkerInfo* _8;
    MarkerCallback mCallback;
    s32 mCallbackParam;
    void* mCallbackUserData;
    s32 _28;
    s32 _2c;
};
static_assert(sizeof(MarkerController) == 0x30, "aal::MarkerController size mismatch");

}  // namespace aal
