#include "Game/AI/aiUnk_71025ba778.h"
#include "KingSystem/ActorSystem/actActor.h"

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
