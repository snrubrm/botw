#include "aal/aalFinalOutputMeasure.h"
#include "aal/aalDebugDrawer.h"
#include <gfx/seadTextWriter.h>
#include <devenv/seadFontMgr.h>
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

// NON_MATCHING: enum index spills, floating-point scheduling and stack layout differ.
void FinalOutputMeasure::drawInformationSimple_(sead::DrawContext* context,
                                                 sead::TextWriter* writer) const {
    writer->setScale({0.8f, 0.8f});
    f32 max_vu = sead::Mathf::minNumber();
    f32 max_peak = sead::Mathf::minNumber();
    for (s32 i = 0; i < 6; ++i) {
        SpeakerChannel channel(i);
        const f32 vu = getVU(channel);
        const f32 peak = _19c[getChannelIndex(channel)];
        max_vu = max_vu > vu ? max_vu : vu;
        max_peak = max_peak > peak ? max_peak : peak;
    }
    DebugDrawer drawer(writer);
    drawer.begin(context);
    sead::Vector2f position = _164;
    const f32 height = writer->getFont()->getHeight() * writer->getScale().y;
    drawMeterBar_(&drawer, position, {_16c, height}, _e8, _194, _17c, _180,
                  _1e0[0] > _1ec[0] ? _1e0[0] : _1ec[0],
                  _1e0[0] < _1ec[0] ? _1e0[0] : _1ec[0], _1f8[0]);
    position.y += height;
    drawMeterBar_(&drawer, position, {_16c, height}, _ec, sead::Mathf::minNumber(), _17c, _180,
                  _1e0[1] > _1ec[1] ? _1e0[1] : _1ec[1],
                  _1e0[1] < _1ec[1] ? _1e0[1] : _1ec[1], _1f8[1]);
    position.y += height;
    drawMeterBar_(&drawer, position, {_16c, height}, max_vu, max_peak, _184, _188,
                  _1d4 > _1d8 ? _1d4 : _1d8, _1d4 < _1d8 ? _1d4 : _1d8,
                  sead::Mathf::minNumber());
    drawer.end();
    writer->beginDraw();
    writer->setCursorFromTopLeft(_164);
    writeLoudnessTextSimple_(writer, "Moment ", _e8, LoudnessTarget::_0);
    writeLoudnessTextSimple_(writer, "Short  ", _ec, LoudnessTarget::_1);
    const sead::Vector2f cursor = writer->getCursor();
    writer->setColor(sead::Color4f::cWhite);
    writer->printf("%s", "Max VU ");
    if (_1d4 < max_vu)
        writer->setColor(sead::Color4f::cRed);
    else if (_1d8 < max_vu)
        writer->setColor(sead::Color4f::cYellow);
    else
        writer->setColor(sead::Color4f::cWhite);
    writer->printf("%6.1f", max_vu);
    writer->setCursor(cursor);
    writer->printf("\n");
    writer->endDraw();
}


