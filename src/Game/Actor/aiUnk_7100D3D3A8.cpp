#include "Game/Actor/aiUnk_7100D3D3A8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

Unk_7100d3d3a8::Unk_7100d3d3a8() = default;

void Unk_7100d3d3a8::sub_7100D3D3C4(int a, const sead::Vector3f* vec, const sead::Vector3f* b, u8 c) {
    if (_3)
        return;

    _0 = a;
    _2 = c;
    _8 = *vec;
    if (b)
        _14 = *b;
}

void Unk_7100d3d3a8::sub_7100D3D40C(ksys::act::Actor* actor, ksys::act::BaseProc* proc, bool flag) {
    ksys::act::ActorLinkConstDataAccess accessor(proc);
    sub_7100D3D49C(actor, &accessor, flag);
}

void Unk_7100d3d3a8::sub_7100D3D49C(ksys::act::Actor* actor, ksys::act::ActorLinkConstDataAccess* accessor, bool flag) {
    _4 = flag;
    actor->sendMessage(*accessor->getMessageTransceiverId(), ksys::MessageType(0x3000014), this, true);
    _3 = 1;
}
