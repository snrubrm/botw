#include "Game/Actor/actMapConst.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actDropData.h"

namespace uking::act {

MapConstActive::MapConstActive(const CreateArg& arg) : MapConstActiveOrMergedDungeonParts(arg) {
    _1c0 = 3;
}

MapConstActive::~MapConstActive() = default;

ksys::act::BaseProc* MapConstActive::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) MapConstActive(arg);
}

ksys::act::Unk_71025ae640* MapConstActive::getAtk() {
    return _850;
}

uking::dmg::DamageManagerBase* MapConstActive::getDamageMgr() {
    return _858;
}

ksys::act::Unk_71025ae620* MapConstActive::getDropData() {
    return _860;
}

void MapConstActive::m148() {
    x_2();
    if (_860)
        _860->sub_71006DA914(getDamageMgr(), false);
}

}  // namespace uking::act
