#pragma once

#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/UI/euiScreen.h"

namespace eui {

// Placeholder name: the first base of the sound link user object of a screen (a vtable only).
class ScreenSoundLinkUserPrimary {
public:
    virtual void m0();
};

// Placeholder name: the 0x18-byte object created by Screen::createSoundLink2User_ (0x7100beb9b0): a primary vtable,
// the ScreenSoundLinkUser base at +8 (the object `Screen::_f0` points to) and the xlink2 user instance at +0x10.
class ScreenSoundLinkUserImpl : public ScreenSoundLinkUserPrimary, public ScreenSoundLinkUser {
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

}  // namespace eui
