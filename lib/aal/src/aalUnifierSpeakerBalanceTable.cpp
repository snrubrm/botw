#include "aal/aalSpeakerBalanceUnifierMgr.h"
#include <basis/seadNew.h>
#include "aal/aalOutputDevice.h"
#include "aal/aalSettings.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b946d4
UnifierSpeakerBalanceTable::UnifierSpeakerBalanceTable() : mData(nullptr) {}

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
    if (mInteriorMaxSpread) {
        delete[] mInteriorMaxSpread;
        mInteriorMaxSpread = nullptr;
    }
}

// 0x7100b94738
void UnifierSpeakerBalanceTable::initialize(sead::Heap* heap) {
    mData = new (heap, 8) UnifierSpeakerBalanceData*[DeviceType::size()];
    s32 num = 1;
    if (OutputDevice* device = SystemAccessor::getSettings()->getOutputDevice(DeviceType::TV))
        num = device->getNumOfInteriorMax();
    mData[0] = new (heap, 8) UnifierSpeakerBalanceData[num];
    mInteriorMaxSpread = new (heap, 8) f32[num];
    mInteriorNum = num;
    makeTable();
}

}  // namespace aal
