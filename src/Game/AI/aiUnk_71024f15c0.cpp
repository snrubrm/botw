#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapDebug.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"

Unk_71024f15c0::Unk_71024f15c0() = default;

const sead::Vector3f& Unk_71024f15c0::Data::sub_7100EEB370() const {
    return pos;
}

ksys::map::Rail* Unk_71024f15c0::Data::sub_7100EEB374() const {
    if (rail && rail->x_20())
        return rail;
    return nullptr;
}

// NON_MATCHING: integer bound checks and the shared zero-progress store are scheduled differently.
void Unk_71024f15c0::Data::sub_7100EEB6D0() {
    if (!rail)
        return;
    if (progress <= 0.0f) {
        progress = 0.0f;
        return;
    }
    const bool closed = rail->isClosed();
    const s32 num_points = rail->getNumPoints();
    if (closed) {
        if (num_points > 0) {
            if (!(progress >= f32(num_points)))
                return;
            do {
                progress -= f32(num_points);
            } while (progress >= f32(num_points));
        } else {
            if (!rail)
                return;
            progress = 0.0f;
        }
    } else {
        if (num_points > 0) {
            if (!(progress > f32(num_points - 1)))
                return;
            if (!rail)
                return;
            progress = f32(num_points - 1);
        } else {
            if (!rail)
                return;
            progress = 0.0f;
        }
    }
    if (rail) {
        sub_7100EEB6D0();
        rail->calcTranslateRotate(&pos, &rot, progress);
    }
}

void Unk_71024f15c0::sub_7100EEBAE0(ksys::map::Rail* rail, f32 progress) {
    _8.rail = rail;
    if (rail) {
        _8.progress = progress;
        _8.sub_7100EEB6D0();
        _8.rail->calcTranslateRotate(&_8.pos, &_8.rot, _8.progress);
    }
    _30.progress = _8.progress;
    _30.rail = _8.rail;
    _30.pos = _8.pos;
    _30.rot = _8.rot;
}

bool Unk_71024f15c0::m3() {
    if (_30.progress == 0)
        return true;
    return _30.progress == f32(_30.rail->getNumPoints() - 1);
}

bool Unk_71024f15c0::sub_7100EEBB74() const {
    return _30.rail != nullptr;
}

// NON_MATCHING: the original copies each Data's progress and rail before pos and rot
void Unk_71024f15c0::m2() {
    _8.progress = 0;
    _8.rail = nullptr;
    _8.pos = sead::Vector3f::zero;
    _8.rot = sead::Vector3f::zero;
    _30.progress = 0;
    _30.rail = nullptr;
    _30.pos = sead::Vector3f::zero;
    _30.rot = sead::Vector3f::zero;
    _58 = 1;
}

void Unk_71024f15c0::sub_7100EEBDB8(const Unk_71024f15c0* other) {
    _8 = other->_8;
    _30 = other->_30;
    _58 = other->_58;
}

bool Unk_71024f15c0::sub_7100EEBE88() const {
    return _8.rail->isClosed();
}

void Unk_71024f15c0::sub_7100EEBE9C(s32 direction) {
    if (direction != -1 && direction != 1)
        direction = 1;
    _58 = direction;
}

ksys::map::Rail* sub_7100EEF034(ksys::act::Actor* actor, s32 idx) {
    auto* object = actor->getMapObject();
    if (!object)
        return nullptr;
    if (!object->getRails_0())
        return nullptr;
    return static_cast<ksys::map::Rail**>(object->getRails_0())[idx];
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

ksys::map::Rail* sub_7100EEF2F0(ksys::act::Actor* actor, const sead::SafeString& name) {
    auto* rail = ksys::act::sub_7100EEF0FC(actor, name);
    if (!rail && actor->getMapObject())
        ksys::map::printDebugMsg(actor, "レールがリンクされていません", nullptr);
    return rail;
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

const char* sub_7100EEF3E4(const ksys::map::Rail* rail, s32 idx) {
    const char* value = &sead::SafeString::cNullChar;
    const auto* point = rail->getPoint(idx);
    if (!point)
        return value;
    if (!point->getIter().isValid())
        return &sead::SafeString::cNullChar;
    point->getIter().tryGetParamStringByKey(&value, "MoveASKeyName");
    return value;
}

const char* sub_7100EEF470(const ksys::map::Rail* rail, s32 idx) {
    const char* value = &sead::SafeString::cNullChar;
    const auto* point = rail->getPoint(idx);
    if (!point)
        return value;
    if (!point->getIter().isValid())
        return &sead::SafeString::cNullChar;
    point->getIter().tryGetParamStringByKey(&value, "OnFlagName");
    return value;
}

const char* sub_7100EEF4FC(const ksys::map::Rail* rail, s32 idx) {
    const char* value = &sead::SafeString::cNullChar;
    const auto* point = rail->getPoint(idx);
    if (!point)
        return value;
    if (!point->getIter().isValid())
        return &sead::SafeString::cNullChar;
    point->getIter().tryGetParamStringByKey(&value, "OffFlagName");
    return value;
}

bool sub_7100EEF588(const ksys::map::Rail* rail, s32 idx) {
    bool value = false;
    const auto* point = rail->getPoint(idx);
    if (point && point->getIter().isValid()) {
        point->getIter().tryGetParamBoolByKey(&value, "IsAdjustPosAndDirToPoint");
        return value;
    }
    return false;
}

f32 sub_7100EEF078(const ksys::map::Rail* rail, s32 idx) {
    f32 value = 0;
    const auto* point = rail->getPoint(idx);
    if (point && point->getIter().isValid())
        point->getIter().tryGetParamFloatByKey(&value, "WaitFrame");
    return value;
}

f32 sub_7100EEF60C(const ksys::map::Rail* rail, s32 idx) {
    f32 value = 0;
    const auto* point = rail->getPoint(idx);
    if (point && point->getIter().isValid())
        point->getIter().tryGetParamFloatByKey(&value, "MoveSpeed");
    return value;
}

f32 sub_7100EEBE90() {
    return 0.001f;
}

// NON_MATCHING: the three final negated-component stores are scheduled differently.
void Unk_71024f15c0::sub_7100EEBBD0(sead::Vector3f* out) const {
    *out = _8.rot;
    if (out->dot(_30.pos - _8.pos) < 0.0f)
        *out = -*out;
}

// NON_MATCHING: the three final negated-component stores are scheduled differently.
void Unk_71024f15c0::sub_7100EEBC44(sead::Vector3f* out) const {
    *out = _30.rot;
    if (out->dot(_30.pos - _8.pos) < 0.0f)
        *out = -*out;
}

s32 sub_7100EEB610(const ksys::map::RailConnectablePoint* point) {
    const auto* rail = point->getJunctionRail();
    const s32 num_points = rail->getNumPoints();
    for (s32 i = 0; i < num_points; ++i) {
        if (rail->getPoint(i) == point)
            return i;
    }
    return -1;
}
