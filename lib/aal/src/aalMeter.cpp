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

// NON_MATCHING: the middle multiply's commutative operand order differs (target
// fmul s1, s3, s1; ours fmul s1, s1, s3), as in other commutative rows.
// 0x7100b7c8e4
sead::Vector3f Meter::toLength(const sead::Vector3f& meter) {
    sead::Vector3f length = meter;
    length.x = toLength(length.x);
    length.y = toLength(length.y);
    length.z = toLength(length.z);
    return length;
}

}  // namespace aal
