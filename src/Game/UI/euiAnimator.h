#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <nn/font/font_Util.h>
#include "Game/UI/euiControlBase.h"

namespace sead {
class Heap;
}

namespace eui {

class LayoutEx;

// nn::ui2d::AnimTransform / AnimTransformBasic placeholders (the SDK sources are not in lib/NintendoSDK): only
// the vtable layout (slots 3-20; slot 0 is the nn-style runtime type info, 1 / 2 the destructor) and the functions
// called from eui are declared.
}  // namespace eui

namespace nn::ui2d {

class Pane;
class Material;
class Group;
class GroupContainer;
class AnimResource;

class AnimTransform {
public:
    NN_RUNTIME_TYPEINFO_BASE()
    virtual ~AnimTransform();
    virtual void UpdateFrame(f32 frame);
    virtual void SetEnabled(bool enabled);

    u16 GetFrameSize() const;
    bool IsLoopData() const;
    bool IsWaitData() const;

    u8 _8[0x20 - 0x8];
    /* 0x20 */ f32 mFrame;
    u8 _24[0x40 - 0x24];
};

class AnimTransformBasic : public AnimTransform {
public:
    NN_RUNTIME_TYPEINFO(AnimTransform)
    AnimTransformBasic();
    ~AnimTransformBasic() override;

    virtual void Animate();
    virtual void AnimatePane(Pane* pane);
    virtual void AnimateMaterial(Material* material);
    virtual void SetResource0();
    virtual void SetResource1();
    virtual void BindPane(Pane* pane, bool recursive);
    virtual void BindGroup(Group* group);
    virtual void BindMaterial(Material* material);
    virtual void ForceBindPane(Pane* pane, const Pane* src);
    virtual void UnbindPane(const Pane* pane);
    virtual void UnbindGroup(const Group* group);
    virtual void UnbindMaterial(const Material* material);
    virtual void UnbindAll();
    virtual void AnimatePaneImpl();
    virtual void AnimateMaterialImpl();
    virtual void AnimateExtUserDataImpl();
};

}  // namespace nn::ui2d

namespace eui {

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

    virtual void Play(PlayType type, f32 frame);
    virtual void PlayAuto(f32 frame);
    virtual void PlayFromCurrent(PlayType type, f32 frame);
    virtual void Stop(f32 frame);
    virtual void StopCurrent();
    virtual void StopAtMin();
    virtual void StopAtMax();

    /* 0x40 */ ListNode _40;
    /* 0x50 */ f32 mRate = 0;
    /* 0x54 */ u16 _54 = 0;
    /* 0x56 */ u8 mPlayType;
    /* 0x57 */ u8 mFlags;  // 0x10: skip first frame, 0x20: sound link
    /* 0x58 */ LayoutEx* mLayout = nullptr;
    /* 0x60 */ const char* mName = nullptr;
};
static_assert(sizeof(Animator) == 0x68);

// A group of animators (one per button state); `mCurrent` is the selected one.
class AnimatorSet {
public:
    AnimatorSet();
    AnimatorSet(const AnimatorSet& other, LayoutEx* layout, sead::Heap* heap);
    virtual ~AnimatorSet() = default;

    // 0x7100be7fdc: disables the current animator and selects `idx` (clamped to the buffer)
    Animator* select(u32 idx);
    void SetSkipFirstFrameAll(bool skip);
    void SetSoundLinkAll(bool on);

    /* 0x08 */ sead::Buffer<Animator*> mAnimators;
    /* 0x18 */ Animator* mCurrent = nullptr;
};
static_assert(sizeof(AnimatorSet) == 0x20);

}  // namespace eui
