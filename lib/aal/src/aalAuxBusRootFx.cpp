#include "aal/aalAuxBusRootFx.h"

#include <nn/atk/SoundSystem.h>
#include "aal/aalAuxBusDataCtrl.h"

namespace aal {

// 0x7100b7be80
void AuxBusRootFx::OnChangeOutputMode() {}

// NON_MATCHING: bus conversion lowers differently and the native discards a device read.
// 0x7100b7b110
void AuxBusRootFx::clearAuxBusDataCtrl() {
    mMutex.lock();
    mHasPending = false;
    mPending = nullptr;
    mMutex.unlock();

    if (mCurrent)
        mCurrent->execOnBusDisconnect();

    nn::atk::AuxBus bus = nn::atk::AuxBus_A;
    switch (mBus) {
    case BusType::AuxB:
        bus = nn::atk::AuxBus_B;
        break;
    case BusType::AuxC:
        bus = nn::atk::AuxBus_C;
        break;
    default:
        break;
    }
    if (!nn::atk::SoundSystem::IsClearEffectFinished(bus, nn::atk::OutputDevice_Main)) {
        SetEnabled(false);
        mCurrent = nullptr;
    }
}

// NON_MATCHING: bus conversion and tail-call lowering differ; the native discards a device read.
// 0x7100b7b18c
void AuxBusRootFx::setAuxBusDataCtrl(AuxBusDataCtrl* control) {
    if (!control) {
        clearAuxBusDataCtrl();
        return;
    }

    control->mState = 1;
    nn::atk::AuxBus bus = nn::atk::AuxBus_A;
    switch (mBus) {
    case BusType::AuxB: bus = nn::atk::AuxBus_B; break;
    case BusType::AuxC: bus = nn::atk::AuxBus_C; break;
    default: break;
    }
    if (!nn::atk::SoundSystem::IsClearEffectFinished(bus, nn::atk::OutputDevice_Main)) {
        mMutex.lock();
        mHasPending = true;
        mPending = control;
        mMutex.unlock();
        return;
    }
    if (mCurrent)
        mCurrent->execOnBusDisconnect();
    mCurrent = control;
    const BusType bus_type = mBus;
    SetEnabled(true);
    if (mIsFinalMix) {
        nn::atk::SoundSystem::AppendEffectToFinalMix(this, mEffectBuffer, mEffectBufferSize);
    } else {
        nn::atk::AuxBus append_bus = nn::atk::AuxBus_A;
        switch (bus_type) {
        case BusType::AuxB: append_bus = nn::atk::AuxBus_B; break;
        case BusType::AuxC: append_bus = nn::atk::AuxBus_C; break;
        default: break;
        }
        nn::atk::SoundSystem::AppendEffect(append_bus, this, mEffectBuffer, mEffectBufferSize);
    }
}

}  // namespace aal