// NON_MATCHING: enum index spills, floating-point scheduling and stack layout differ.
void FinalOutputMeasure::drawInformationSimpleStereo_(sead::DrawContext* context,
                                                       sead::TextWriter* writer) const {
    writer->setScale({0.8f, 0.8f});
    DebugDrawer drawer(writer);
    drawer.begin(context);
    sead::Vector2f position = _164;
    const f32 height = writer->getFont()->getHeight() * writer->getScale().y;
    drawMeterBar_(&drawer, position, {_16c, height}, _e8, _194, _17c, _180,
                  _1e0[0] > _1ec[0] ? _1e0[0] : _1ec[0],
                  _1e0[0] < _1ec[0] ? _1e0[0] : _1ec[0], _1f8[0]);
    position.y += height;
    drawMeterBar_(&drawer, position, {_16c, height}, _ec, sead::Mathf::minNumber(), _17c, _180,
                  _1e0[1] > _1ec[1] ? _1e0[1] : _1ec[1],
                  _1e0[1] < _1ec[1] ? _1e0[1] : _1ec[1], _1f8[1]);
    position.y += height;
    drawMeterBar_(&drawer, position, {_16c, height}, getVU(SpeakerChannel::FrontLeft),
                  _19c[getChannelIndex(SpeakerChannel::FrontLeft)], _184, _188,
                  _1d4 > _1d8 ? _1d4 : _1d8, _1d4 < _1d8 ? _1d4 : _1d8,
                  sead::Mathf::minNumber());
    position.y += height;
    drawMeterBar_(&drawer, position, {_16c, height}, getVU(SpeakerChannel::FrontRight),
                  _19c[getChannelIndex(SpeakerChannel::FrontRight)], _184, _188,
                  _1d4 > _1d8 ? _1d4 : _1d8, _1d4 < _1d8 ? _1d4 : _1d8,
                  sead::Mathf::minNumber());
    drawer.end();
    writer->beginDraw();
    writer->setCursorFromTopLeft(_164);
    writeLoudnessTextSimple_(writer, "Moment ", _e8, LoudnessTarget::_0);
    writeLoudnessTextSimple_(writer, "Short  ", _ec, LoudnessTarget::_1);
    {
        const sead::Vector2f cursor = writer->getCursor();
        const f32 vu = getVU(SpeakerChannel::FrontLeft);
        writer->setColor(sead::Color4f::cWhite);
        writer->printf("%s", "VU L   ");
        if (_1d4 < vu)
            writer->setColor(sead::Color4f::cRed);
        else if (_1d8 < vu)
            writer->setColor(sead::Color4f::cYellow);
        else
            writer->setColor(sead::Color4f::cWhite);
        writer->printf("%6.1f", vu);
        writer->setCursor(cursor);
        writer->printf("\n");
    }
    {
        const sead::Vector2f cursor = writer->getCursor();
        const f32 vu = getVU(SpeakerChannel::FrontRight);
        writer->setColor(sead::Color4f::cWhite);
        writer->printf("%s", "VU R   ");
        if (_1d4 < vu)
            writer->setColor(sead::Color4f::cRed);
        else if (_1d8 < vu)
            writer->setColor(sead::Color4f::cYellow);
        else
            writer->setColor(sead::Color4f::cWhite);
        writer->printf("%6.1f", vu);
        writer->setCursor(cursor);
        writer->printf("\n");
    }
    writer->endDraw();
}


