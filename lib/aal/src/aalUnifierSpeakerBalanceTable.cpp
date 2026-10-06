#include "aal/aalSpeakerBalanceUnifierMgr.h"
#include <basis/seadNew.h>
#include "aal/aalOutputDevice.h"
#include "aal/aalSettings.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b946d4
UnifierSpeakerBalanceTable::UnifierSpeakerBalanceTable() : mData(nullptr) {}

// 0x7100b95630
f32 UnifierSpeakerBalanceTable::getTotalVolumeMax(DeviceType device, s32 interior) const {
    return mTotalVolumeMax[device][interior];
}

// 0x7100b95524
void UnifierSpeakerBalanceTable::getSpeakerBalanceU8Range(SpeakerChannelVolume* volume, s32 angle, DeviceType device,
                                                          s32 interior) const {
    const UnifierSpeakerBalanceData::ChannelBalance& balance = mData[device][interior].mBalance[0][angle];
    for (s32 i = 0; i < 5; ++i)
        volume->volume[i] = balance[i];
}

// 0x7100b95598
void UnifierSpeakerBalanceTable::getSpeakerBalanceU8RangeWithSpread(SpeakerChannelVolume* volume, s32 angle,
                                                                    DeviceType device, s32 interior, f32 spread) const {
    const s32 spread_index = static_cast<s32>(spread * 47.0f);
    const UnifierSpeakerBalanceData::ChannelBalance& balance =
        mData[device][interior].mBalance[spread_index][angle];
    for (s32 i = 0; i < 5; ++i)
        volume->volume[i] = balance[i];
}

// 0x7100b946dc
UnifierSpeakerBalanceTable::~UnifierSpeakerBalanceTable() {
    if (mData) {
        if (mData[0]) {
            delete[] mData[0];
            mData[0] = nullptr;
        }
        delete[] mData;
        mData = nullptr;
    }
    if (mTotalVolumeMax[0]) {
        delete[] mTotalVolumeMax[0];
        mTotalVolumeMax[0] = nullptr;
    }
}

// 0x7100b94738
void UnifierSpeakerBalanceTable::initialize(sead::Heap* heap) {
    mData = new (heap, 8) UnifierSpeakerBalanceData*[DeviceType::size()];
    s32 num = 1;
    if (OutputDevice* device = SystemAccessor::getSettings()->getOutputDevice(DeviceType::TV))
        num = device->getNumOfInteriorMax();
    mData[0] = new (heap, 8) UnifierSpeakerBalanceData[num];
    mTotalVolumeMax[0] = new (heap, 8) f32[num];
    mInteriorNum = num;
    makeTable();
}

}  // namespace aal
