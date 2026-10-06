#pragma once

#include <basis/seadTypes.h>
#include "aal/aalFadeCurveType.h"
#include "aal/aalAssetInfo.h"

namespace nn::atk {
enum StreamRegionCallbackResult : int;
struct StreamRegionCallbackParam;
}  // namespace nn::atk

namespace aal {

/// Controls the nn::atk sound of a SoundSource. TODO: only the members SoundSource forwards to are declared.
class SoundController {
public:
    using StreamRegionCallback =
        nn::atk::StreamRegionCallbackResult (*)(nn::atk::StreamRegionCallbackParam*, void*);

    /// 0x7100ba1d64 / 0x7100ba2058 / 0x7100ba2060 / 0x7100ba2068 / 0x7100ba2070 (declared only)
    void startPrepared();
    void setFadeCurveType(FadeCurveType type);
    void setStartSampleOffset(u32 offset);
    void setStreamRegionCallback(StreamRegionCallback callback, void* user_data);
    void setIgnorePrefetch(bool ignore);

    u8 _0[0x30];
    const AssetInfo* mAssetInfo;
};

/// The playing state of a SoundSource (SoundSource +0x100). TODO: only the controller pointer is modeled.
class PlayingStateController {
public:
    u8 _0[8];
    SoundController* mSoundController;
};

}  // namespace aal
