#include <random/seadGlobalRandom.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100be73c8
Animator::Animator() = default;

// 0x7100be7414 (D1), 0x7100be7418 (D0)
Animator::~Animator() = default;

// 0x7100be743c
void Animator::SetupBasic(const nn::ui2d::AnimResource& res, LayoutEx* layout, bool enabled) {
    mName = res.GetTagName();
    mLayout = layout;
    SetEnabled(enabled);
}

// 0x7100be7484
void Animator::SetupWithGroup(const nn::ui2d::AnimResource& res, LayoutEx* layout,
                              nn::ui2d::Group* group, bool enabled) {
    BindGroup(group);
    mName = res.GetTagName();
    mLayout = layout;
    SetEnabled(enabled);
}

// 0x7100be74e0
void Animator::SetupWithGroupAll(const nn::ui2d::AnimResource& res, LayoutEx* layout,
                                 nn::ui2d::GroupContainer* groups, bool enabled) {
    for (u32 i = 0, n = res.GetGroupCount(); i < n; ++i)
        BindGroup(groups->FindGroupByName(res.GetGroupArray()[i].name));
    mName = res.GetTagName();
    mLayout = layout;
    SetEnabled(enabled);
}

// 0x7100be76e0
bool Animator::PlayAuto(f32 speed) {
    return Play(PlayType(IsLoopData()), speed);
}

// 0x7100be782c
bool Animator::PlayFromFrame(PlayType type, f32 start_frame, f32 speed) {
    mFrame = start_frame;
    return PlayFromCurrent(type, speed);
}

// 0x7100be7840
bool Animator::PlayRandom(PlayType type, f32 speed) {
    const u16 frame_size = GetFrameSize();
    mFrame = sead::GlobalRandom::instance()->getU32(frame_size + 1u);
    return PlayFromCurrent(type, speed);
}

// NON_MATCHING: the original copies mFrame as a 32-bit integer (ldr w / str w), so `other.mRate` is not reloaded
// 0x7100be78bc
void Animator::ContinueFrom(const Animator& other) {
    if (other.mRate != 0) {
        mFrame = other.mFrame;
        PlayFromCurrent(PlayType(other.mPlayType), other.mRate);
    } else {
        Stop(other.mFrame);
    }
}

// 0x7100be78f0
void Animator::Stop(f32 frame) {
    mFlags &= 0xf0;
    mRate = 0;
    mFrame = frame;
    SetEnabled(true);
}

// 0x7100be7914
void Animator::StopCurrent() {
    mFlags &= 0xf0;
    mRate = 0;
    SetEnabled(true);
}

// 0x7100be7934
void Animator::StopAtMin() {
    mFlags &= 0xf0;
    mRate = 0;
    mFrame = 0;
    SetEnabled(true);
}

// 0x7100be7958
void Animator::StopAtMax() {
    mRate = 0;
    const f32 size = GetFrameSize();
    mFlags &= 0xf0;
    mFrame = size;
    SetEnabled(true);
}

// 0x7100be79a4
void Animator::SetEnabled(bool enabled) {
    nn::ui2d::AnimTransform::SetEnabled(enabled);
    if (enabled) {
        if (!_40.isLinked())
            mLayout->mScreen->addAnimator(this);
    } else {
        mRate = 0;
    }
}

// 0x7100be79fc
void Animator::Disable() {
    nn::ui2d::AnimTransform::SetEnabled(false);
    const bool linked = _40.isLinked();
    mRate = 0;
    if (linked)
        mLayout->mScreen->removeAnimator(this);
}

// NON_MATCHING: flag updates merge into register ORs and different shared blocks.
// 0x7100be7a4c
void Animator::UpdateFrame(f32 delta) {
    mFlags &= 0xf0;
    if (mRate == 0.0f)
        return;
    f32 frame = mFrame + mRate * delta;
    if (mRate > 0.0f) {
        if (frame >= GetFrameSize()) {
            switch (mPlayType) {
            case 0:
                frame = GetFrameSize();
                mRate = 0.0f;
                mFlags |= 1;
                break;
            case 1:
                frame -= GetFrameSize();
                mFlags |= 4;
                break;
            case 2:
                frame = GetFrameSize() - (frame - GetFrameSize());
                mRate = -mRate;
                mFlags |= 4;
                break;
            }
        }
    } else if (frame <= 0.0f) {
        switch (mPlayType) {
        case 0:
            frame = 0.0f;
            mRate = 0.0f;
            mFlags |= 1;
            break;
        case 1:
            frame += GetFrameSize();
            mFlags |= 8;
            break;
        case 2:
            frame = -frame;
            mRate = -mRate;
            mFlags |= 8;
            break;
        }
    }
    mFrame = frame;
}

// 0x7100be7c78
AnimatorSet::AnimatorSet() = default;

// 0x7100be7c94
AnimatorSet::AnimatorSet(const AnimatorSet& other, LayoutEx* layout, sead::Heap* heap) {
    if (other.mAnimators.size() == 0)
        return;
    allocBuffer(other.mAnimators.size(), heap);
    s32 i = 0;
    for (Animator* src : other.mAnimators) {
        if (src) {
            const bool is_current = src == other.mCurrent;
            mAnimators[i] = layout->createAnimatorAuto(src->mName, is_current);
            if (is_current)
                mCurrent = mAnimators[i];
        }
        ++i;
    }
}

// 0x7100be7e40
void AnimatorSet::allocBuffer(u32 count, sead::Heap* heap) {
    mAnimators.tryAllocBuffer(count, heap);
    const s32 size = mAnimators.size();
    for (s32 i = 0; i < size; ++i)
        mAnimators(i) = nullptr;
}

// 0x7100be7f20
void AnimatorSet::setBuffer(u32 count, Animator** buffer) {
    mAnimators.setBuffer(count, buffer);
    const s32 size = mAnimators.size();
    for (s32 i = 0; i < size; ++i)
        mAnimators(i) = nullptr;
}

// 0x7100be7fdc
Animator* AnimatorSet::select(u32 idx) {
    Animator* animator = mAnimators[idx];
    Animator* old = mCurrent;
    if (old != animator) {
        old->nn::ui2d::AnimTransform::SetEnabled(false);
        old->mRate = 0;
        mCurrent = animator;
    }
    return animator;
}

// 0x7100be8038
void AnimatorSet::SetSkipFirstFrameAll(bool skip) {
    for (Animator* animator : mAnimators) {
        if (animator) {
            if (skip)
                animator->mFlags |= 0x10;
            else
                animator->mFlags &= ~0x10;
        }
    }
}

// 0x7100be8094
void AnimatorSet::SetSoundLinkAll(bool on) {
    for (Animator* animator : mAnimators) {
        if (animator) {
            if (on)
                animator->mFlags |= 0x20;
            else
                animator->mFlags &= ~0x20;
        }
    }
}

// 0x7100be7fb4
void AnimatorSet::setAnimator(u32 idx, Animator* animator) {
    mAnimators[idx] = animator;
    if (!mCurrent)
        mCurrent = animator;
}

}  // namespace eui
