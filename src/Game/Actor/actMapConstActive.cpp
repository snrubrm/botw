#include "Game/Actor/actMapConst.h"
#include <basis/seadNew.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actDropData.h"

namespace uking::act {

MapConstActive::MapConstActive(const CreateArg& arg) : MapConstActiveOrMergedDungeonParts(arg) {
    _1c0 = 3;
}

MapConstActive::~MapConstActive() = default;

ksys::act::BaseProc* MapConstActive::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) MapConstActive(arg);
}

bool MapConstActive::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    if (!MapConstActiveOrMergedDungeonParts::prepareInit_(heap, arg))
        return false;
    if (actorHasTgtBody(this)) {
        _850 = ksys::act::ActorAtk::makeForActor(this, heap);
        if (!_850)
            return false;
    }
    if (sub_71006D28AC(this)) {
        _858 = gameObjectInitField(this, heap);
        if (!_858)
            return false;
    }
    _860 = makeDropData(heap);
    return true;
}

ksys::act::Unk_71025ae640* MapConstActive::getAtk() {
    return _850;
}

void MapConstActive::m63() {
    MapConstActiveOrMergedDungeonParts::m63();
    sub_71007394E8(this);
    sub_7100739108(getActorAttackSensor(this));
    sub_7100739168(sub_71007A2844(this));
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
