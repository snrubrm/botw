#include "Game/Actor/aiUnk_71024f15f8.h"
#include <cfloat>
#include "KingSystem/Map/mapPlacement18.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapRail.h"

const char* Unk_71024f15f8::sub_7100EEBF24() const {
    auto* route = _8.rail && _8.rail->x_20() ? static_cast<ksys::map::RailRoute*>(_8.rail) : nullptr;
    return route ? route->getRouteId() : nullptr;
}

Unk_71024f15f8::Unk_71024f15f8() = default;

void Unk_71024f15f8::m2() {
    _8.progress = 0;
    _8.rail = nullptr;
    _8.pos = sead::Vector3f::zero;
    _8.rot = sead::Vector3f::zero;
    _30.progress = 0;
    _30.rail = nullptr;
    _30.pos = sead::Vector3f::zero;
    _30.rot = sead::Vector3f::zero;
    _58 = 1;
    _60 = sead::SafeString::cEmptyString;
}

bool Unk_71024f15f8::m8(const ksys::map::RailConnectablePoint* point,
                        const sead::Vector3f* direction) {
    if (point && _30.sub_7100EEB3B4(point)) {
        m4(-1.0f, direction, nullptr);
        return _30.rail != nullptr;
    }
    m2();
    return false;
}

bool Unk_71024f15f8::m5() {
    auto* mgr = ksys::map::PlacementMgr::instance();
    if (!mgr)
        return false;
    const auto* point = mgr->roadStuff(_60);
    if (point && _30.sub_7100EEB3B4(point)) {
        m4(0.1f, nullptr, nullptr);
        return _30.rail != nullptr;
    }
    m2();
    return false;
}

bool Unk_71024f15f8::m6(const sead::Vector3f* pos) {
    auto* mgr = ksys::map::PlacementMgr::instance();
    if (!mgr)
        return false;
    const auto* point = mgr->sub_71011EA45C(pos, _60);
    if (point && _30.sub_7100EEB3B4(point)) {
        m4(0.1f, nullptr, nullptr);
        return _30.rail != nullptr;
    }
    m2();
    return false;
}

bool Unk_71024f15f8::m7(const sead::Vector3f* pos, const sead::Vector3f* direction) {
    return m8(ksys::map::PlacementMgr::instance()->sub_71011EA45C(pos, _60), direction);
}

// NON_MATCHING: two moves in the prologue are swapped.
void Unk_71024f15f8::m4(f32 distance, const sead::Vector3f* direction, u32* flags) {
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
    _8.rail = _30.rail;
    _8.progress = _30.progress;
    _8.pos = _30.pos;
    _8.rot = _30.rot;
    if (distance < 0.0f) {
        _58 = sub_7100EEC2D0(&_30, _58, direction, flags);
        _30.sub_7100EEB868(FLT_MAX, _58, flags, false);
    } else {
        while (distance > 0.001f) {
            _58 = sub_7100EEC2D0(&_30, _58, direction, flags);
            distance = _30.sub_7100EEB868(distance, _58, flags, false);
        }
    }
}

bool Unk_71024f15f8::m9(const ksys::map::RailRoute* route) {
    return ksys::map::sub_7100D4953C(route, _60);
}

// NON_MATCHING: the original keeps the progress in a register across the end test.
bool Unk_71024f15f8::m3() {
    if (_30.progress != 0 && _30.progress != f32(_30.rail->getNumPoints() - 1))
        return false;
    const f32 progress = _30.progress;
    auto* rail = _30.rail && _30.rail->x_20() ? _30.rail : nullptr;
    if (!rail)
        return true;
    const auto* point = static_cast<const ksys::map::RailConnectablePoint*>(rail->getPoint(s32(progress)));
    if (point && point->getJunctionPoint())
        return false;
    return true;
}
