// The TU at 0x71012c629c .. 0x71012c7350: SoundMgr::_2a0 (Unk_SoundMgr2a0), the final output measure user.
#include <aal/aalDecibel.h>
#include <aal/aalFinalOutputMeasure.h>
#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalOutputDevice.h>
#include <aal/aalSettings.h>
#include <aal/aalSystemAccessor.h>
#include <algorithm>
#include <math/seadMathCalcCommon.h>
#include "Game/Scene/gameScene.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::snd {

// The level thresholds (0x710251b2d0, in .data): volume over now, volume over held (with the hold time), true
// peak over.
KSYS_VISIBILITY_HIDDEN f32 sUnk_710251b2d0[4] = {-13.0f, -14.0f, 0.5f, -3.0f};

// NON_MATCHING: the over kind's zero is materialised as w1 here where the original uses x1 (the 1 / 2 calls use
// w1 in both), and the delta-time / group checks are scheduled slightly differently. The threshold table is now a
// hidden global, so it is read with adrp + add like the original.
void Unk_SoundMgr2a0::sub_71012C629C() {
    if (!_8)
        return;
    auto* settings = aal::SystemAccessor::getSettings();
    if (!settings)
        return;
    auto* measure = settings->getOutputDevice(aal::DeviceType::TV)->getFinalOutputMeasure();
    if (!measure)
        return;

    if (_8 && !measure->isFrameProcessAdded())
        measure->activate();
    if (_30 > 0)
        --_30;
    if (_34 > 0)
        --_34;
    _14 = measure->get_e8();

    f32 peak = sead::Mathf::max(measure->getSamplePeak(aal::SpeakerChannel(0)), -100.0f);
    for (s32 i = 1; i < 6; ++i) {
        const f32 value = measure->getSamplePeak(aal::SpeakerChannel(i));
        if (value > peak)
            peak = value;
    }
    mSamplePeak = peak;

    f32 vu = sead::Mathf::max(measure->getVU(aal::SpeakerChannel(0)), -100.0f);
    for (s32 i = 1; i < 6; ++i) {
        const f32 value = measure->getVU(aal::SpeakerChannel(i));
        if (value > vu)
            vu = value;
    }
    mVU = vu;

    _20 = 0.0f;
    const f32 vu_volume = aal::Decibel::toVolume(vu);
    if (vu_volume > 0.0f)
        _20 = aal::Decibel::toVolume(mSamplePeak) / vu_volume;

    const f32 delta = VFR::instance()->getDeltaTime();
    if (_28 > 0.0f) {
        _28 = sead::Mathf::clampMin(_28 - delta, 0.0f);
        return;
    }

    if (auto* group_mgr = aal::SystemAccessor::getGroupMgr()) {
        if (auto* group = group_mgr->findGroup(aal::GroupMgr::getDummyGroupName())) {
            if (group->getDuckingCount() > 0) {
                _30 = 30;
                return;
            }
        }
    }
    if (_30 > 0 || _34 > 0)
        return;
    if (sub_71012C6614())
        return;

    if (_14 > sUnk_710251b2d0[0]) {
        sub_71012C679C(0, "音量オーバー(即時)");
    } else if (_14 > sUnk_710251b2d0[1]) {
        if (_24 < sUnk_710251b2d0[2]) {
            _24 += delta;
            if (!(_24 < sUnk_710251b2d0[2]))
                sub_71012C679C(1, "音量オーバー(持続)");
        }
    } else {
        _24 = 0.0f;
    }

    if (mSamplePeak > sUnk_710251b2d0[3])
        sub_71012C679C(2, "トゥルーピークオーバー");
}

bool Unk_SoundMgr2a0::sub_71012C6614() {
    if ((getSceneStatus() & ~1) == 4)
        return true;
    if (tera::checkTeraSystemStatus())
        return true;
    const auto& map_type = StageInfo::getCurrentMapType();
    return !(map_type == "MainField" || map_type == "MainFieldDungeon" || map_type == "CDungeon");
}

void Unk_SoundMgr2a0::sub_71012C6DC4() {
    if (_8)
        return;
    auto* settings = aal::SystemAccessor::getSettings();
    if (!settings)
        return;
    if (auto* measure = settings->getOutputDevice(aal::DeviceType::TV)->getFinalOutputMeasure()) {
        measure->activate();
        _8 = true;
        _2c = true;
    }
}

}  // namespace ksys::snd
