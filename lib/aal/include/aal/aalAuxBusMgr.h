#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "aal/aalDeviceType.h"
#include "aal/aalTimedFader.h"

namespace aal {

class AuxBusCtrl {
public:
    // 0x7100ba2734 (U): the per-bus work of one auxiliary bus. Called by AuxBusMgr::calc and by
    // 0x7100b7a8d4's neighbours; declaration only.
    void calc();
};

/// Manages the auxiliary buses (the environment effect send). TODO: incomplete: the singleton and everything
/// before offset 0x48 are not modeled.
class AuxBusMgr {
public:
    // The native singleton disposer has its own complete two-slot lifetime table.
    // Its embedded storage remains in the opaque interval below.
    class SingletonDisposer_ : public sead::IDisposer {
    public:
        using sead::IDisposer::IDisposer;
        ~SingletonDisposer_() override;
        static SingletonDisposer_* sStaticDisposer;
    };

    ~AuxBusMgr();
    static void deleteInstance();
    static AuxBusMgr* sInstance;

    // 0x7100b7a8d4: per-frame work of the auxiliary buses and the two environment-send faders.
    void calc();
    /// The duration of one audio frame in seconds.
    f32 getAudioFrameTime() const;
    AuxBusCtrl* getAuxBusCtrl(BusType bus, DeviceType device) const;
    f32 getMinEnvFxSend() const;
    f32 getMaxEnvFxSend() const;
    BusType getEnvFxBus() const { return mEnvFxBus; }
    /// Moves the environment effect send range to [min_send, max_send] in `time` seconds (a negative maximum
    /// means the same as the minimum).
    void setEnvFxSend(f32 min_send, f32 max_send, f32 time);

private:
    u8 _0[0x28];
    AuxBusCtrl*** mAuxBusCtrls;
    // calc (0x7100b7a8d4) calls calc on this pointer when it is non-null; its owner is not otherwise
    // modelled, so the name keeps the offset.
    AuxBusCtrl* _30;
    u8 _38[0x40 - 0x38];
    /// The bus that the environment effect is sent to.
    BusType mEnvFxBus;
    u8 _44[0x48 - 0x44];
    SimpleTimedFader mMinEnvFxSendFader;
    SimpleTimedFader mMaxEnvFxSendFader;
    f32 mMinEnvFxSendTarget;
    f32 mMaxEnvFxSendTarget;
};

}  // namespace aal
