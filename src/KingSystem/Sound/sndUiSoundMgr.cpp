#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

bool UiSoundMgr::playSound(const sead::SafeString& label, xlink2::HandleSLink* handle) {
    if (_20) {
        xlink2::HandleSLink h = _20->searchAndEmit(label.cstr());
        if (handle)
            *handle = h;
        return h.isActive();
    }
    return false;
}

}  // namespace ksys::snd
