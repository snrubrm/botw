#include "gsys/gsysModelAutoAnimation.h"

namespace gsys {

// 0x7100c00718
void ModelAutoAnimation::forceUpdate() {
    update_(mModel, 0.0f);
}

}  // namespace gsys
