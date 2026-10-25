#include "Game/Actor/AI/aiAirOctaDataMgr.h"
namespace uking {

// 0x71002fb1a8 (placeholder name): copies the message's snapshot into unk_28 and marks it valid.
void AirOctaDataMgr::sub_71002FB1A8(const SubData* src) {
    sub_71002FB1D8(&unk_28, src);
    mFlags |= 4;
}

// 0x71002fb32c (placeholder name): the snapshot once the message has been copied in.
AirOctaDataMgr::SubData* AirOctaDataMgr::sub_71002FB32C() {
    return (mFlags & 4) ? &unk_28 : nullptr;
}

void AirOctaDataMgr::sub_71002FB340(f32 x, f32 z) {
    vec_F8.x = x;
    vec_F8.z = z;
}

void AirOctaDataMgr::changeOctasYheightMaybe() {
    float result = vec_EC.y + unk_110 + unk_114 + unk_118 + unk_11c;
    vec_F8.y = result;
}
}  // namespace uking