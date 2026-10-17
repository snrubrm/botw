#include "KingSystem/Sound/sndFxMgr.h"
#include "KingSystem/Sound/sndReverbMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include <aal/aalDecibel.h>
#include <aal/aalFxDelayParamSetter.h>
#include <aal/aalFxReverbI3DL2ParamSetter.h>

namespace ksys::snd {

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

void FxMgr::sub_71010514F4(sead::DrawContext* context, const sead::Camera& camera,
                         const sead::Projection& projection, const sead::Viewport& viewport) {
    if (_50)
        _50->sub_7101059C00(context, camera, projection, viewport);
}

}  // namespace ksys::snd

Unk_7102502640::~Unk_7102502640() = default;
