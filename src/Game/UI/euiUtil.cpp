#include "Game/UI/euiTypes.h"

namespace eui {

// 0x7100bed2bc
f32 GetRadAngleOfDirection(Direction direction) {
    switch (int(direction.value())) {
    case 0:
        return 1.5707964f;
    case 1:
        return 4.712389f;
    case 2:
        return 3.1415927f;
    default:
        return 0.0f;
    }
}

}  // namespace eui
