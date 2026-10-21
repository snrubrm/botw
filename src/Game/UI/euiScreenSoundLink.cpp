#include <xlink2/xlink2SystemELink.h>
#include <xlink2/xlink2UserInstanceELink.h>
#include <prim/seadStringBuilder.h>
#include <xlink2/xlink2ToolConnectionContext.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiEffectLinkUser.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/euiScreenSoundLinkUser.h"
#include "Game/UI/euiTextSearcher.h"

namespace eui {

// 0x71009cf5b4
void Screen::createEffectLinkUser_(sead::Heap* heap, u32 count) {
    if (count == 0)
        return;
    auto* user = new (heap, 8) EffectLinkUser;
    user->initialize(heap, count, mLayout, _c8.cstr());
    _e8 = user;
}

// 0x71009cf66c
void Screen::invokeSoundLink2Event_(const char* name) {
    static_cast<SoundLink2User*>(_f0)->searchAndEmit(name);
}

// 0x71009cf6b0
void Screen::invokeSoundLink2ButtonEvent_(AnimButton* button, const char* name) {
    sead::FixedStringBuilder<256> label;
    CreateLayoutItemUniqueName(&label, button->mName,
                               button->mFlags & 0x2000 ? button->mLayout->_88 : button->mLayout);
    label.append(name, -1);
    xlink2::HandleSLink handle = static_cast<SoundLink2User*>(_f0)->searchAndEmit(label.cstr());
    if (handle.isActive())
        return;
    label.copy("button", -1);
    label.append(name, -1);
    static_cast<SoundLink2User*>(_f0)->searchAndEmit(label.cstr());
}

// 0x71009cf7d4
void Screen::invokeSoundLink2AnimPlayEvent(Animator* animator, const char* name) {
    sead::FixedStringBuilder<256> label;
    label.copy("anim_", -1);
    AppendLayoutItemUniqueName(&label, animator->mName, animator->mLayout);
    label.append(name, -1);
    static_cast<SoundLink2User*>(_f0)->searchAndEmit(label.cstr());
}

// 0x71009cfb14
void EffectLinkUser::initialize(sead::Heap* heap, s32 num_bones, LayoutEx* layout, const char* name) {
    mBones.tryAllocBuffer(num_bones, heap, 16);
    s32 num_slots;
    {
        Unk_7100be81bc ctx(layout, heap, &mBones);
        num_slots = sub_7100BE81CC(layout->GetPane(), 0, &ctx);
    }
    mActionSlots.tryAllocBuffer(num_slots, heap, 8);
    mNumActions = sub_7100BE86F8(&mActionSlots, &mBones, heap);

    const u32 size = sead::SafeString(name).calcLength() + 5;
    sead::BufferedSafeString user_name(static_cast<char*>(heap->alloc(size, 8)), size);
    user_name.format("[UI]%s", name);

    xlink2::UserInstance::CreateArg arg(user_name.cstr(), this);
    arg.numActionSlot = mNumActions;
    const char** names = new (heap, 8) const char*[mNumActions];
    for (s32 i = 0; i < mNumActions; ++i)
        names[i] = mActionSlots[i].mName;
    arg.actionSlotNames = names;
    arg.rootMtx.reset();
    mUserInstance = xlink2::SystemELink::instance()->createUserInstance(arg, heap, 0);
    mUserInstance->setupResource(heap);
    static_cast<xlink2::UserInstanceELink*>(mUserInstance)->setDefaultGroup(sub_7100BE8F04(layout));
    mUserInstance->setIsActive(false);
}

// 0x71009cfe08
sead::Matrix34f* EffectLinkUser::getBoneWorldMtxPtr(const char* name) const {
    for (const auto& bone : mBones) {
        const char* bone_name = bone.mName;
        bool equal = true;
        for (s32 j = 0; j < 128; ++j) {
            if (name[j] != bone_name[j]) {
                equal = false;
                break;
            }
            if (name[j] == '\0')
                break;
        }
        // IUser returns a mutable matrix pointer from a const function
        if (equal)
            return const_cast<sead::Matrix34f*>(&bone.mMtx);
    }
    return nullptr;
}

// 0x71009cfe70
const char* EffectLinkUser::getActionSlotName(s32 action_slot_idx) const {
    return mActionSlots[action_slot_idx].mName;
}

// 0x71009cfeb0
void EffectLinkUser::getReservedAssetName(xlink2::ToolConnectionContext* ctx) const {
    const u16 num_actions = mNumActions;
    const ActionSlot* slots = mActionSlots.getBufferPtr();
    for (s32 i = 0; i < num_actions; ++i)
        ctx->addLabel(slots[i].mName);
}

// 0x71009cfef8
u32 EffectLinkUser::getNumBone() const {
    return mBones.size();
}

// 0x71009cff00
const char* EffectLinkUser::getBoneName(s32 bone_idx) const {
    return mBones[bone_idx].mName;
}

// 0x71009cff20
u32 EffectLinkUser::getNumAction(s32) const {
    return 2;
}

// 0x71009cff28
char* EffectLinkUser::getActionName(s32, s32 index) const {
    // IUser returns a mutable pointer; the names are literals
    if (index == 0)
        return const_cast<char*>("normal");
    if (index == 1)
        return const_cast<char*>("reverse");
    return const_cast<char*>("");
}

// 0x71009cff54
void EffectLinkUser::captureScreen(const char*) {}

// 0x71009cff58
f32 EffectLinkUser::getSortKey(const sead::Vector3f&) const {
    return 0.0f;
}

// 0x71009cff60
sead::Matrix34f EffectLinkUser::getAutoInputMtxSource() const {
    return sead::Matrix34f::ident;
}

// 0x71009cff74
sead::Matrix34f EffectLinkUser::getMtxCorrectingDrawBone() const {
    return sead::Matrix34f::ident;
}

// 0x71009cff88
void EffectLinkUser::m2() {
    mUserInstance->destroy();
}

// 0x71009cff90: starts, follows and stops the action of each slot with the playback of its animator
void EffectLinkUser::m0() {
    const u16 num_actions = mNumActions;
    ActionSlot* slots = mActionSlots.getBufferPtr();
    for (s32 i = 0; i < num_actions; ++i) {
        Animator* animator = slots[i].mAnimator;
        if (!animator)
            continue;

        bool active = false;
        if (animator->mEnabled) {
            const s32 frame = animator->mRate >= 0 ? s32(animator->mFrame) :
                                                     s32(animator->GetFrameSize() - animator->mFrame);
            if (slots[i].mActive)
                mUserInstance->setActionFrame(frame, i);
            else
                mUserInstance->changeAction(getActionName(0, animator->mRate >= 0 ? 0 : 1), frame, i);
            active = true;
        } else if (slots[i].mActive) {
            mUserInstance->stopAction(i);
        }
        slots[i].mActive = active;
    }
}

// 0x71009d0144
void EffectLinkUser::m3() {
    mUserInstance->setIsActive(true);
    const u16 num_actions = mNumActions;
    ActionSlot* slots = mActionSlots.getBufferPtr();
    for (s32 i = 0; i < num_actions; ++i)
        slots[i].mActive = false;
}

// 0x71009d01d0
void EffectLinkUser::m4() {
    mUserInstance->setIsActive(false);
}

}  // namespace eui
