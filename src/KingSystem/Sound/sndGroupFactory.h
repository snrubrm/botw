#pragma once

#include <aal/aalGroupMgr.h>

namespace ksys::snd {

// The group factory of the sound system (vtable 0x710251b6b8; SoundMgr::_c0, created by Sound::init). Every group
// it creates gets an Unk_710251b678 (group user data) at aal::Group +0x98.
class Unk_710251b6b8 : public aal::GroupFactory {
public:
    Unk_710251b6b8();
    aal::SoundGroup* createSoundGroup(const sead::SafeString& name, sead::Heap* heap) override;
    aal::GroupFolder* createGroupFolder(const sead::SafeString& name, sead::Heap* heap) override;
    void destroyGroup(aal::Group* group) override;
};

}  // namespace ksys::snd
