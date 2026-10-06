#include "aal/aalISpeakerBalanceSupplier.h"

namespace aal {

// 0x7100b9359c
void ISpeakerBalanceSupplier::calcSpeakerBalance(SpeakerChannelVolume* volume, DeviceType device,
                                                 s32 index_a, s32 index_b, f32 spread) {
    calcSpeakerBalance(volume, device, index_b, spread);
}

}  // namespace aal
