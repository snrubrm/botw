#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

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

bool UiSoundMgr::emitGetItemSound(const sead::SafeString& label) {
    if (!_18)
        return false;
    if (_84 & 1)
        _88.log("[GetItemSound] %s", label.cstr());
    auto handle = eft::searchAndEmitSLink(_18, label.cstr(), true);
    if (handle.isActive())
        return true;
    if (label.findIndex("Rupee") != -1) {
        handle = eft::searchAndEmitSLink(_18, "Rupee", true);
        if (handle.isActive())
            return true;
    }
    if (label.findIndex("Weapon") != -1) {
        handle = eft::searchAndEmitSLink(_18, "Weapon", true);
        if (handle.isActive())
            return true;
    }
    handle = eft::searchAndEmitSLink(_18, "Default", true);
    return handle.isActive();
}

}  // namespace ksys::snd
