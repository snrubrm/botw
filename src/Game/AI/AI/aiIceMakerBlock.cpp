#include "Game/AI/AI/aiIceMakerBlock.h"

namespace uking::ai {

// NON_MATCHING: the original merges the _a0-_a7 stores into one 8-byte store (ours: _a5-_a8)
IceMakerBlock::IceMakerBlock(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IceMakerBlock::~IceMakerBlock() {
    _78[0] = nullptr;
    _78[1] = nullptr;
    _88 = nullptr;
    _90 = nullptr;
    _98 = nullptr;
}

bool IceMakerBlock::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IceMakerBlock::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void IceMakerBlock::leave_() {
    ksys::act::ai::Ai::leave_();
}

void IceMakerBlock::loadParams_() {
    getStaticParam(&mSubRigidStartOffset_s, "SubRigidStartOffset");
    getStaticParam(&mSubRigidEndOffset_s, "SubRigidEndOffset");
    getStaticParam(&mSubRigidExOffset_s, "SubRigidExOffset");
}

}  // namespace uking::ai
