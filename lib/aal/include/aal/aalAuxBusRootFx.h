#pragma once

#include <aal/aalDeviceType.h>
#include <aal/aalMemoryPool.h>
#include <aal/aalWorkerThread.h>
#include <hostio/seadHostIONode.h>
#include <nn/atk/EffectAux.h>
#include <nn/atk/SampleFormat.h>
#include <thread/seadMutex.h>

namespace aal {
class AuxBusCtrl;
class AuxBusDataCtrl;

// Partial model: only the bases and fields used by clearAuxBusDataCtrl are exposed.
// Constructor, destructor and the other virtual method bodies remain undecompiled.
class AuxBusRootFx : public nn::atk::EffectAux, public WorkerTask, public sead::hostio::Node {
public:
    AuxBusRootFx(BusType bus, DeviceType device);
    ~AuxBusRootFx() override;

    bool Initialize() override;
    void Finalize() override;
    void OnChangeOutputMode() override;
    void UpdateSamples(s32* samples, const UpdateSamplesArg& arg) override;
    virtual void UpdateBuffer(s32 channels, void** buffers, size_t samples,
                              nn::atk::SampleFormat format, f32 sample_rate,
                              nn::atk::OutputMode mode);
    void workerThreadProc_(bool is_quitting) override;

    void clearAuxBusDataCtrl();
    void setAuxBusDataCtrl(AuxBusDataCtrl* control);

private:
    u8 _78[0xb8 - 0x78];
    BusType mBus;
    DeviceType mDevice;
    AuxBusCtrl* mOwner;
    AuxBusDataCtrl* mCurrent;
    bool mHasPending;
    u8 _d1[7];
    AuxBusDataCtrl* mPending;
    sead::Mutex mMutex;
    u8 _120[0x138 - 0x120];
    MemoryPool mMemoryPool;
    u8 _1a0[0x1b0 - 0x1a0];
};
static_assert(sizeof(AuxBusRootFx) == 0x1b0, "AuxBusRootFx size mismatch");
}  // namespace aal