// NON_MATCHING: enum index conversions, tick-loop lowering, and stack scheduling differ.
// 0x7100bae1d0
void FinalOutputMeasure::drawInformationVerticalSimple_(sead::DrawContext* context,
                                                        sead::TextWriter* writer) const {
    writer->setScale({0.7f, 0.7f});
    f32 max_vu = sead::Mathf::minNumber();
    f32 max_vu_peak = sead::Mathf::minNumber();
    for (s32 i = 0; i < 6; ++i) {
        SpeakerChannel channel(i);
        const f32 vu = getVU(channel);
        const f32 peak = _19c[getChannelIndex(channel)];
        max_vu = max_vu > vu ? max_vu : vu;
        max_vu_peak = max_vu_peak > peak ? max_vu_peak : peak;
    }
    f32 max_sample = sead::Mathf::minNumber();
    f32 max_sample_peak = sead::Mathf::minNumber();
    for (s32 i = 0; i < 6; ++i) {
        SpeakerChannel channel(i);
        const f32 sample = getSamplePeak(channel);
        const f32 held = _1b4[getChannelIndex(channel)];
        const f32 peak = held == 0.0f ? -100.0f : sead::Mathf::logTable(held) * 8.685889f;
        max_sample = max_sample > sample ? max_sample : sample;
        max_sample_peak = max_sample_peak > peak ? max_sample_peak : peak;
    }

    const f32 glyph_width = writer->getFont()->getCharWidth('W');
    const f32 width = glyph_width * writer->getScale().x;
    const f32 narrow_width = width * 3.0f;
    DebugDrawer drawer(writer);
    drawer.begin(context);
    const f32 wide_width = width * 11.0f;
    const f32 wide_height = _16c;
    const f32 wide_font_height = writer->getFont()->getHeight();
    const f32 wide_line_height = wide_font_height * writer->getScale().y;
    const sead::Vector2f wide_size{wide_width, wide_height + (wide_line_height + wide_line_height)};
    const f32 narrow_height = _16c;
    const f32 narrow_font_height = writer->getFont()->getHeight();
    const f32 narrow_line_height = narrow_font_height * writer->getScale().y;
    const sead::Vector2f narrow_size{narrow_width, narrow_height + (narrow_line_height + narrow_line_height)};
    sead::Vector2f position = _164;
    drawer.drawRect(position, narrow_size, _204, false, sead::Color4f::cGray);
    position.x += narrow_width;
    drawer.drawRect(position, wide_size, _204, false, sead::Color4f::cGray);
    const f32 wide_step = width * 12.0f;
    position.x += wide_step;
    drawer.drawRect(position, narrow_size, _204, false, sead::Color4f::cGray);
    position.x += narrow_width;
    drawer.drawRect(position, wide_size, _204, false, sead::Color4f::cGray);
    position.x += wide_width;
    drawer.drawRect(position, narrow_size, _204, false, sead::Color4f::cGray);

    const sead::Vector2f bar_origin = _164;
    position = {bar_origin.x + narrow_width, bar_origin.y};
    const f32 bar_font_height = writer->getFont()->getHeight();
    position.y += bar_font_height * writer->getScale().y;
    const sead::Vector2f bar_size{width * 5.0f, _16c};
    drawMeterBarVertical_(&drawer, position, bar_size, _e8, _194, _17c, _180,
                          _1e0[0] > _1ec[0] ? _1e0[0] : _1ec[0],
                          _1e0[0] < _1ec[0] ? _1e0[0] : _1ec[0], _1f8[0],
                          {0.5f, 1.0f, 1.0f, 1.0f});
    const f32 bar_step = width * 6.0f;
    position.x += bar_step;
    drawMeterBarVertical_(&drawer, position, bar_size, _ec, sead::Mathf::minNumber(), _17c, _180,
                          _1e0[1] > _1ec[1] ? _1e0[1] : _1ec[1],
                          _1e0[1] < _1ec[1] ? _1e0[1] : _1ec[1], _1f8[1],
                          {0.5f, 1.0f, 1.0f, 1.0f});
    position.x += bar_step;
    position.x += narrow_width;
    drawMeterBarVertical_(&drawer, position, bar_size, max_vu, max_vu_peak, _184, _188,
                          _1d4 > _1d8 ? _1d4 : _1d8, _1d4 < _1d8 ? _1d4 : _1d8,
                          sead::Mathf::minNumber(), {0.0f, 0.75f, 0.0f, 1.0f});
    position.x += bar_step;
    drawMeterBarVertical_(&drawer, position, bar_size, max_sample, max_sample_peak, _18c, _190,
                          _1dc, sead::Mathf::maxNumber(), sead::Mathf::minNumber(),
                          {0.8f, 0.4f, 0.2f, 1.0f});
    drawer.end();

    position = {_164.x + narrow_width, _164.y};
    writer->beginDraw();
    writer->setCursorFromTopLeft(position);
    if (_e8 > -100.0f)
        writer->printf("%5.1f ", _e8);
    else
        writer->printf("-inf. ");
    if (_ec > -100.0f)
        writer->printf("%5.1f ", _ec);
    else
        writer->printf("-inf. ");
    writer->printf("   ");
    if (max_vu > -100.0f)
        writer->printf("%5.1f ", max_vu);
    else
        writer->printf("-inf. ");
    if (-100.0f < max_sample)
        writer->printf("%5.1f ", max_sample);
    else
        writer->printf("-inf. ");
    const f32 label_font_height = writer->getFont()->getHeight();
    position.y += label_font_height * writer->getScale().y;
    position.y += _16c;
    writer->setCursorFromTopLeft(position);
    writer->printf(" MMT  ");
    writer->printf(" SHT  ");
    writer->printf("   ");
    writer->printf(" VU   ");
    writer->printf(" PK   ");

    const f32 base_x = _164.x;
    const f32 base_y = _164.y;
    const f32 top_font_height = writer->getFont()->getHeight();
    const f32 top = base_y + top_font_height * writer->getScale().y;
    {
        const f32 min = _17c, max = _180, height = _16c;
        const f32 font_height = writer->getFont()->getHeight();
        const f32 half_font_height = font_height * writer->getScale().y * -0.5f;
        for (s32 i = static_cast<s32>(min), last = static_cast<s32>(max); i <= last; ++i) {
            if (i % 5 == 0) {
                writer->setCursorFromTopLeft(
                    {base_x, top + half_font_height + height * (1.0f - (f32(i) - min) / (max - min))});
                writer->printf("%3d", i);
            }
            if (i == last)
                break;
        }
    }
    const f32 second_axis_x = wide_step + (narrow_width + base_x);
    {
        const f32 min = _184, max = _188, height = _16c;
        const f32 x = second_axis_x;
        const f32 font_height = writer->getFont()->getHeight();
        const f32 half_font_height = font_height * writer->getScale().y * -0.5f;
        for (s32 i = static_cast<s32>(min), last = static_cast<s32>(max); i <= last; ++i) {
            if (i % 5 == 0) {
                writer->setCursorFromTopLeft(
                    {x, top + half_font_height + height * (1.0f - (f32(i) - min) / (max - min))});
                writer->printf("%3d", i);
            }
            if (i == last)
                break;
        }
    }
    {
        const f32 min = _18c, max = _190, height = _16c;
        const f32 font_height = writer->getFont()->getHeight();
        const f32 x = (wide_step + (narrow_width + second_axis_x)) - width;
        const f32 half_font_height = font_height * writer->getScale().y * -0.5f;
        for (s32 i = static_cast<s32>(min), last = static_cast<s32>(max); i <= last; ++i) {
            if (i % 5 == 0) {
                writer->setCursorFromTopLeft(
                    {x, top + half_font_height + height * (1.0f - (f32(i) - min) / (max - min))});
                writer->printf("%3d", i);
            }
            if (i == last)
                break;
        }
    }
    writer->endDraw();
}

