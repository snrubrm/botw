#include "aal/aalOutputDevice.h"
#include <math/seadMathCalcCommon.h>
#include "aal/aalFinalFxCtrl.h"
#include "aal/aalInterior.h"
#include "aal/aalInteriorSet.h"

namespace aal {

// 0x7100b86234
VirtualSurroundCtrl* OutputDevice::getVirtualSurroundCtrl() const {
    return nullptr;
}

// 0x7100b8623c
FinalFxCtrl* OutputDevice::getFinalFxCtrl() const {
    return nullptr;
}

// 0x7100b86244
FinalOutputMeasure* OutputDevice::getFinalOutputMeasure() const {
    return nullptr;
}

// 0x7100b85d5c (D1) / 0x7100b85db8 (D0)
OutputDevice::~OutputDevice() {
    if (mSurroundInteriorSet) {
        delete mSurroundInteriorSet;
        mSurroundInteriorSet = nullptr;
    }
    if (mStereoInteriorSet) {
        delete mStereoInteriorSet;
        mStereoInteriorSet = nullptr;
    }
}

// 0x7100b8624c
void OutputDevice::calc() {}

// 0x7100b86250
void OutputDevice::drawInformation(sead::DrawContext*, sead::TextWriter*) const {}

// 0x7100b85e14
void OutputDevice::initializeInterior(const sead::Buffer<InteriorType>& stereo_types,
                                      const sead::Buffer<InteriorType>& surround_types,
                                      sead::Heap* heap) {
    mStereoInteriorSet = new (heap) InteriorSet;
    mStereoInteriorSet->initialize(stereo_types, heap);
    mSurroundInteriorSet = new (heap) InteriorSet;
    mSurroundInteriorSet->initialize(surround_types, heap);
}

// 0x7100b85ea0
// NON_MATCHING: the original compares the mode against 2, 1 and finally 0 (here the zero case is tested first).
void OutputDevice::changeInterior(OutputMode mode) {
    switch (mode) {
    case OutputMode::Surround:
        mCurrentInterior = mSurroundInteriorSet;
        break;
    case OutputMode::Stereo:
        mCurrentInterior = mStereoInteriorSet;
        break;
    case OutputMode::Mono:
        mCurrentInterior = nullptr;
        break;
    }
}

// 0x7100b85ee8
Interior* OutputDevice::getCurrentInterior(s32 index) const {
    if (!mCurrentInterior)
        return nullptr;
    return mCurrentInterior->getInterior(index);
}

// 0x7100b85ef8
void OutputDevice::setInteriorSize(f32 size) {
    if (size > 0.0f) {
        if (mSurroundInteriorSet)
            mSurroundInteriorSet->setInteriorSize(size);
        if (mStereoInteriorSet)
            mStereoInteriorSet->setInteriorSize(size);
    }
}

// 0x7100b85f98
s32 OutputDevice::getNumOfInteriorMax() const {
    s32 num = 0;
    if (mSurroundInteriorSet)
        num = sead::Mathi::max(mSurroundInteriorSet->getNumOfInterior(), 0);
    if (mStereoInteriorSet)
        num = sead::Mathi::max(num, mStereoInteriorSet->getNumOfInterior());
    return num;
}

// 0x7100b85fec
OutputDeviceMultiSpeaker::OutputDeviceMultiSpeaker() = default;

// 0x7100b86010 (D1) / 0x7100b860b8 (D0)
OutputDeviceMultiSpeaker::~OutputDeviceMultiSpeaker() {
    if (mFinalFxCtrl) {
        delete mFinalFxCtrl;
        mFinalFxCtrl = nullptr;
    }
    if (mFinalOutputMeasure) {
        mFinalOutputMeasure->finalize();
        delete mFinalOutputMeasure;
        mFinalOutputMeasure = nullptr;
    }
}

// 0x7100b86254
FinalFxCtrl* OutputDeviceMultiSpeaker::getFinalFxCtrl() const {
    return mFinalFxCtrl;
}

// 0x7100b8625c
FinalOutputMeasure* OutputDeviceMultiSpeaker::getFinalOutputMeasure() const {
    return mFinalOutputMeasure;
}

// 0x7100b86160
void OutputDeviceMultiSpeaker::calc() {
    if (mFinalOutputMeasure)
        mFinalOutputMeasure->calc();
}

// 0x7100b86224
void OutputDeviceMultiSpeaker::drawInformation(sead::DrawContext* context,
                                               sead::TextWriter* writer) const {
    if (mFinalOutputMeasure)
        mFinalOutputMeasure->drawInformation(context, writer);
}

// 0x7100b86170
void OutputDeviceMultiSpeaker::initializeFinalFxCtrl(DeviceType device, sead::Heap* heap) {
    mFinalFxCtrl = new (heap) FinalFxCtrl(device);
}

// 0x7100b861bc
void OutputDeviceMultiSpeaker::initializeFinalOutputMeasure(
    DeviceType device, FinalOutputMeasure::InitializeArg arg, sead::Heap* heap) {
    mFinalOutputMeasure = new (heap) FinalOutputMeasure(device);
    mFinalOutputMeasure->initialize(arg, heap);
}

// 0x7100b85f54
s32 OutputDevice::getSpeakerChannelAngleIdx(SpeakerChannel channel, s32 index) const {
    if (mCurrentInterior) {
        if (Interior* interior = mCurrentInterior->getInterior(index))
            return interior->getSpeakerChannelAngleIdx(channel);
    }
    return 0;
}

}  // namespace aal
