#include "Game/AI/Action/actionMoveWithAS.h"

namespace uking::action {

MoveWithAS::MoveWithAS(const InitArg& arg) : MoveBase(arg) {}

MoveWithAS::~MoveWithAS() = default;

bool MoveWithAS::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void MoveWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void MoveWithAS::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
