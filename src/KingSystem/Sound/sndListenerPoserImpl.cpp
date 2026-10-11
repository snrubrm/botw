#include "KingSystem/Sound/sndListenerPoserImpl.h"
#include <aal/aalMeter.h>
#include <aal/aalListenerMgr.h>
#include <aal/aalSettings.h>
#include <aal/aalSystemAccessor.h>
#include <heap/seadHeap.h>

// NON_MATCHING: LookAtCamera member initialization uses different stores and scheduling.
ksys::snd::Unk_710251b1f0* sub_71012C5810(const sead::SafeString& name, sead::Heap* heap) {
    if (aal::SystemAccessor::getListenerMgr()->findListenerPoser(name))
        return nullptr;
    return new (heap, 8) ksys::snd::Unk_710251b1f0(name);
}

namespace ksys::snd {

Unk_710251b1f0::~Unk_710251b1f0() {
    // Preserve the native vtable stores before member destruction, as in
    // GameDataFlagSelector's empty-statement destructor (upstream 96101229).
    ;
}

void Unk_710251b1f0::reset() {
    mTarget = nullptr;
    _70 = sead::Vector3f::zero;
    auto* settings = aal::SystemAccessor::getSettings();
    _80 = sead::Vector3f::zero;
    _8c = sead::Vector3f::ez;
    _98 = sead::Vector3f::ey;
    _7d = false;
    _b0.setValueImmediate(1.0f);
    _a4 = sead::Vector3f::zero;
    if (settings)
        settings->mDopplerMode = 0;
    _148 = 0.0f;
    _7c = false;
    _e0 = false;
    _dc = 0.0f;
}


void Unk_710251b1f0::sub_71012C6090(const sead::Vector3f& position) {
    _70 = aal::Meter::toLength(position);
}

void Unk_710251b1f0::sub_71012C60C0(f32 value) {
    if (value <= 0.0f) {
        value = 0.0f;
        _7d = true;
    }
    _dc = value;
}

}  // namespace ksys::snd
