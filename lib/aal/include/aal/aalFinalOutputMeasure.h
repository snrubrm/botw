#pragma once

#include <basis/seadTypes.h>
#include "aal/aalDeviceType.h"
#include "aal/aalSpeakerChannel.h"

namespace sead {
class DrawContext;
class Heap;
class TextWriter;
}  // namespace sead

namespace aal {

/// Measures the final output of a device. TODO: incomplete.
class FinalOutputMeasure {
public:
    struct InitializeArg {
        f32 _0;
    };

    explicit FinalOutputMeasure(DeviceType device);
    virtual ~FinalOutputMeasure();

    void initialize(const InitializeArg& arg, sead::Heap* heap);
    void finalize();
    void calc();
    void drawInformation(sead::DrawContext* context, sead::TextWriter* writer) const;
    /// Starts measuring (the measure is active only while something wants to see it).
    void activate();
    /// The VU value (the average level) of the channel.
    f32 getVU(SpeakerChannel channel) const;
    /// The sample peak of the channel in dB (-100 if the channel is silent).
    f32 getSamplePeak(SpeakerChannel channel) const;

private:
    /// 0x7100baa27c (declared only)
    void updateActivation();
    /// The different layouts of the information that drawInformation draws (declared only).
    void drawInformationSimple_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationSimpleStereo_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationSimpleSurround_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationFull_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalSimple_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalStereo_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalSurround_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalSimpleLFE_(sead::DrawContext* context, sead::TextWriter* writer) const;

    u8 _8[0x37 - 8];
    bool mIsActive;
    u8 _38[0xf4 - 0x38];
    f32 mVU[6];
    f32 mSamplePeak[6];
    u8 _124[0x160 - 0x124];
    s32 mDisplayMode;
    u8 _164[0x218 - 0x164];
};
static_assert(sizeof(FinalOutputMeasure) == 0x218, "aal::FinalOutputMeasure size mismatch");

}  // namespace aal
