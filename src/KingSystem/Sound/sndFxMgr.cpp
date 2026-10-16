#include "KingSystem/Sound/sndFxMgr.h"
#include "KingSystem/Sound/sndReverbMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include <aal/aalFxDelayParamSetter.h>

namespace ksys::snd {

void FxMgr::sub_7101050348() {
    sub_710105034C();
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
