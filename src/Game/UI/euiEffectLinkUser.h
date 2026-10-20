#pragma once

#include <container/seadBuffer.h>
#include <math/seadMatrix.h>
#include <xlink2/xlink2IUser.h>
#include <xlink2/xlink2UserInstance.h>
#include "Game/UI/euiScreen.h"

namespace nn::ui2d {
class Pane;
}

namespace eui {

class Animator;
class LayoutEx;

// The effect link (ELink) user of a screen (0x40 bytes; created by Screen::createEffectLinkUser_, which keeps a pointer
// to the secondary base in Screen::_e8). Vtable 0x710247f430: 20 IUser / own slots, then the five ScreenUnkE8 slots.
class EffectLinkUser : public xlink2::IUser, public ScreenUnkE8 {
public:
    // One effect bone: a pane and its world matrix (0x60 bytes, allocated with 16-byte alignment).
    struct Bone {
        nn::ui2d::Pane* mPane = nullptr;
        void* _8 = nullptr;
        const char* mName = nullptr;
        u8 _18[0x20 - 0x18];
        /* 0x20 */ sead::Matrix34f mMtx;
        u8 _50[0x60 - 0x50];
    };
    static_assert(sizeof(Bone) == 0x60);

    // One action slot: an animator whose playback drives the xlink action of the same index.
    struct ActionSlot {
        Animator* mAnimator = nullptr;
        const char* mName = nullptr;
        bool mActive = false;
    };
    static_assert(sizeof(ActionSlot) == 0x18);

    // 0x71009cfb14 (declared only)
    void initialize(sead::Heap* heap, s32 num_bones, LayoutEx* layout, const char* name);

    sead::Matrix34f* getBoneWorldMtxPtr(const char* name) const override;
    const char* getActionSlotName(s32 action_slot_idx) const override;
    void getReservedAssetName(xlink2::ToolConnectionContext* ctx) const override;
    u32 getNumBone() const override;
    const char* getBoneName(s32 bone_idx) const override;
    u32 getNumAction(s32 slot) const override;
    char* getActionName(s32 slot, s32 index) const override;
    void captureScreen(const char* name) override;
    f32 getSortKey(const sead::Vector3f& pos) const override;
    sead::Matrix34f getAutoInputMtxSource() const override;
    sead::Matrix34f getMtxCorrectingDrawBone() const override;

    // Overrides of ScreenUnkE8, in the order of the primary vtable (slots 15 - 19): destroy the user instance, update
    // the actions from the animators, calculate, activate, deactivate.
    void m2() override;
    void m0() override;
    void m1() override;
    void m3() override;
    void m4() override;

    /* 0x10 */ xlink2::UserInstance* mUserInstance = nullptr;
    /* 0x18 */ sead::Buffer<Bone> mBones;
    /* 0x28 */ sead::Buffer<ActionSlot> mActionSlots;
    /* 0x38 */ u16 mNumActions = 0;
};
static_assert(sizeof(EffectLinkUser) == 0x40);

}  // namespace eui
