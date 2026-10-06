#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// Limits the number of sound requests (TODO: partial, the limiting calculation is not modeled).
class RequestSoundLimiter {
public:
    /// The settings as they are stored in the resource.
    struct __attribute__((packed)) Settings {
        s32 mLimitNum = -1;
        s32 mField1 = 0;
        f32 mField2 = 0.0f;
        f32 mField3 = 1.0f;
        f32 mField4 = 1.0f;
        bool mFlag = false;
    };
    static_assert(sizeof(Settings) == 0x15, "aal::RequestSoundLimiter::Settings size mismatch");

    RequestSoundLimiter();
    virtual ~RequestSoundLimiter() = default;

    /// Copies the settings; negative values and fractions that are out of range are replaced by the defaults.
    void setup(const Settings& settings);

private:
    Settings mSettings;
};

}  // namespace aal
