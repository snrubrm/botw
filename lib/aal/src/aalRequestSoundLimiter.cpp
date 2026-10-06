#include "aal/aalRequestSoundLimiter.h"

namespace aal {

// 0x7100b83720
RequestSoundLimiter::RequestSoundLimiter() = default;

// 0x7100b8374c
void RequestSoundLimiter::setup(const Settings& settings) {
    mSettings = settings;
    if (mSettings.mField1 < 0)
        mSettings.mField1 = 0;
    if (mSettings.mField2 < 0.0f)
        mSettings.mField2 = 0.0f;
    if (!(mSettings.mField3 >= 0.0f && mSettings.mField3 <= 1.0f))
        mSettings.mField3 = 1.0f;
    if (!(mSettings.mField4 >= 0.0f && mSettings.mField4 <= 1.0f))
        mSettings.mField4 = 1.0f;
}

}  // namespace aal
