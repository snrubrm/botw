#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <nn/ui2d/AnimTransform.h>
#include <nn/ui2d/Group.h>
#include "Game/UI/euiControlBase.h"

namespace sead {
class Heap;
}

namespace eui {

class LayoutEx;

// The eui animation player (CSV eui::Animator; 0x68 bytes, vtable 0x24c8d50 with 28 slots). Names of the fields are
// guesses.
class Animator : public nn::ui2d::AnimTransformBasic {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::AnimTransformBasic)

    enum PlayType : s32 {};

    Animator();
    ~Animator() override;

    void UpdateFrame(f32 frame) override;
    void SetEnabled(bool enabled) override;

    // Slots 21-27.
    virtual void Play(PlayType type, f32 speed);
    virtual void PlayAuto(f32 speed);
    virtual void PlayFromCurrent(PlayType type, f32 speed);
    virtual void Stop(f32 frame);
    virtual void StopCurrent();
    virtual void StopAtMin();
    virtual void StopAtMax();

    // 0x7100be743c / 0x7100be7484 / 0x7100be74e0
    void SetupBasic(const nn::ui2d::AnimResource& res, LayoutEx* layout, bool enabled);
    void SetupWithGroup(const nn::ui2d::AnimResource& res, LayoutEx* layout, nn::ui2d::Group* group,
                        bool enabled);
    void SetupWithGroupAll(const nn::ui2d::AnimResource& res, LayoutEx* layout,
                           nn::ui2d::GroupContainer* groups, bool enabled);
    // 0x7100be79fc (placeholder name): disables the animator and unlinks it from the screen's list
    void Disable();
    // 0x7100be782c (placeholder name)
    void PlayFromFrame(PlayType type, f32 start_frame, f32 speed);
    // 0x7100be7840: starts at a random frame
    void PlayRandom(PlayType type, f32 speed);
    // 0x7100be78bc (placeholder name): continues the other animator's playback
    void ContinueFrom(const Animator& other);

    /* 0x40 */ ListNode _40;
    /* 0x50 */ f32 mRate = 0;
    /* 0x54 */ u16 _54 = 0;
    /* 0x56 */ u8 mPlayType = 0;
    /* 0x57 */ u8 mFlags = 0x20;  // 0x10: skip first frame, 0x20: sound link
    /* 0x58 */ LayoutEx* mLayout = nullptr;
    /* 0x60 */ const char* mName = nullptr;
};
static_assert(sizeof(Animator) == 0x68);

// A group of animators (one per button state); `mCurrent` is the selected one.
class AnimatorSet {
public:
    AnimatorSet();
    AnimatorSet(const AnimatorSet& other, LayoutEx* layout, sead::Heap* heap);
    // 0x7100be7f18 (D1: `ret`) / 0x7100be7f1c (D0)
    virtual ~AnimatorSet();

    // 0x7100be7e40 / 0x7100be7f20
    void allocBuffer(u32 count, sead::Heap* heap);
    void setBuffer(u32 count, Animator** buffer);

    // 0x7100be7fdc: disables the current animator and selects `idx` (clamped to the buffer)
    Animator* select(u32 idx);
    // 0x7100be7fb4
    void setAnimator(u32 idx, Animator* animator);
    void SetSkipFirstFrameAll(bool skip);
    void SetSoundLinkAll(bool on);

    /* 0x08 */ sead::Buffer<Animator*> mAnimators;
    /* 0x18 */ Animator* mCurrent = nullptr;
};
static_assert(sizeof(AnimatorSet) == 0x20);

}  // namespace eui
