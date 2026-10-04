#include "Game/AI/aiUnk_710070E434.h"
#include "KingSystem/ActorSystem/actActor.h"

void Unk_710070e434::sub_710070E434(const sead::SafeString& name) {
    if (name.isEmpty()) {
        _c = false;
        _70.setName(name);
        return;
    }
    _c = true;
    _70.setName(name);
    _70._68 = sead::Matrix34f::ident;
    mActor->boneHandleStuff(&_70, false);
}

void Unk_710070e434::sub_710070E4C0() {
    mActor->sub_71011DA868(&_70);
    _c = false;
}

void Unk_710070e434::sub_710070E714() {
    _10.setMul(mActor->getMtx(), _40);
}
