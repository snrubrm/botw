#include "Game/AI/aiUnk_71025ba778.h"
#include "KingSystem/ActorSystem/actActor.h"

void Unk_71025ba778::sub_710070F350(ksys::act::Actor* actor) {
    if (!actor)
        return;
    if (!_100._8)
        actor->boneHandleStuff(&_18, false);
    _8 |= 1;
}

void Unk_71025ba778::sub_710070F79C(ksys::act::Actor* actor) {
    if (!actor)
        return;
    if (!_100._8) {
        _100.setName("Man_Spine_1");
        actor->boneHandleStuff(&_100, true);
    }
    _8 |= 2;
}

void Unk_71025ba778::sub_710070F820(ksys::act::Actor* actor) {
    _8 &= ~2;
}

void Unk_71025ba778::sub_710070F398(ksys::act::Actor* actor) {
    if (!actor || !(_8 & 1))
        return;
    actor->sub_71011DA868(&_18);
    _8 &= ~1;
    if (_100._8) {
        _8 &= ~2;
        actor->sub_71011DA868(&_100);
    }
}
