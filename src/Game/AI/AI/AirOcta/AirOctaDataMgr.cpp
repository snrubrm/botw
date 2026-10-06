#include "Game/AI/AI/AirOcta/AirOctaDataMgr.h"
namespace uking {

void AirOctaDataMgr::sub_71002FB340(f32 x, f32 z) {
    vec_F8.x = x;
    vec_F8.z = z;
}

void AirOctaDataMgr::changeOctasYheightMaybe() {
    float result = vec_EC.y + unk_110 + unk_114 + unk_118 + unk_11c;
    vec_F8.y = result;
}
}  // namespace uking