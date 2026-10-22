// The TU at 0x71012ceddc ..: the second SLink event callback of SoundMgr::_70 (Unk_710251b7a0).
#include <aal/aalGroupMgr.h>
#include <aal/aalHandle.h>
#include <algorithm>
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <xlink2/xlink2ResourceAccessorSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
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

void Unk_SoundMgrB8::sub_71012D1F3C() {
    ++_8;
}

// 0x71012d1f4c (declared only; placeholder name): the priority / interior setup behind _350.
u32 sub_71012D1F4C(void* object, const xlink2::IEventCallbackSLink::EventArg& arg);

// 0x71012cf2c0: forwards to the object at _350.
u32 Unk_710251b7a0::soundPrePlay(const EventArg& arg) {
    return sub_71012D1F4C(_350, arg);
}

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

// NON_MATCHING: the bit moves of the NaN tests are scheduled after the first compare.
void Unk_710251b7a0::sub_71012CF50C(f32 volume, const EventArg& arg) {
    const auto& accessor = arg.pUserInstance->getResourceAccessor();
    const f32 base = accessor.getCustomParamValueFloat(0u, *arg.pAssetCallTable, arg.pUserInstance);
    const f32 scale1 = accessor.getCustomParamValueFloat(4, *arg.pAssetCallTable, arg.pUserInstance);
    f32 value = scale1 != 1.0f ? base * scale1 : base;
    const f32 scale2 = accessor.getCustomParamValueFloat(6, *arg.pAssetCallTable, arg.pUserInstance);
    value = scale2 != 1.0f ? value * scale2 : value;
    if (sead::Mathf::isNan(scale2) | sead::Mathf::isNan(scale1) | sead::Mathf::isNan(base) |
        sead::Mathf::isNan(volume))
        value = 0.0f;

    if (volume >= 0.0f)
        value *= volume;
    else if (value == 1.0f)
        return;
    arg.pHandle->setVolume(std::max(value, 0.0f));
}

}  // namespace ksys::snd
