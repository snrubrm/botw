#include "Game/AI/AI/aiNPCReturnAnchor.h"

namespace uking::ai {

NPCReturnAnchor::NPCReturnAnchor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCReturnAnchor::~NPCReturnAnchor() = default;

bool NPCReturnAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCReturnAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCReturnAnchor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCReturnAnchor::loadParams_() {}

void NPCReturnAnchor::calc_() {
    if (isCurrentChild("振り向く")) {
        if (getCurrentChild()->isFinished())
            sub_71004D6E7C();
    } else if (isCurrentChild("姿勢変更")) {
        if (getCurrentChild()->isFinished()) {
            sub_71004D70D8();
            setFinished();
        }
    }
}

}  // namespace uking::ai
