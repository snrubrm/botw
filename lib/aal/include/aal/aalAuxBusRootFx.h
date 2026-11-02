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
    // Partial argument model: fields are established by the native caller and initializer.
    struct CreateArg {
        u32 _0;
        u8 _4;
        u8 _5;
        u8 _6[2];
        u32 _8;
        u32 _c;
    };

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

    void initialize(const CreateArg& arg, AuxBusCtrl* owner, sead::Heap* heap);
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
    u8 mIsFinalMix;
    u8 _121[7];
    void* mEffectBuffer;
    size_t mEffectBufferSize;
    MemoryPool mMemoryPool;
    u8 _1a0[0x1b0 - 0x1a0];
};
static_assert(sizeof(AuxBusRootFx) == 0x1b0, "AuxBusRootFx size mismatch");
}  // namespace aal
