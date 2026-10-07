#pragma once

#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>
#include "aal/aalDeviceType.h"
#include "aal/aalFinalOutputMeasure.h"
#include "aal/aalOutputMode.h"
#include "aal/aalSpeakerChannel.h"

namespace sead {
class DrawContext;
class Heap;
class TextWriter;
}  // namespace sead

namespace aal {

class FinalFxCtrl;
class Interior;
class InteriorSet;
class VirtualSurroundCtrl;
enum class InteriorType : u32;

/// An audio output device: owns the interior sets of the speaker setups it supports.
class OutputDevice : public sead::hostio::Node {
public:
    virtual VirtualSurroundCtrl* getVirtualSurroundCtrl() const;
    virtual FinalFxCtrl* getFinalFxCtrl() const;
    virtual FinalOutputMeasure* getFinalOutputMeasure() const;
    virtual ~OutputDevice();
    virtual void calc();
    virtual void drawInformation(sead::DrawContext* context, sead::TextWriter* writer) const;

    void initializeInterior(const sead::Buffer<InteriorType>& stereo_types,
                            const sead::Buffer<InteriorType>& surround_types, sead::Heap* heap);
    void changeInterior(OutputMode mode);
    Interior* getCurrentInterior(s32 index) const;
    s32 getSpeakerChannelAngleIdx(SpeakerChannel channel, s32 index) const;
    void setInteriorSize(f32 size);
    s32 getNumOfInteriorMax() const;
    InteriorSet* getCurrentInteriorSet() const { return mCurrentInterior; }
    f32 get_20() const { return _20; }

protected:
    InteriorSet* mCurrentInterior = nullptr;
    InteriorSet* mSurroundInteriorSet = nullptr;
    InteriorSet* mStereoInteriorSet = nullptr;
    f32 _20 = 1.0f;
};
static_assert(sizeof(OutputDevice) == 0x28, "aal::OutputDevice size mismatch");

/// An output device with speakers (the TV).
class OutputDeviceMultiSpeaker : public OutputDevice {
public:
    OutputDeviceMultiSpeaker();
    ~OutputDeviceMultiSpeaker() override;

    FinalFxCtrl* getFinalFxCtrl() const override;
    FinalOutputMeasure* getFinalOutputMeasure() const override;
    void calc() override;
    void drawInformation(sead::DrawContext* context, sead::TextWriter* writer) const override;

    void initializeFinalFxCtrl(DeviceType device, sead::Heap* heap);
    void initializeFinalOutputMeasure(DeviceType device, FinalOutputMeasure::InitializeArg arg,
                                      sead::Heap* heap);

private:
    FinalFxCtrl* mFinalFxCtrl = nullptr;
    FinalOutputMeasure* mFinalOutputMeasure = nullptr;
};
static_assert(sizeof(OutputDeviceMultiSpeaker) == 0x38, "aal::OutputDeviceMultiSpeaker size mismatch");

}  // namespace aal
