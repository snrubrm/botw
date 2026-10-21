// The TU at 0x71012ceddc ..: the second SLink event callback of SoundMgr::_70 (Unk_710251b7a0).
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include "KingSystem/Sound/sndSoundAttenuationMgr.h"

namespace ksys::snd {

namespace {

// Removes the groups that are in the array more than once (the first copy stays).
void removeDuplicates(sead::PtrArray<aal::Group>& groups) {
    for (s32 i = 0; i < groups.size() - 1; ++i) {
        for (s32 j = i + 1; j < groups.size();) {
            if (groups(i) == groups(j))
                groups.erase(j);
            else
                ++j;
        }
    }
}

void pushGroup(aal::GroupMgr* mgr, sead::PtrArray<aal::Group>& groups, const sead::SafeString& name) {
    if (auto* group = mgr->findGroup(name))
        aal::GroupMgr::pushDescendantsAndSelfGroupArray(&groups, group);
}

}  // namespace

Unk_710251b7a0::Unk_710251b7a0() = default;

Unk_710251b7a0::~Unk_710251b7a0() = default;

void Unk_710251b7a0::sub_71012CEE90(sead::Heap* heap) {}

// NON_MATCHING: the first duplicate loop's entry test is `size < 2` here (`size <= 1` in the original).
void Unk_710251b7a0::sub_71012CEE94() {
    auto* mgr = aal::SystemAccessor::getGroupMgr();
    if (!mgr)
        return;

    mIndoorOutdoorGroups.clear();
    pushGroup(mgr, mIndoorOutdoorGroups, "EnvIndoor");
    pushGroup(mgr, mIndoorOutdoorGroups, "EnvIndoorOnly");
    pushGroup(mgr, mIndoorOutdoorGroups, "EnvOutdoor");
    pushGroup(mgr, mIndoorOutdoorGroups, "EnvInAndOut");
    pushGroup(mgr, mIndoorOutdoorGroups, "ChemicalFireIndoor");
    pushGroup(mgr, mIndoorOutdoorGroups, "ChemicalFireOutdoor");
    pushGroup(mgr, mIndoorOutdoorGroups, "ObjIndoor");
    pushGroup(mgr, mIndoorOutdoorGroups, "ObjOutdoor");
    removeDuplicates(mIndoorOutdoorGroups);

    mLifeGroups.clear();
    pushGroup(mgr, mLifeGroups, "Life");
    pushGroup(mgr, mLifeGroups, "EnvOutdoorLife");
    removeDuplicates(mLifeGroups);

    mFootstepGroups.clear();
    pushGroup(mgr, mFootstepGroups, "PlayerFootstep");

    mGrassShakeGroups.clear();
    pushGroup(mgr, mGrassShakeGroups, "ObjGrassShake");
    pushGroup(mgr, mGrassShakeGroups, "ObjOutdoor");
    removeDuplicates(mGrassShakeGroups);
}

}  // namespace ksys::snd
