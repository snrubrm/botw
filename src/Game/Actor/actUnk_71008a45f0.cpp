#include "Game/Actor/actCameraUtil.h"

namespace uking::act {

Unk_71008a45f0::Unk_71008a45f0() : _0(sead::Matrix33f::ident), _24(sead::Matrix33f::ident) {
    _d8 = 0;
    _da = 0;
}

void Unk_71008a45f0::sub_71008A4644() {
    if (_da) {
        _da = 0;
        _0.makeIdentity();
        _24.makeIdentity();
        _b4.makeIdentity();
        _d8 = 0;
    }
}

}  // namespace uking::act
