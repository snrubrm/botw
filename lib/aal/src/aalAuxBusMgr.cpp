#include "aal/aalAuxBusMgr.h"

namespace aal {

// NON_MATCHING: null return block duplication and enum argument evaluation order differ.
AuxBusCtrl* AuxBusMgr::getAuxBusCtrl(BusType bus, DeviceType device) const {
    if (bus == BusType::Main || !mAuxBusCtrls)
        return nullptr;
    if (device >= DeviceType::size())
        return nullptr;
    return mAuxBusCtrls[device][bus - 1];
}


AuxBusMgr* AuxBusMgr::sInstance = nullptr;

// 0x7100b7a998
f32 AuxBusMgr::getAudioFrameTime() const {
    return 0.005f;
}

// 0x7100b7a9a4
void AuxBusMgr::setEnvFxSend(f32 min_send, f32 max_send, f32 time) {
    if (max_send < 0.0f)
        max_send = min_send;
    mMinEnvFxSendFader.moveTo(min_send, time);
    mMinEnvFxSendTarget = min_send;
    mMaxEnvFxSendFader.moveTo(max_send, time);
    mMaxEnvFxSendTarget = max_send;
}

// 0x7100b7aa04
f32 AuxBusMgr::getMinEnvFxSend() const {
    return mMinEnvFxSendFader.getValue();
}

// 0x7100b7aa0c
f32 AuxBusMgr::getMaxEnvFxSend() const {
    return mMaxEnvFxSendFader.getValue();
}

}  // namespace aal
