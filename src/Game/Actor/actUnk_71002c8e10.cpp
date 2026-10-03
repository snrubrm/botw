#include "Game/Actor/actMotorcycleStickControl.h"

namespace uking::act {

Unk_71002c8e10::Unk_71002c8e10(f32 a, f32 b, bool flag) {
    const f32 first = a > 0.0f ? a : 0.008f;
    _4 = first;
    const f32 second = b > 0.0f ? b : 0.008f;
    _8 = second;
    _0 = flag ? second : -first;
}

}  // namespace uking::act
