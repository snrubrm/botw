#include "KingSystem/Sound/sndFxMgr.h"
#include "KingSystem/Sound/sndReverbMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include <aal/aalAuxBusMgr.h>
#include <aal/aalDecibel.h>
#include <aal/aalFxDelayParamSetter.h>
#include <aal/aalFxReverbI3DL2ParamSetter.h>

namespace ksys::snd {

// 0x71026140ce0 / 0x71026140ce4 / 0x71026140cf0: the reverb debug overrides (nothing in the game
// writes them): use the five override values instead of the reverb manager's, and keep the I3DL2
// parameters untouched.
KSYS_VISIBILITY_HIDDEN bool sUnk_71026140CE0;
KSYS_VISIBILITY_HIDDEN bool sUnk_71026140CE4;
KSYS_VISIBILITY_HIDDEN f32 sUnk_71026140CF0[5];

// 0x7102502540: the five-float reverb preset rows (row 0 is the no-preset row; the rest are zero).
KSYS_VISIBILITY_HIDDEN const f32 sUnk_7102502540[12][5] = {
    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    {0.144f, 0.0f, 0.543f, 610.0f, 1140.0f},
    {0.144f, 0.0f, 0.543f, 310.0f, 1140.0f},
    {0.144f, 0.0f, 0.543f, 310.0f, 1140.0f},
    {0.144f, 0.0f, 0.543f, 610.0f, 500.0f},
    {0.144f, 0.0f, 0.543f, 610.0f, 1140.0f},
};

void FxMgr::sub_7101050104() {
    if (!_50)
        return;

    _50->sub_71010599AC();

    f32 p0;
    f32 p1;
    f32 p2;
    f32 p3;
    f32 p4;
    if (sUnk_71026140CE0) {
        p0 = sUnk_71026140CF0[0];
        p1 = sUnk_71026140CF0[1];
        p2 = sUnk_71026140CF0[2];
        p3 = sUnk_71026140CF0[3];
        p4 = sUnk_71026140CF0[4];
    } else {
        p0 = _50->_60[0];
        p1 = _50->_60[1];
        p2 = _50->_60[2];
        p3 = _50->_60[3];
        p4 = _50->_60[4];

        const FxPreset preset = _b5 ? FxPreset::_5 : _b4 ? FxPreset::_4 : FxPreset(_a8);
        if (int(preset) != 0) {
            const f32* add = sUnk_7102502540[int(preset)];
            p0 += add[0];
            p1 += add[1];
            p2 += add[2];
            p3 += add[3];
            p4 += add[4];
        }
    }

    if (_64) {
        const f32* extra = _ac ? &_b0 : &_60;
        p0 += *extra;
    }

    f32 min_send = p0 + _58;
    if (min_send < 0.0f)
        min_send = 0.0f;
    else if (min_send > 1.0f)
        min_send = 1.0f;
    f32 max_send = p0 + _5c;
    if (max_send < 0.0f)
        max_send = 0.0f;
    else if (max_send > 1.0f)
        max_send = 1.0f;
    aal::AuxBusMgr::sInstance->setEnvFxSend(min_send, max_send, 0.0f);

    if (!_18)
        return;
    if (sUnk_71026140CE4)
        return;

    const f32 decay_time = p1 + _18->_14;
    f32 feedback = p2 + _18->_40;
    if (feedback < 0.0f)
        feedback = 0.0f;
    else if (feedback > 0.99f)
        feedback = 0.99f;
    const f32 room_hf = sead::Mathf::min(0.0f, static_cast<f32>(_18->_10) + p3);
    const f32 reverb = sead::Mathf::min(0.0f, static_cast<f32>(_18->_24) + p4);

    aal::FxReverbI3DL2ParamSetter setter;
    setter.setDecayTime(decay_time);
    setter.setEarlyReflectionFeedback(feedback);
    setter.setRoomHf(s32(room_hf));
    setter.setReverb(s32(reverb));
    if (_8)
        _8->updateParam(setter);
    if (_10)
        _10->updateParam(setter);
}

// NON_MATCHING: the original zeroes 0x98..0xad with two overlapping stores (0xa5 + 8, 0x98 + 16),
// as if the block were one packed 21-byte aggregate; our separate fields also zero 0xa8.
FxMgr::FxMgr() = default;

FxMgr::~FxMgr() {
    if (_8) {
        delete _8;
        _8 = nullptr;
    }
    if (_10) {
        delete _10;
        _10 = nullptr;
    }
    if (_68) {
        delete _68;
        _68 = nullptr;
    }
    if (_70) {
        delete _70;
        _70 = nullptr;
    }
    if (_50) {
        delete _50;
        _50 = nullptr;
    }
    mUsed.freeBuffer();
}

void FxMgr::sub_7101050348() {
    sub_710105034C();
}

sead::DirectResource* FxMgr::sub_7101051410(const sead::SafeString& path, sead::Heap* heap) {
    res::ResourceMgrTask::DirectLoadArg arg{};
    arg.req.mPath = path;
    arg.req.mLoadDataAlignment = 4;
    arg.heap = heap;
    return sead::DynamicCast<sead::DirectResource>(res::ResourceMgrTask::instance()->load(arg));
}

void FxMgr::sub_7101050CCC() {
    if (!_18)
        return;
    const f32 room = aal::Decibel::toDecibelTable(1.0f) + static_cast<f32>(_18->mRoom);
    aal::FxReverbI3DL2ParamSetter setter;
    setter.setRoom(s32(room), 0.0f);
    _8->updateParam(setter);
    _10->updateParam(setter);
}

void FxMgr::sub_7101051078() {
    if (_18) {
        const f32 room = aal::Decibel::toDecibelTable(0.0f) + static_cast<f32>(_18->mRoom);
        aal::FxReverbI3DL2ParamSetter setter;
        setter.setRoom(s32(room), 2.0f);
        _8->updateParam(setter);
        _10->updateParam(setter);
    }
    if (_68 && _70) {
        aal::FxDelayParamSetter setter;
        setter.setOutGain(0.0f, 2.0f);
        _68->updateParam(setter);
        _70->updateParam(setter);
    }
}

void FxMgr::sub_7101051154(f32 gain) {
    if (!_68 || !_70)
        return;
    aal::FxDelayParamSetter setter;
    setter.setOutGain(0.0f, gain);
    _68->updateParam(setter);
    _70->updateParam(setter);
}

void FxMgr::sub_710105126C() {
    if (!_68 || !_70)
        return;
    aal::FxDelayParamSetter setter;
    setter.setOutGain(1.0f, 0.1f);
    _68->updateParam(setter);
    _70->updateParam(setter);
}

void FxMgr::sub_71010511D4() {
    _a8 = 0;
}

void FxMgr::sub_71010511DC(f32 gain) {
    if (!_18)
        return;
    const f32 decibel = aal::Decibel::toDecibelTable(0.0f);
    const f32 room = decibel + f32(_18->mRoom);
    aal::FxReverbI3DL2ParamSetter setter;
    setter.setRoom(s32(room), gain);
    _8->updateParam(setter);
    _10->updateParam(setter);
}

void FxMgr::sub_71010514F4(sead::DrawContext* context, const sead::Camera& camera,
                         const sead::Projection& projection, const sead::Viewport& viewport) {
    if (_50)
        _50->sub_7101059C00(context, camera, projection, viewport);
}

}  // namespace ksys::snd

Unk_7102502640::~Unk_7102502640() = default;
