#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <gfx/seadColor.h>
#include <math/seadVector.h>
#include "aal/aalAudioFrameProcessMgr.h"
#include "aal/aalDeviceType.h"
#include "aal/aalSpeakerChannel.h"
#include "aal/aalWorkerThread.h"

namespace sead {
class DrawContext;
class Heap;
class TextWriter;
class Color4f;
}  // namespace sead

namespace aal {
class DebugDrawer;

/// Measures the final output of a device. TODO: incomplete.
// Constructor 0x7100BA9B38 and table 0x71024C5A70 establish the three bases.
// Finalization independently unregisters the frame-process subobject at +0x10.
class FinalOutputMeasure : public WorkerTask, public IAudioFrameProcess, public sead::hostio::Node {
public:
    struct InitializeArg {
        f32 _0;
    };

    // The native callers pass 0, 1 or 2; the three threshold arrays use those indices.
    // Repeated stack-backed conversions follow the existing aal SEAD_ENUM convention.
    // The enumerator names have not been recovered.
    SEAD_ENUM(LoudnessTarget, _0, _1, _2)

    explicit FinalOutputMeasure(DeviceType device);
    ~FinalOutputMeasure() override;

    void initialize(const InitializeArg& arg, sead::Heap* heap);
    void initialize(const InitializeArg& arg, sead::Heap* heap, WorkerThread* worker,
                    AudioFrameProcessMgr* frameProcessMgr);
    void finalize();
    void calc();
    void drawInformation(sead::DrawContext* context, sead::TextWriter* writer) const;
    /// Starts measuring (the measure is active only while something wants to see it).
    void activate();
    /// The VU value (the average level) of the channel.
    f32 getVU(SpeakerChannel channel) const;
    /// The sample peak of the channel in dB (-100 if the channel is silent).
    f32 getSamplePeak(SpeakerChannel channel) const;
    /// Inline in the original: ksys::snd::Unk_SoundMgr2a0 0x71012c629c reads +0x35 and +0xe8 directly.
    bool isFrameProcessAdded() const { return mIsFrameProcessAdded; }
    f32 get_e8() const { return _e8; }

private:
    void workerThreadProc_(bool is_quitting) override;
    void audioFrameProcess_() override;
    void analyze_();
    /// 0x7100baa0d0 (declared only)
    void reset();
    /// 0x7100baa27c
    void updateActivation();
    /// The different layouts of the information that drawInformation draws.
    void drawInformationSimple_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationSimpleStereo_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationSimpleSurround_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationFull_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalSimple_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalStereo_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalSurround_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalSimpleLFE_(sead::DrawContext* context, sead::TextWriter* writer) const;

    // Parameter names describe the ranges and markers consumed by the native drawing helpers.
    void drawMeterBar_(DebugDrawer* drawer, const sead::Vector2f& position,
                       const sead::Vector2f& size, f32 value, f32 peak, f32 minimum,
                       f32 maximum, f32 upper_threshold, f32 lower_threshold,
                       f32 reference) const;
    void drawMeterBarVertical_(DebugDrawer* drawer, const sead::Vector2f& position,
                               const sead::Vector2f& size, f32 value, f32 peak, f32 minimum,
                               f32 maximum, f32 upper_threshold, f32 lower_threshold,
                               f32 reference, const sead::Color4f& color) const;
    void writeLoudnessTextSimple_(sead::TextWriter* writer, const sead::SafeString& label,
                                 f32 value, LoudnessTarget target) const;
    void writeLoudnessText_(sead::TextWriter* writer, const sead::SafeString& label,
                           f32 value, f32 secondary_value, LoudnessTarget target) const;
    void writeVUText_(sead::TextWriter* writer, const sead::SafeString& label,
                     f32 value, f32 secondary_value) const;

    u8 _30[0x35 - 0x30];
    /// Set from AudioFrameProcessMgr::addProcess's result in updateActivation (0x7100baa2f8).
    bool mIsFrameProcessAdded;
    /// Set by updateActivation when there is no AudioFrameProcessMgr to add the measure to.
    bool _36;
    bool mIsActive;
    u8 _38[0xe8 - 0x38];
    /// reset (0x7100baa0f8) sets both to -100; analyze_ writes them, calc takes the maximum of +0xe8.
    f32 _e8;
    f32 _ec;
    u8 _f0[0xf4 - 0xf0];
    f32 mVU[6];
    f32 mSamplePeak[6];
    u8 _124[0x130 - 0x124];
    AudioFrameProcessMgr* mFrameProcessMgr;
    u8 _138[0x158 - 0x138];
    /// Also keeps the measure active (updateActivation).
    bool _158;
    u8 _159[0x160 - 0x159];
    s32 mDisplayMode;
    sead::Vector2f _164;
    f32 _16c;
    u8 _170[0x17c - 0x170];
    f32 _17c;
    f32 _180;
    f32 _184;
    f32 _188;
    f32 _18c;
    f32 _190;
    f32 _194;
    f32 _198;
    f32 _19c[6];
    f32 _1b4[6];
    // Constructor initializes this to zero; both meter helpers compare it with 0.0f.
    f32 _1cc;
    u8 _1d0[0x1d4 - 0x1d0];
    // Constructor defaults and the native text helpers identify these threshold fields.
    f32 _1d4;
    f32 _1d8;
    f32 _1dc;
    f32 _1e0[3];
    f32 _1ec[3];
    f32 _1f8[3];
    sead::Color4f _204;
    u8 _214[4];
};
static_assert(sizeof(FinalOutputMeasure) == 0x218, "aal::FinalOutputMeasure size mismatch");

}  // namespace aal
