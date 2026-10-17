#pragma once

#include <basis/seadTypes.h>

#include "aal/aalAuxBusDataSerialCtrl.h"
#include "aal/aalFxReverbI3DL2.h"

namespace aal {

// Ctor 0x71012cc088 constructs AuxBusDataSerialCtrl directly at +0x88 (it does not
// construct FxReverbI3DL2); the object is 0x100 bytes. Its typeinfo nevertheless names
// FxReverbI3DL2 as the parent (SEAD_RTTI_OVERRIDE in the original). Slots 11 / 12 are
// initialize / updateParam (0x71012cc1f0 / 0x71012cc4d4).
class FxDelay : public AuxBusDataSerialCtrl {
    SEAD_RTTI_OVERRIDE(FxDelay, FxReverbI3DL2)
public:
    FxDelay();
    ~FxDelay() override;

    void initialize(const FxInitializeArg& arg, const FxParamSetter& setter,
                    sead::Heap* heap) override;
    void updateParam(const FxParamSetter& setter) override;

private:
    // The fields between +0x88 and +0x100 are not modelled yet.
    u8 _88[0x100 - 0x88];
};
static_assert(sizeof(FxDelay) == 0x100, "aal::FxDelay size mismatch");

}  // namespace aal
