#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapDebug.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"
#include <math/seadMathCalcCommon.h>
#include <cfloat>

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

// NON_MATCHING: the closed-rail previous-point branch duplicates the index subtraction.
void Unk_71024f15c0::Data::sub_7100EEB7A4(const ksys::map::RailPoint** previous,
                                        const ksys::map::RailPoint** next) const {
    *next = nullptr;
    const auto* previous_rail = rail;
    s32 index = s32(progress);
    if (index < 0) {
        *previous = nullptr;
    } else if (index != 0) {
        *previous = previous_rail->getPoint(index - 1);
    } else if (previous_rail->isClosed() && (index = previous_rail->getNumPoints()) != 0) {
        *previous = previous_rail->getPoint(index - 1);
    } else {
        *previous = nullptr;
    }
    index = s32(progress);
    if (index < 0) {
        *next = nullptr;
        return;
    }
    const auto* current_rail = rail;
    if (index < current_rail->getNumPoints() - 1) {
        *next = previous_rail->getPoint(index + 1);
    } else if (current_rail->isClosed()) {
        *next = previous_rail->getPoint(0);
    } else {
        *next = nullptr;
    }
}

// NON_MATCHING: backward integer-index adjustment is scheduled across the point-count calls.
f32 Unk_71024f15c0::Data::sub_7100EEB868(f32 distance, s32 direction, u32* flags,
                                        bool check_end) {
    u32 local_flags = 0;
    if (!flags)
        flags = &local_flags;
    f32 old_progress = progress;
    s32 index = s32(old_progress);
    const auto* old_rail = rail;
    if (direction < 0 && old_progress == f32(index)) {
        --index;
        if (index < 0) {
            if (!old_rail->isClosed())
                return 0.0f;
            index = old_rail->getNumPoints() - 1;
            old_progress = f32(old_rail->getNumPoints());
        }
    }
    if (!rail)
        return 0.0f;
    const auto* current_rail = rail;
    const auto* point = current_rail->getPoint(index);
    if (!point)
        return 0.0f;
    const f32 length = point->getNextDistance();
    if (length <= 0.0f)
        return 0.0f;
    const f32 fraction = distance / length;
    const f32 new_progress = old_progress + f32(direction) * sead::Mathf::clampMax(fraction, 1.0f);
    const s32 new_index = new_progress < 0.0f ? -1 : s32(new_progress);
    if (!(fraction >= 1.0f) && new_index == index) {
        if (rail) {
            progress = new_progress;
            sub_7100EEB6D0();
            rail->calcTranslateRotate(&pos, &rot, progress);
        }
        return 0.0f;
    }
    *flags |= 1;
    index = sead::Mathi::max(index, new_index);
    if (index < old_rail->getNumPoints()) {
        if (rail) {
            progress = f32(index);
            sub_7100EEB6D0();
            rail->calcTranslateRotate(&pos, &rot, progress);
        }
        if (index == 0 && check_end)
            *flags |= 2;
    } else if (old_rail->isClosed()) {
        if (rail) {
            progress = 0.0f;
            sub_7100EEB6D0();
            rail->calcTranslateRotate(&pos, &rot, progress);
        }
    } else {
        --index;
        if (rail) {
            progress = f32(index);
            sub_7100EEB6D0();
            rail->calcTranslateRotate(&pos, &rot, progress);
        }
        if (check_end)
            *flags |= 2;
    }
    return sead::Mathf::clampMin(distance - length * (f32(direction) * (f32(index) - old_progress)), 0.0f);
}

// NON_MATCHING: local flags stack placement and the Data copy load/store grouping differ.
void Unk_71024f15c0::m4(f32 distance, void*, u32* flags) {
    _8.sub_7100EEB6D0();
    _30.sub_7100EEB6D0();
    u32 local_flags = 0;
    if (!flags)
        flags = &local_flags;
    *flags = 0;
    if (!_30.rail) {
        m2();
        return;
    }
    if (distance == 0.0f)
        return;
    _8 = _30;
    if (distance < 0.0f) {
        _30.sub_7100EEB868(FLT_MAX, _58, flags, true);
    } else {
        while (distance > 0.001f)
            distance = _30.sub_7100EEB868(distance, _58, flags, true);
    }
}

bool Unk_71024f15c0::Data::sub_7100EEB3B4(const ksys::map::RailConnectablePoint* point) {
    if (point->getJunctionPoint())
        return sub_7100EEB514(point);
    rail = point->getJunctionRail();
    const s32 point_index = sub_7100EEB610(point);
    if (rail) {
        progress = f32(point_index);
        sub_7100EEB6D0();
        rail->calcTranslateRotate(&pos, &rot, progress);
    }
    if (rail->getNumPoints() != 1 || point->getJunctionPoint())
        return true;
    // The native body calls this even though the following reset clears the position.
    point->getTranslate();
    progress = 0.0f;
    rail = nullptr;
    pos = sead::Vector3f::zero;
    rot = sead::Vector3f::zero;
    return false;
}

// NON_MATCHING: the cached const Rail view changes load scheduling and register allocation.
bool Unk_71024f15c0::Data::sub_7100EEB514(const ksys::map::RailConnectablePoint* point) {
    rail = point->getJunctionRail();
    const ksys::map::Rail* current_rail = rail;
    const f32 endpoint = current_rail->getPoint(0) == point ? 0.0f : f32(current_rail->getNumPoints() - 1);
    if (rail) {
        progress = endpoint;
        sub_7100EEB6D0();
        rail->calcTranslateRotate(&pos, &rot, progress);
    }
    if (rail->getNumPoints() != 1 || point->getJunctionPoint())
        return true;
    // The native body calls this even though the following reset clears the position.
    point->getTranslate();
    progress = 0.0f;
    rail = nullptr;
    pos = sead::Vector3f::zero;
    rot = sead::Vector3f::zero;
    return false;
}
