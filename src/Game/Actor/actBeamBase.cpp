#include "Game/Actor/actBeamBase.h"
#include <prim/seadScopedLock.h>

namespace uking::act {

BeamBase::BeamBase(const CreateArg& arg) : DynamicActor(arg) {
    _b90._40.reset();
    _be0.getKey().reset();
}

// NON_MATCHING: the original computes &_b90 and &_b90._40 into callee-saved registers before the inlined
// ~BoneAccessKeyEx call; we recompute them after it
BeamBase::~BeamBase() = default;

void BeamBase::sub_7100003804(ksys::act::Actor* shooter, const sead::SafeString& bone) {
    auto lock = sead::makeScopedLock(_b90._0);
    _b90._40.acquire(shooter, false);
    if (auto* model = shooter->getModel())
        _be0.search(model, bone);
}

void BeamBase::sub_710000395C(ksys::act::Actor* shooter, const sead::SafeString& bone,
                               const sead::Vector3f* offset) {
    auto lock = sead::makeScopedLock(_b90._0);
    _b90._40.acquire(shooter, false);
    if (auto* model = shooter->getModel())
        _be0.search(model, bone);
    _c18 = *offset;
}

void BeamBase::m165(sead::Vector3f* out) {
    mMtx.getTranslation(*out);
}

}  // namespace uking::act
