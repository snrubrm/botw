#pragma once

#include <math/seadVector.h>
#include "aal/aalIUnifiable.h"

namespace aal {

/// A fixed position to unify (see SoundSourceUnifierSource).
class UnifiablePosition : public IUnifiable {
public:
    ~UnifiablePosition() override = default;

    bool calcUnifiablePositions(const Listener& listener, sead::Vector3f* a,
                                sead::Vector3f* b) override;

    sead::Vector3f mPosition;
};
static_assert(sizeof(UnifiablePosition) == 0x38, "aal::UnifiablePosition size mismatch");

}  // namespace aal
