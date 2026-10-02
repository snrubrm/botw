#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapDebug.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"

Unk_71024f15c0::Unk_71024f15c0() = default;

const sead::Vector3f& Unk_71024f15c0::Data::sub_7100EEB370() const {
    return pos;
}

bool Unk_71024f15c0::m3() {
    if (_30.progress == 0)
        return true;
    return _30.progress == f32(_30.rail->getNumPoints() - 1);
}

bool Unk_71024f15c0::sub_7100EEBB74() const {
    return _30.rail != nullptr;
}

bool Unk_71024f15c0::sub_7100EEBE88() const {
    return _8.rail->isClosed();
}

void Unk_71024f15c0::sub_7100EEBE9C(s32 direction) {
    if (direction != -1 && direction != 1)
        direction = 1;
    _58 = direction;
}

ksys::map::Rail* sub_7100EEF264(ksys::act::Actor* actor, s32 idx) {
    auto* object = actor->getMapObject();
    if (!object)
        return nullptr;

    if (object->getRails_0()) {
        if (auto* rail = static_cast<ksys::map::Rail**>(object->getRails_0())[idx])
            return rail;
    }

    if (actor->getMapObject())
        ksys::map::printDebugMsg(actor, "レールがリンクされていません", nullptr);
    return nullptr;
}

const char* sub_7100EEF358(const ksys::map::Rail* rail, s32 idx) {
    const char* value = &sead::SafeString::cNullChar;
    const auto* point = rail->getPoint(idx);
    if (!point)
        return value;
    if (!point->getIter().isValid())
        return &sead::SafeString::cNullChar;
    point->getIter().tryGetParamStringByKey(&value, "WaitASKeyName");
    return value;
}

f32 sub_7100EEF078(const ksys::map::Rail* rail, s32 idx) {
    f32 value = 0;
    const auto* point = rail->getPoint(idx);
    if (point && point->getIter().isValid())
        point->getIter().tryGetParamFloatByKey(&value, "WaitFrame");
    return value;
}
