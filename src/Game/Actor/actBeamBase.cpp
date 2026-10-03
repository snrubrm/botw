#include "Game/Actor/actBeamBase.h"

namespace uking::act {

// NON_MATCHING: the stores of _c58 (the original writes 8 + 4 bytes, we write 4 + 8) and of _c80 / _c84
// (the original keeps two separate word stores)
BeamBase::BeamBase(const CreateArg& arg) : DynamicActor(arg) {
    _b90._40.reset();
    _b90._50.getKey().reset();
}

// NON_MATCHING: the original computes &_b90 and &_b90._40 into callee-saved registers before the inlined
// ~BoneAccessKeyEx call; we recompute them after it
BeamBase::~BeamBase() = default;

void BeamBase::m165(sead::Vector3f* out) {
    mMtx.getTranslation(*out);
}

}  // namespace uking::act
