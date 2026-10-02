#include "Game/AI/AI/aiPipeDrawing.h"

namespace uking::ai {

PipeDrawing::PipeDrawing(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PipeDrawing::~PipeDrawing() = default;

bool PipeDrawing::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PipeDrawing::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004F6298();
}

void PipeDrawing::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PipeDrawing::loadParams_() {}

}  // namespace uking::ai
