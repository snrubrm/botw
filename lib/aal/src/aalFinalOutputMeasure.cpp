#include "aal/aalFinalOutputMeasure.h"
#include "aal/aalDebugDrawer.h"
#include <gfx/seadTextWriter.h>
#include <math/seadMathCalcCommon.h>
#include <nn/atk/SoundSystem.h>
#include <nn/atk/detail/driver/HardwareManager.h>
#include "aal/aalSystem.h"

namespace aal {

// The native static initializer supplies the reference, upper and lower marker colors.
static sead::Color4f sUnk_71025FC610[3] = {
    {0.8f, 0.4f, 0.4f, 1.0f}, sead::Color4f::cRed, sead::Color4f::cYellow};

// NON_MATCHING: enum argument spills and register allocation differ.
void FinalOutputMeasure::writeLoudnessTextSimple_(
    sead::TextWriter* writer, const sead::SafeString& label, f32 value,
    LoudnessTarget target) const {
    const sead::Vector2f cursor = writer->getCursor();
    writer->setColor(sead::Color4f::cWhite);
    writer->printf("%s", label.cstr());
    if (_1e0[target] < value)
        writer->setColor(sead::Color4f::cRed);
    else if (_1ec[target] < value)
        writer->setColor(sead::Color4f::cYellow);
    else if (_1f8[target] > value)
        writer->setColor({0.7f, 0.7f, 1.0f, 1.0f});
    else
        writer->setColor(sead::Color4f::cWhite);
    writer->printf("%6.1f", value);
    writer->setCursor(cursor);
    writer->printf("\n");
}

// NON_MATCHING: enum argument spills and stack layout differ.
void FinalOutputMeasure::writeLoudnessText_(
    sead::TextWriter* writer, const sead::SafeString& label, f32 value,
    f32 secondary_value, LoudnessTarget target) const {
    const sead::Vector2f cursor = writer->getCursor();
    writer->setColor(sead::Color4f::cWhite);
    writer->printf("%s", label.cstr());
    if (_1e0[target] < value)
        writer->setColor(sead::Color4f::cRed);
    else if (_1ec[target] < value)
        writer->setColor(sead::Color4f::cYellow);
    else if (_1f8[target] > value)
        writer->setColor({0.7f, 0.7f, 1.0f, 1.0f});
    else
        writer->setColor(sead::Color4f::cWhite);
    writer->printf("%7.2f", value);
    if (target != LoudnessTarget::_2) {
        if (_1e0[target] < secondary_value)
            writer->setColor(sead::Color4f::cRed);
        else if (_1ec[target] < secondary_value)
            writer->setColor(sead::Color4f::cYellow);
        else if (_1f8[target] > secondary_value)
            writer->setColor({0.7f, 0.7f, 1.0f, 1.0f});
        else
            writer->setColor(sead::Color4f::cWhite);
        writer->printf(" (%7.2f)", secondary_value);
    }
    writer->setCursor(cursor);
    writer->printf("\n");
}

void FinalOutputMeasure::writeVUText_(
    sead::TextWriter* writer, const sead::SafeString& label, f32 value,
    f32 secondary_value) const {
    const sead::Vector2f cursor = writer->getCursor();
    writer->setColor(sead::Color4f::cWhite);
    writer->printf("%s", label.cstr());
    if (_1d4 < value)
        writer->setColor(sead::Color4f::cRed);
    else if (_1d8 < value)
        writer->setColor(sead::Color4f::cYellow);
    else
        writer->setColor(sead::Color4f::cWhite);
    writer->printf("%7.2f", value);
    if (_1d4 < secondary_value)
        writer->setColor(sead::Color4f::cRed);
    else if (_1d8 < secondary_value)
        writer->setColor(sead::Color4f::cYellow);
    else
        writer->setColor(sead::Color4f::cWhite);
    writer->printf(" (%7.2f)", secondary_value);
    writer->setCursor(cursor);
    writer->printf("\n");
}

// NON_MATCHING: vector temporaries and floating-point loads use a different schedule.
void FinalOutputMeasure::drawMeterBar_(
    DebugDrawer* drawer, const sead::Vector2f& position, const sead::Vector2f& size,
    f32 value, f32 peak, f32 minimum, f32 maximum, f32 upper_threshold,
    f32 lower_threshold, f32 reference) const {
    if (maximum <= minimum)
        maximum = minimum + 1.0f;

    const sead::Color4f outline(0.4f, 0.4f, 0.6f, 1.0f);
    drawer->drawRect(position, size, {0.0f, 0.0f, 1.0f, 0.2f}, true, outline);

    s32 tick = static_cast<s32>(minimum);
    if (static_cast<f32>(tick) == minimum)
        ++tick;
    const s32 tick_end = static_cast<s32>(maximum);
    for (; tick < tick_end; ++tick) {
        if (tick % 5 != 0)
            continue;
        sead::Vector2f start = position;
        start.x += (static_cast<f32>(tick) - minimum) * size.x / (maximum - minimum);
        drawer->drawLine(start, start + sead::Vector2f(0.0f, 3.0f), outline);
        start.y += size.y - 3.0f;
        drawer->drawLine(start, start + sead::Vector2f(0.0f, 3.0f), outline);
    }

    sead::Vector2f upper_position = position;
    if (maximum > upper_threshold) {
        upper_position.x += (upper_threshold - minimum) * size.x / (maximum - minimum);
        drawer->drawLine(upper_position, upper_position + sead::Vector2f(0.0f, size.y),
                         sUnk_71025FC610[1]);
    }
    sead::Vector2f lower_position = position;
    if (maximum > lower_threshold) {
        lower_position.x += (lower_threshold - minimum) * size.x / (maximum - minimum);
        drawer->drawLine(lower_position, lower_position + sead::Vector2f(0.0f, size.y),
                         sUnk_71025FC610[2]);
    }

    f32 level = value;
    if (level < minimum)
        level = minimum;
    else if (level > maximum)
        level = maximum;

    f32 peak_line = sead::Mathf::minNumber();
    if (peak != sead::Mathf::minNumber()) {
        peak_line = peak;
        if (peak_line < minimum)
            peak_line = minimum;
        else if (peak_line > maximum)
            peak_line = maximum;
    }

    if (level >= upper_threshold) {
        const f32 segment = level - upper_threshold;
        sead::Vector2f start = upper_position;
        start.y += 1.0f;
        drawer->drawRect(start, {segment * size.x / (maximum - minimum), size.y - 2.0f},
                         sead::Color4f::cRed, false, sead::Color4f::cGray);
        level -= segment;
    }
    if (level >= lower_threshold) {
        const f32 segment = level - lower_threshold;
        sead::Vector2f start = lower_position;
        start.y += 1.0f;
        drawer->drawRect(start, {segment * size.x / (maximum - minimum), size.y - 2.0f},
                         sead::Color4f::cYellow, false, sead::Color4f::cGray);
        level -= segment;
    }

    const sead::Color4f green(0.0f, 0.75f, 0.0f, 1.0f);
    sead::Vector2f fill_position = position;
    fill_position.y += 1.0f;
    drawer->drawRect(fill_position,
                     {(level - minimum) * size.x / (maximum - minimum), size.y - 2.0f},
                     green, false, sead::Color4f::cGray);

    if (reference > sead::Mathf::minNumber()) {
        sead::Vector2f start = position;
        start.x += (reference - minimum) * size.x / (maximum - minimum);
        drawer->drawLine(start, start + sead::Vector2f(0.0f, size.y), sUnk_71025FC610[0]);
    }
    if (peak_line != sead::Mathf::minNumber()) {
        sead::Vector2f start = position;
        start.y += 1.0f;
        start.x += (peak_line - minimum) * size.x / (maximum - minimum);
        sead::Color4f color = green;
        if (_1cc == 0.0f) {
            color.a = 0.5f;
            drawer->drawLine(start, start + sead::Vector2f(0.0f, size.y - 2.0f), color);
        } else {
            color = sead::Color4f::cGreen;
            drawer->drawLine(start, start + sead::Vector2f(0.0f, size.y - 2.0f), color);
            start.x -= 1.0f;
            drawer->drawLine(start, start + sead::Vector2f(0.0f, size.y - 2.0f), color);
        }
    }
}

// NON_MATCHING: vector temporaries change the stack layout and expression scheduling.
void FinalOutputMeasure::drawMeterBarVertical_(
    DebugDrawer* drawer, const sead::Vector2f& position, const sead::Vector2f& size,
    f32 value, f32 peak, f32 minimum, f32 maximum, f32 upper_threshold,
    f32 lower_threshold, f32 reference, const sead::Color4f& color) const {
    if (maximum <= minimum)
        maximum = minimum + 1.0f;

    const sead::Color4f outline(0.4f, 0.4f, 0.6f, 1.0f);
    drawer->drawRect(position, size, {0.0f, 0.0f, 1.0f, 0.2f}, true, outline);

    s32 tick = static_cast<s32>(minimum);
    if (static_cast<f32>(tick) == minimum)
        ++tick;
    const s32 tick_end = static_cast<s32>(maximum);
    for (; tick < tick_end; ++tick) {
        if (tick % 5 != 0)
            continue;
        sead::Vector2f start = position;
        start.y += (1.0f - (static_cast<f32>(tick) - minimum) / (maximum - minimum)) * size.y;
        drawer->drawLine(start, start + sead::Vector2f(4.0f, 0.0f), outline);
        start.x += size.x - 4.0f;
        drawer->drawLine(start, start + sead::Vector2f(4.0f, 0.0f), outline);
    }

    sead::Vector2f upper_position = position;
    if (maximum > upper_threshold) {
        upper_position.y += (1.0f - (upper_threshold - minimum) / (maximum - minimum)) * size.y;
        drawer->drawLine(upper_position, upper_position + sead::Vector2f(size.x, 0.0f),
                         sUnk_71025FC610[1]);
    }
    sead::Vector2f lower_position = position;
    if (maximum > lower_threshold) {
        lower_position.y += (1.0f - (lower_threshold - minimum) / (maximum - minimum)) * size.y;
        drawer->drawLine(lower_position, lower_position + sead::Vector2f(size.x, 0.0f),
                         sUnk_71025FC610[2]);
    }

    f32 level = value;
    if (level < minimum)
        level = minimum;
    else if (level > maximum)
        level = maximum;

    f32 peak_line = sead::Mathf::minNumber();
    if (peak != sead::Mathf::minNumber()) {
        peak_line = peak;
        if (peak_line < minimum)
            peak_line = minimum;
        else if (peak_line > maximum)
            peak_line = maximum;
    }

    if (level >= upper_threshold) {
        const f32 segment = level - upper_threshold;
        const f32 height = segment * size.y / (maximum - minimum);
        sead::Vector2f start = upper_position;
        start.x += 1.0f;
        start.y -= height;
        drawer->drawRect(start, {size.x - 2.0f, height}, sead::Color4f::cRed, false,
                         sead::Color4f::cGray);
        level -= segment;
    }
    if (level >= lower_threshold) {
        const f32 segment = level - lower_threshold;
        const f32 height = segment * size.y / (maximum - minimum);
        sead::Vector2f start = lower_position;
        start.x += 1.0f;
        start.y -= height;
        drawer->drawRect(start, {size.x - 2.0f, height}, sead::Color4f::cYellow, false,
                         sead::Color4f::cGray);
        level -= segment;
    }

    const f32 height = (level - minimum) * size.y / (maximum - minimum);
    sead::Vector2f fill_position = position;
    fill_position.x += 1.0f;
    fill_position.y += size.y;
    fill_position.y -= height;
    drawer->drawRect(fill_position, {size.x - 2.0f, height}, color, false, sead::Color4f::cGray);

    if (reference > sead::Mathf::minNumber()) {
        sead::Vector2f start = position;
        start.y += (1.0f - (reference - minimum) / (maximum - minimum)) * size.y;
        drawer->drawLine(start, start + sead::Vector2f(size.x, 0.0f), sUnk_71025FC610[0]);
    }
    if (peak_line != sead::Mathf::minNumber()) {
        sead::Vector2f start = position;
        start.x += 1.0f;
        start.y += (1.0f - (peak_line - minimum) / (maximum - minimum)) * size.y;
        sead::Color4f peak_color = color;
        if (_1cc == 0.0f) {
            peak_color.a = 0.5f;
            drawer->drawLine(start, start + sead::Vector2f(size.x - 2.0f, 0.0f), peak_color);
        } else {
            drawer->drawLine(start, start + sead::Vector2f(size.x - 2.0f, 0.0f), peak_color);
            start.y += 1.0f;
            drawer->drawLine(start, start + sead::Vector2f(size.x - 2.0f, 0.0f), peak_color);
        }
    }
}

// 0x7100BA9D00
FinalOutputMeasure::~FinalOutputMeasure() {
    finalize();
}

// 0x7100BA9ECC
void FinalOutputMeasure::initialize(const InitializeArg& arg, sead::Heap* heap) {
    initialize(arg, heap, nullptr, nullptr);
}

// 0x7100BAA5C0
void FinalOutputMeasure::workerThreadProc_(bool is_quitting) {
    analyze_();
}

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

// 0x7100baa27c
// NON_MATCHING: when the first two conditions fail, the original loads mIsActive and mIsFrameProcessAdded
// together and branches on both (same logic, different block layout).
void FinalOutputMeasure::updateActivation() {
    const auto& hardware =
        nn::atk::detail::Util::Singleton<nn::atk::detail::driver::HardwareManager>::GetInstance();
    if ((hardware.GetRendererSampleRate() == 48000 && mDisplayMode != 0) || _158 || mIsActive) {
        if (mIsFrameProcessAdded || nn::atk::SoundSystem::GetCircularBufferSinkBufferSize() == 0)
            return;
        if (!mFrameProcessMgr) {
            mFrameProcessMgr = System::sInstance->mAudioFrameProcessMgr;
            if (!mFrameProcessMgr) {
                _36 = true;
                return;
            }
        }
        reset();
        mIsFrameProcessAdded = mFrameProcessMgr->addProcess(this);
    } else if (mIsFrameProcessAdded) {
        if (mFrameProcessMgr)
            mFrameProcessMgr->removeProcess(this);
        mIsFrameProcessAdded = false;
    }
}

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
