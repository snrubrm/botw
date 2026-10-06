#include "aal/aalMeter.h"
#include "aal/aalSettings.h"
#include "aal/aalSystem.h"

namespace aal {

// 0x7100b7c8ac
f32 Meter::toLength(f32 meter) {
    return System::sInstance->mSettings->mLengthPerMeter * meter;
}

// 0x7100b7c8c8
f32 Meter::toMeter(f32 length) {
    return length / System::sInstance->mSettings->mLengthPerMeter;
}

// 0x7100b7c8e4
sead::Vector3f Meter::toLength(const sead::Vector3f& meter) {
    const f32 x = meter.x;
    const f32 y = meter.y;
    const f32 z = meter.z;
    const f32 scale = System::sInstance->mSettings->mLengthPerMeter;
    return {x * scale, scale * y, z * scale};
}

}  // namespace aal
