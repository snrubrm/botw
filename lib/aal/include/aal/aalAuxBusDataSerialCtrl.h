#pragma once

#include <thread/seadMutex.h>

#include "aal/aalAuxBusDataCtrl.h"
#include "aal/aalTimedFader.h"

namespace aal {

class AuxBusDataSerialCtrl : public AuxBusDataCtrl {
    SEAD_RTTI_OVERRIDE(AuxBusDataSerialCtrl, AuxBusDataCtrl)
public:
    AuxBusDataSerialCtrl();
    ~AuxBusDataSerialCtrl() override;

    void calc() override;
    void stop(f32 time) override;
    bool execOnBusConnect() override;
    void execOnBusDisconnect() override;
    void updateBusData(int num_channels, void** buffers, int num_samples,
                       SampleFormat format, f32 sample_rate, DeviceType device) override;

protected:
    bool mIsConnected = false;
    AuxBusDataCtrl* mChild = nullptr;
    bool mHasPendingChild = false;
    AuxBusDataCtrl* mPendingChild = nullptr;
    SimpleTimedFader mStopFader;
    sead::Mutex mChildMutex;
    bool mEnabled = true;
};
// 1405d20 constructs fader +28 / Mutex +40 / enable +80. Independent
// Delay 12cc088 and Reverb 1051b04 reuse base tail padding at +81.
static_assert(sizeof(AuxBusDataSerialCtrl) == 0x88, "AuxBusDataSerialCtrl size");

}  // namespace aal
