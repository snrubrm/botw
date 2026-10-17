#pragma once

#include <hostio/seadHostIONode.h>
#include <prim/seadRuntimeTypeInfo.h>

#include "aal/aalDeviceType.h"

namespace sead {
class DrawContext;
class TextWriter;
class Heap;
}

namespace aal {

class SampleFormat;
class FxInitializeArg;
class FxParamSetter;

// The full eleven-slot retail interface is shared by Serial 2532ee0,
// Delay 251b5c0 and Reverb 2502640. SampleFormat's class identity is known
// from native signatures, but its enumerator domain remains unresolved.
class AuxBusDataCtrl : public sead::hostio::Node {
    SEAD_RTTI_BASE(AuxBusDataCtrl)
public:
    virtual ~AuxBusDataCtrl() = default;
    virtual void calc();
    virtual void stop(f32 time);
    virtual bool execOnBusConnect();
    virtual void execOnBusDisconnect();
    virtual void updateBusData(int num_channels, void** buffers, int num_samples,
                               SampleFormat format, f32 sample_rate, DeviceType device);
    virtual void drawInformation(sead::DrawContext*, sead::TextWriter*) const;
    // Slots 11 / 12: the Serial table leaves both null (pure); the Fx effect classes
    // implement them (FxMgr::init 0x71010504fc calls slot 11, 0x7101051154 slot 12).
    virtual void initialize(const FxInitializeArg& arg, const FxParamSetter& setter,
                            sead::Heap* heap) = 0;
    virtual void updateParam(const FxParamSetter& setter) = 0;

    // Inline-only, name guessed: Serial calc 1405e90 and independent RootFx
    // calc b7b03c both read the controller state at +8 before dispatch.
    u32 getState() const { return mState; }

protected:
    u32 mState = 0;
};
static_assert(sizeof(AuxBusDataCtrl) == 0x10, "AuxBusDataCtrl size");

}  // namespace aal
