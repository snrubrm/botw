#include "Game/AI/AI/aiCameraAI.h"

namespace uking::ai {

CameraAI::CameraAI(const InitArg& arg) : ksys::act::ai::Ai(arg), Unk_7102459708(this) {}

bool CameraAI::init_(sead::Heap* heap) {
    mFlags.set(Flag::Changeable);
    return m34(heap);
}

void CameraAI::enter_(ksys::act::ai::InlineParamPack* params) {
    m35(params);
}

void CameraAI::calc_() {
    m36();
}

void CameraAI::leave_() {
    m37();
}

void CameraAI::loadParams_() {
    m38();
}

}  // namespace uking::ai
