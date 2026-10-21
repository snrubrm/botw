#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include "aal/aalAudioFrameProcessMgr.h"
#include "aal/aalDeviceType.h"
#include "aal/aalSpeakerChannel.h"
#include "aal/aalWorkerThread.h"

namespace sead {
class DrawContext;
class Heap;
class TextWriter;
}  // namespace sead

namespace aal {

/// Measures the final output of a device. TODO: incomplete.
// Constructor 0x7100BA9B38 and table 0x71024C5A70 establish the three bases.
// Finalization independently unregisters the frame-process subobject at +0x10.
class FinalOutputMeasure : public WorkerTask, public IAudioFrameProcess, public sead::hostio::Node {
public:
    struct InitializeArg {
        f32 _0;
    };

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
    /// The different layouts of the information that drawInformation draws (declared only).
    void drawInformationSimple_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationSimpleStereo_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationSimpleSurround_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationFull_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalSimple_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalStereo_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalSurround_(sead::DrawContext* context, sead::TextWriter* writer) const;
    void drawInformationVerticalSimpleLFE_(sead::DrawContext* context, sead::TextWriter* writer) const;

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
    u8 _164[0x218 - 0x164];
};
static_assert(sizeof(FinalOutputMeasure) == 0x218, "aal::FinalOutputMeasure size mismatch");

}  // namespace aal
