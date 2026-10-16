#include "Game/Actor/Behavior/behaviorCameraNotify2Sound.h"
#include "KingSystem/Sound/sndSound.h"

namespace uking::behavior {

namespace {

struct SoundState {
    s32 mode;
    void (ksys::snd::Unk_710104e5b4::*enter)();
    void (ksys::snd::Unk_710104e5b4::*leave)();
};
static_assert(sizeof(SoundState) == 0x28);

SoundState sSoundStates[] = {
    {1, &ksys::snd::Unk_710104e5b4::sub_710104F420, &ksys::snd::Unk_710104e5b4::sub_710104F438},
    {2, &ksys::snd::Unk_710104e5b4::sub_710104F3EC, &ksys::snd::Unk_710104e5b4::sub_710104F404},
    {3, &ksys::snd::Unk_710104e5b4::sub_710104F454, &ksys::snd::Unk_710104e5b4::sub_710104F46C},
    {4, &ksys::snd::Unk_710104e5b4::sub_710104F488, &ksys::snd::Unk_710104e5b4::sub_710104F4A0},
};

}  // namespace


CameraNotify2Sound::CameraNotify2Sound(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

bool CameraNotify2Sound::init_(sead::Heap* heap) {
    const u32 state = *mCameraStateNotify2Sound_s;
    _30 = state < 4 ? state : 0;
    return true;
}

// NON_MATCHING: the compiler specializes the known nonvirtual member-pointer table dispatch.
void CameraNotify2Sound::enter() {
    const u32 state = *mCameraStateNotify2Sound_s;
    _30 = state < 4 ? state : 0;
    if (auto* manager = ksys::snd::SoundMgr::instance()) {
        if (manager->_58)
            manager->_58->_78 = sSoundStates[_30].mode;
    }
    if (auto* sound = ksys::snd::Unk_710104e5b4::instance())
        (sound->*sSoundStates[_30].enter)();
}

// NON_MATCHING: the compiler specializes the known nonvirtual member-pointer table dispatch.
void CameraNotify2Sound::leave() {
    if (auto* manager = ksys::snd::SoundMgr::instance()) {
        if (manager->_58)
            manager->_58->_78 = 0;
    }
    if (auto* sound = ksys::snd::Unk_710104e5b4::instance())
        (sound->*sSoundStates[_30].leave)();
}

void CameraNotify2Sound::loadParams() {
    getStaticParam(&mCameraStateNotify2Sound_s, "CameraStateNotify2Sound");
}

}  // namespace uking::behavior
