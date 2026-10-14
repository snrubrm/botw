#include "Game/AI/aiUnk_710073E688.h"
#include "Game/AI/aiUnk_7100D3D3A8.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

Unk_710073e688::Unk_710073e688() = default;

Unk_710073e688::~Unk_710073e688() {
    if (_18.isBufferReady()) {
        for (s32 i = 0; i < _18.size(); ++i)
            delete _18[i];
        _18.freeBuffer();
    }
}

bool Unk_710073e688::sub_710073E730(sead::Heap* heap, s32 count,
                                    ksys::act::Actor* actor) {
    _0 = actor;
    _18.tryAllocBuffer(count, heap, 8);
    if (!_18.isBufferReady())
        return false;
    _18.fill(nullptr);
    for (s32 i = 0; i < _18.size(); ++i) {
        _18[i] = new (heap, 8) Unk_7100d3d3a8;
        if (!_18[i])
            return false;
    }
    return true;
}

void Unk_710073e688::sub_710073E8C4(ksys::act::BaseProcLink* link,
                                    const sead::Vector3f* target) {
    if (_18.size() <= _28)
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    sead::Vector3f acceleration;
    sub_71005DE398(&acceleration, link, target, _c, _8, _10);
    _18[_28]->sub_7100D3D3C4(0, &acceleration, nullptr, 1);
    _18[_28]->sub_7100D3D49C(_0, &accessor, false);
    ++_28;
}
