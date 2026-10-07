#include "Game/AI/aiUnk_7102433970.h"

// 0x7100744200: switches to `mode` (unless one is already set and `force` is false). Mode 1 restarts the timer
// `_e0` at 90 (or keeps its current value if that is larger) with the default rate.
void Unk_7100743798::sub_7100744200(s32 mode, bool force) {
    if (_0 != -1 && !force)
        return;
    f32 value = mode == 1 ? 90.0f : 0.0f;
    _0 = mode;
    if (mode != 1)
        return;
    value = value > _e0.value ? value : _e0.value;
    _e0 = ksys::Timer(value, value);
}
