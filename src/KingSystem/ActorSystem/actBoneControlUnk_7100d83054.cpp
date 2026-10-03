#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace ksys::act {

Unk_7100d83054::Unk_7100d83054(Actor* actor) : mActor(actor) {}

void Unk_7100d83054::sub_7100D838A8() {
    if (_30.isBufferReady()) {
        for (u32 i = 0; i < _40; ++i)
            mActor->sub_71011DA868(&_30[i]._28);
        _30.freeBuffer();
    }
}

void Unk_7100d83054::sub_7100D839A8() {
    for (u32 i = 0; i < _40; ++i) {
        _30[i]._188 = 0;
        _30[i]._18c = 0;
    }
    _24 &= ~0x3008;
}

void Unk_7100d83054::sub_7100D852EC() {
    _24 |= 0x10;
    for (u32 i = 0; i < _40; ++i) {
        _30[i]._188 = 0;
        _30[i]._18c = 0;
        _30[i]._28._68 = sead::Matrix34f::ident;
    }
}

}  // namespace ksys::act
