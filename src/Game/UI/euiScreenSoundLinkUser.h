#pragma once

#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2IUser.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/UI/euiScreen.h"

namespace eui {

// Placeholder name: the 0x18-byte object allocated by Screen::createSoundLink2User_
// (0x7100beb7e0). Initialization at 0x7100beb9b0 passes its primary base to
// CreateArgSLink as IUser*. Screen::_f0 points to the secondary base at +8.
// This remains a partial, abstract pointer model: the primary overrides and
// their unresolved matrix-slot identities are not reconstructed here.
class ScreenSoundLinkUserImpl : public xlink2::IUser, public ScreenSoundLinkUser {
public:
    // inline-only in the original; name is a guess (Screen::invokeSoundLink2*Event* discard the result; the empty
    // handle is stored in the other arm)
    xlink2::HandleSLink searchAndEmit(const char* name) {
        if (mUser)
            return mUser->searchAndEmit(name);
        return {};
    }

    xlink2::UserInstanceSLink* mUser;
};
static_assert(sizeof(ScreenSoundLinkUserImpl) == 0x18);
static_assert(offsetof(ScreenSoundLinkUserImpl, mUser) == 0x10);

}  // namespace eui
