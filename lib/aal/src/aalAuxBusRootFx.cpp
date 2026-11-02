#include "aal/aalAuxBusRootFx.h"

#include <nn/atk/SoundSystem.h>
#include "aal/aalAuxBusDataCtrl.h"

namespace aal {

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

}  // namespace aal
