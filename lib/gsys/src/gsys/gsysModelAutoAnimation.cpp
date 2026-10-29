#include "gsys/gsysModelAutoAnimation.h"

namespace gsys {

ModelAutoAnimation::InitArg::InitArg() = default;

// 0x7100bfffd8
ModelAutoAnimation::ModelAutoAnimation() {}

// 0x7100c00718
void ModelAutoAnimation::forceUpdate() {
    update_(mModel, 0.0f);
}

}  // namespace gsys
