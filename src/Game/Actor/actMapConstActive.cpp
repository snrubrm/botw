#include "Game/Actor/actMapConst.h"
#include <basis/seadNew.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

// Source ownership is unknown; declaration only.
void sub_7100D2D424(uking::dmg::DamageManagerBase* manager);

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

void MapConstActive::preDelete2_(const PreDeleteArg& arg) {
    if (_850) {
        _850->free();
        delete _850;
        _850 = nullptr;
    }
    if (auto* manager = _858) {
        sub_7100D2D424(manager);
        manager->preDelete1();
        manager->preDelete2();
        delete _858;
        _858 = nullptr;
    }
    if (_860) {
        ksys::act::DropData::sub_71006DB89C(_860);
        _860 = nullptr;
    }
    MapConstActiveOrMergedDungeonParts::preDelete2_(arg);
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

void MapConstActive::initMaybe() {
    MapConstActiveOrMergedDungeonParts::initMaybe();
    if (ksys::act::hasTag(this, ksys::act::tags::XLinkEventOnAtInit))
        xlinkEventOn(this, 25, 1, false);
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
