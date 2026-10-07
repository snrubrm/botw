#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/System/StageInfo.h"

namespace ksys::snd {

void UiSoundMgr::sub_710105D0E4(sead::Heap* heap) {}

UiSoundMgr::UiSoundMgr() : _88("UiSoundMgr") {}

UiSoundMgr::~UiSoundMgr() {
    if (_20) {
        _20->destroy();
        _20 = nullptr;
    }
}

void UiSoundMgr::sub_710105D23C(sead::Heap* heap, act::ActorCreator* creator) {
    if (!creator)
        return;
    if (StageInfo::getCurrentMapType() != "TitleMenu")
        creator->requestCreateActor("GetItemSound", heap, &_8, nullptr, nullptr, 1);
}

void UiSoundMgr::sub_710105D308() {
    _8.deleteProc();
    _18 = nullptr;
}

void UiSoundMgr::sub_710105D9F8(aal::SoundSource* source) {
    _48.attachSoundSource(source);
    _58.moveTo(0.0f, 0.2f);
    _80 |= 0x10;
}

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
