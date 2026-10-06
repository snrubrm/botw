#include <prim/seadStringBuilder.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/euiScreenSoundLinkUser.h"
#include "Game/UI/euiTextSearcher.h"

namespace eui {

// 0x71009cf66c
void Screen::invokeSoundLink2Event_(const char* name) {
    static_cast<ScreenSoundLinkUserImpl*>(_f0)->searchAndEmit(name);
}

// 0x71009cf6b0
void Screen::invokeSoundLink2ButtonEvent_(AnimButton* button, const char* name) {
    sead::FixedStringBuilder<256> label;
    CreateLayoutItemUniqueName(&label, button->mName,
                               button->mFlags & 0x2000 ? button->mLayout->_88 : button->mLayout);
    label.append(name, -1);
    xlink2::HandleSLink handle = static_cast<ScreenSoundLinkUserImpl*>(_f0)->searchAndEmit(label.cstr());
    if (handle.isActive())
        return;
    label.copy("button", -1);
    label.append(name, -1);
    static_cast<ScreenSoundLinkUserImpl*>(_f0)->searchAndEmit(label.cstr());
}

// 0x71009cf7d4
void Screen::invokeSoundLink2AnimPlayEvent(Animator* animator, const char* name) {
    sead::FixedStringBuilder<256> label;
    label.copy("anim_", -1);
    AppendLayoutItemUniqueName(&label, animator->mName, animator->mLayout);
    label.append(name, -1);
    static_cast<ScreenSoundLinkUserImpl*>(_f0)->searchAndEmit(label.cstr());
}

}  // namespace eui