// NON_MATCHING: enum index conversions, tick-loop lowering, and stack scheduling differ.
// 0x7100baeb4c
void FinalOutputMeasure::drawInformationVerticalStereo_(sead::DrawContext* context,
                                                        sead::TextWriter* writer) const {
    writer->setScale({0.7f, 0.7f});
    const f32 glyph_width = writer->getFont()->getCharWidth('W');
    const f32 width = glyph_width * writer->getScale().x;
    const f32 narrow_width = width * 3.0f;
    DebugDrawer drawer(writer);
    drawer.begin(context);
    const f32 wide_width = width * 11.0f;
    const f32 wide_height = _16c;
    const f32 wide_font_height = writer->getFont()->getHeight();
    const f32 wide_line_height = wide_font_height * writer->getScale().y;
    const sead::Vector2f wide_size{wide_width, wide_height + (wide_line_height + wide_line_height)};
    const f32 narrow_height = _16c;
    const f32 narrow_font_height = writer->getFont()->getHeight();
    const f32 narrow_line_height = narrow_font_height * writer->getScale().y;
    const sead::Vector2f narrow_size{narrow_width, narrow_height + (narrow_line_height + narrow_line_height)};
    sead::Vector2f position = _164;
    drawer.drawRect(position, narrow_size, _204, false, sead::Color4f::cGray);
    position.x += narrow_width;
    drawer.drawRect(position, wide_size, _204, false, sead::Color4f::cGray);
    const f32 wide_step = width * 12.0f;
    position.x += wide_step;
    drawer.drawRect(position, narrow_size, _204, false, sead::Color4f::cGray);
    position.x += narrow_width;
    drawer.drawRect(position, wide_size, _204, false, sead::Color4f::cGray);
    position.x += wide_step;
    drawer.drawRect(position, wide_size, _204, false, sead::Color4f::cGray);
    position.x += wide_width;
    drawer.drawRect(position, narrow_size, _204, false, sead::Color4f::cGray);

    const sead::Vector2f bar_origin = _164;
    position = {bar_origin.x + narrow_width, bar_origin.y};
    const f32 bar_font_height = writer->getFont()->getHeight();
    position.y += bar_font_height * writer->getScale().y;
    const sead::Vector2f bar_size{width * 5.0f, _16c};
    drawMeterBarVertical_(&drawer, position, bar_size, _e8, _194, _17c, _180,
                          _1e0[0] > _1ec[0] ? _1e0[0] : _1ec[0],
                          _1e0[0] < _1ec[0] ? _1e0[0] : _1ec[0], _1f8[0],
                          {0.5f, 1.0f, 1.0f, 1.0f});
    const f32 bar_step = width * 6.0f;
    position.x += bar_step;
    drawMeterBarVertical_(&drawer, position, bar_size, _ec, sead::Mathf::minNumber(), _17c, _180,
                          _1e0[1] > _1ec[1] ? _1e0[1] : _1ec[1],
                          _1e0[1] < _1ec[1] ? _1e0[1] : _1ec[1], _1f8[1],
                          {0.5f, 1.0f, 1.0f, 1.0f});
    position.x += bar_step;
    position.x += narrow_width;
    drawMeterBarVertical_(&drawer, position, bar_size, getVU(SpeakerChannel::FrontLeft),
                          _19c[getChannelIndex(SpeakerChannel::FrontLeft)], _184, _188,
                          _1d4 > _1d8 ? _1d4 : _1d8, _1d4 < _1d8 ? _1d4 : _1d8,
                          sead::Mathf::minNumber(), {0.0f, 0.75f, 0.0f, 1.0f});
    position.x += bar_step;
    const f32 left_sample = getSamplePeak(SpeakerChannel::FrontLeft);
    const f32 left_held = _1b4[getChannelIndex(SpeakerChannel::FrontLeft)];
    const f32 left_peak = left_held == 0.0f ? -100.0f : sead::Mathf::logTable(left_held) * 8.685889f;
    drawMeterBarVertical_(&drawer, position, bar_size, left_sample, left_peak, _18c, _190,
                          _1dc, sead::Mathf::maxNumber(), sead::Mathf::minNumber(),
                          {0.8f, 0.4f, 0.2f, 1.0f});
    position.x += bar_step;
    position.x += narrow_width;
    drawMeterBarVertical_(&drawer, position, bar_size, getVU(SpeakerChannel::FrontRight),
                          _19c[getChannelIndex(SpeakerChannel::FrontRight)], _184, _188,
                          _1d4 > _1d8 ? _1d4 : _1d8, _1d4 < _1d8 ? _1d4 : _1d8,
                          sead::Mathf::minNumber(), {0.0f, 0.75f, 0.0f, 1.0f});
    position.x += bar_step;
    const f32 right_sample = getSamplePeak(SpeakerChannel::FrontRight);
    const f32 right_held = _1b4[getChannelIndex(SpeakerChannel::FrontRight)];
    const f32 right_peak = right_held == 0.0f ? -100.0f : sead::Mathf::logTable(right_held) * 8.685889f;
    drawMeterBarVertical_(&drawer, position, bar_size, right_sample, right_peak, _18c, _190,
                          _1dc, sead::Mathf::maxNumber(), sead::Mathf::minNumber(),
                          {0.8f, 0.4f, 0.2f, 1.0f});
    drawer.end();

    position = {_164.x + narrow_width, _164.y};
    writer->beginDraw();
    writer->setCursorFromTopLeft(position);
    if (_e8 > -100.0f)
        writer->printf("%5.1f ", _e8);
    else
        writer->printf("-inf. ");
    if (_ec > -100.0f)
        writer->printf("%5.1f ", _ec);
    else
        writer->printf("-inf. ");
    writer->printf("   ");
    const f32 left_vu_text = getVU(SpeakerChannel::FrontLeft);
    if (left_vu_text > -100.0f)
        writer->printf("%5.1f ", left_vu_text);
    else
        writer->printf("-inf. ");
    const f32 left_sample_text = getSamplePeak(SpeakerChannel::FrontLeft);
    if (left_sample_text > -100.0f)
        writer->printf("%5.1f ", left_sample_text);
    else
        writer->printf("-inf. ");
    const f32 right_vu_text = getVU(SpeakerChannel::FrontRight);
    if (right_vu_text > -100.0f)
        writer->printf("%5.1f ", right_vu_text);
    else
        writer->printf("-inf. ");
    const f32 right_sample_text = getSamplePeak(SpeakerChannel::FrontRight);
    if (right_sample_text > -100.0f)
        writer->printf("%5.1f ", right_sample_text);
    else
        writer->printf("-inf. ");
    const f32 label_font_height = writer->getFont()->getHeight();
    position.y += label_font_height * writer->getScale().y;
    position.y += _16c;
    writer->setCursorFromTopLeft(position);
    writer->printf(" MMT  ");
    writer->printf(" SHT  ");
    writer->printf("   ");
    writer->printf("VU-L  ");
    writer->printf("PK-L  ");
    writer->printf("VU-R  ");
    writer->printf("PK-R  ");

    const f32 base_x = _164.x;
    const f32 base_y = _164.y;
    const f32 top_font_height = writer->getFont()->getHeight();
    const f32 top = base_y + top_font_height * writer->getScale().y;
    {
        const f32 min = _17c, max = _180, height = _16c;
        const f32 font_height = writer->getFont()->getHeight();
        const f32 half_font_height = font_height * writer->getScale().y * -0.5f;
        for (s32 i = static_cast<s32>(min), last = static_cast<s32>(max); i <= last; ++i) {
            if (i % 5 == 0) {
                writer->setCursorFromTopLeft(
                    {base_x, top + half_font_height + height * (1.0f - (f32(i) - min) / (max - min))});
                writer->printf("%3d", i);
            }
            if (i == last)
                break;
        }
    }
    const f32 second_axis_x = wide_step + (narrow_width + base_x);
    {
        const f32 min = _184, max = _188, height = _16c;
        const f32 x = second_axis_x;
        const f32 font_height = writer->getFont()->getHeight();
        const f32 half_font_height = font_height * writer->getScale().y * -0.5f;
        for (s32 i = static_cast<s32>(min), last = static_cast<s32>(max); i <= last; ++i) {
            if (i % 5 == 0) {
                writer->setCursorFromTopLeft(
                    {x, top + half_font_height + height * (1.0f - (f32(i) - min) / (max - min))});
                writer->printf("%3d", i);
            }
            if (i == last)
                break;
        }
    }
    {
        const f32 min = _18c, max = _190, height = _16c;
        const f32 font_height = writer->getFont()->getHeight();
        const f32 x = (wide_step + (wide_step + (narrow_width + second_axis_x))) - width;
        const f32 half_font_height = font_height * writer->getScale().y * -0.5f;
        for (s32 i = static_cast<s32>(min), last = static_cast<s32>(max); i <= last; ++i) {
            if (i % 5 == 0) {
                writer->setCursorFromTopLeft(
                    {x, top + half_font_height + height * (1.0f - (f32(i) - min) / (max - min))});
                writer->printf("%3d", i);
            }
            if (i == last)
                break;
        }
    }
    writer->endDraw();
}

}  // namespace aal
