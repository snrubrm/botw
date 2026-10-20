#pragma once

#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2IUser.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/UI/euiScreen.h"

namespace eui {

// The sound link (SLink) user of a screen: the 0x18-byte object allocated by Screen::createSoundLink2User_
// (0x7100beb7e0). Initialization at 0x7100beb9b0 passes its primary base to CreateArgSLink as IUser*.
// Screen::_f0 points to the secondary base at +8. Vtable 0x71024c90d8 (21 primary slots, then the six
// ScreenSoundLinkUser slots).
class SoundLink2User : public xlink2::IUser, public ScreenSoundLinkUser {
public:
    sead::Matrix34f* getBoneWorldMtxPtr(const char* name) const override;
    void getReservedAssetName(xlink2::ToolConnectionContext* ctx) const override;
    u32 getNumBone() const override;
    const char* getBoneName(s32 bone_idx) const override;
    u32 getNumAction(s32 slot) const override;
    char* getActionName(s32 slot, s32 index) const override;
    void captureScreen(const char* name) override;
    f32 getSortKey(const sead::Vector3f& pos) const override;
    // folded with xlink2::IUser::getMtxCorrectingDrawBone (0x7100bebdf0) in the original
    sead::Matrix34f getAutoInputMtxSource() const override;

    // Overrides of ScreenSoundLinkUser, in the order of the primary vtable (slots 15 - 20).
    void m1() override;
    void m0() override;
    void m2() override;
    void m3() override;
    void setDrawTarget(s32 target) override;
    void setButtonProperty(s32 property) override;

    // inline-only in the original; name is a guess (Screen::invokeSoundLink2*Event* discard the result; the empty
    // handle is stored in the other arm)
    xlink2::HandleSLink searchAndEmit(const char* name) {
        if (mUser)
            return mUser->searchAndEmit(name);
        return {};
    }

    xlink2::UserInstanceSLink* mUser;
};
static_assert(sizeof(SoundLink2User) == 0x18);
static_assert(offsetof(SoundLink2User, mUser) == 0x10);

}  // namespace eui
