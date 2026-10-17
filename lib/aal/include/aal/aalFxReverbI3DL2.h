#pragma once

#include <basis/seadTypes.h>

#include "aal/aalAuxBusDataSerialCtrl.h"

namespace aal {

// Ctor 0x7101051b04 constructs the base at +0x88, clears the fields to +0xd0 and
// zeroes the 0xb0-byte parameter block at +0xd8; the whole object is 0x188 bytes
// (FxMgr::init allocates that size). Slots 11 / 12 are initialize / updateParam
// (0x7101051ef0 / 0x7101052bf4).
class FxReverbI3DL2 : public AuxBusDataSerialCtrl {
    SEAD_RTTI_OVERRIDE(FxReverbI3DL2, AuxBusDataSerialCtrl)
public:
    FxReverbI3DL2();
    ~FxReverbI3DL2() override;

    void initialize(const FxInitializeArg& arg, const FxParamSetter& setter,
                    sead::Heap* heap) override;
    void updateParam(const FxParamSetter& setter) override;

private:
    // The fields between +0x88 and +0x188 are not modelled yet.
    u8 _88[0x188 - 0x88];
};
static_assert(sizeof(FxReverbI3DL2) == 0x188, "aal::FxReverbI3DL2 size mismatch");

}  // namespace aal
