#include "aal/aalFinalOutputMeasure.h"
#include <math/seadMathCalcCommon.h>

namespace aal {

namespace {
// The position of the channel in the arrays of the measure.
s32 getChannelIndex(SpeakerChannel channel) {
    switch (s32(channel)) {
    case 0:
        return 1;
    case 1:
        return 0;
    case 2:
        return 5;
    case 3:
        return 4;
    case 4:
        return 2;
    case 5:
        return 3;
    default:
        return 0;
    }
}
}  // namespace

// 0x7100baa514
void FinalOutputMeasure::activate() {
    mIsActive = true;
    updateActivation();
}

// 0x7100baa520
f32 FinalOutputMeasure::getVU(SpeakerChannel channel) const {
    return mVU[getChannelIndex(channel)];
}

// 0x7100baa558
f32 FinalOutputMeasure::getSamplePeak(SpeakerChannel channel) const {
    const f32 peak = mSamplePeak[getChannelIndex(channel)];
    if (peak == 0.0f)
        return -100.0f;
    return sead::Mathf::logTable(peak) * 8.685889f;
}

// 0x7100bab198
void FinalOutputMeasure::drawInformation(sead::DrawContext* context, sead::TextWriter* writer) const {
    switch (mDisplayMode) {
    case 1:
        drawInformationSimple_(context, writer);
        break;
    case 2:
        drawInformationSimpleStereo_(context, writer);
        break;
    case 3:
        drawInformationSimpleSurround_(context, writer);
        break;
    case 4:
    case 5:
        drawInformationFull_(context, writer);
        break;
    case 6:
        drawInformationVerticalSimple_(context, writer);
        break;
    case 7:
        drawInformationVerticalStereo_(context, writer);
        break;
    case 8:
        drawInformationVerticalSurround_(context, writer);
        break;
    case 9:
        drawInformationVerticalSimpleLFE_(context, writer);
        break;
    default:
        break;
    }
}

}  // namespace aal
