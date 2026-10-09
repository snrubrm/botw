#include "KingSystem/Sound/sndFxMgr.h"
#include "KingSystem/Sound/sndReverbMgr.h"

namespace ksys::snd {

void FxMgr::sub_7101050348() {
    sub_710105034C();
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
