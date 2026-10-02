#include "Game/AI/AI/aiCameraTool.h"

namespace uking::ai {

CameraTool::CameraTool(const InitArg& arg) : CameraAI(arg) {}

CameraTool::~CameraTool() = default;

bool CameraTool::m34(sead::Heap* heap) {
    mFlags.set(Flag::Changeable);
    return true;
}

void CameraTool::m35(ksys::act::ai::InlineParamPack* params) {
    _48.sub_7100791B88();
    _b8 = 0;
}

}  // namespace uking::ai
