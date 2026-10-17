#include "Game/Actor/aiUnk_71024f15f8.h"
#include <cfloat>
#include "KingSystem/Map/mapPlacement18.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapRail.h"
#include <random/seadGlobalRandom.h>

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

// NON_MATCHING: the candidate loop and the end check schedule the junction walk differently.
s8 Unk_71024f15f8::sub_7100EEC2D0(Unk_71024f15c0::Data* data, s32 direction,
                                  const sead::Vector3f* dir, u32* flags) {
    const s32 index = s32(data->progress);
    if (data->progress != f32(index))
        return direction;
    if (!data->rail || !data->rail->x_20())
        return direction;
    if (!data->rail)
        return direction;

    auto* point = static_cast<ksys::map::RailConnectablePoint*>(data->rail->getPoint(index));
    if (!point)
        return direction;

    const ksys::map::RailPoint* prev;
    const ksys::map::RailPoint* next;
    data->sub_7100EEB7A4(&prev, &next);

    const ksys::map::RailPoint* neighbours[16];
    ksys::map::RailConnectablePoint* candidates[16];
    f32 distances[16];
    s32 count = 0;

    if (prev && _58 < 0) {
        distances[0] = -1.0f;
        candidates[0] = point;
        count = 1;
    }
    if (next && _58 >= 0) {
        candidates[count] = point;
        neighbours[count] = next;
        distances[count] = 1.0f;
        ++count;
    }

    if (auto* junction = point->getJunctionPoint()) {
        for (auto** iter = junction; *iter; ++iter) {
            auto* junction_point = *iter;
            if (!m9(static_cast<const ksys::map::RailRoute*>(junction_point->getJunctionRail())))
                continue;

            Unk_71024f15c0::Data junction_data{};
            junction_data.sub_7100EEB514(junction_point);
            const ksys::map::RailPoint* junction_prev;
            const ksys::map::RailPoint* junction_next;
            junction_data.sub_7100EEB7A4(&junction_prev, &junction_next);
            if (junction_prev) {
                if (count > 15)
                    break;
                neighbours[count] = junction_prev;
                candidates[count] = junction_point;
                distances[count] = -1.0f;
                ++count;
            }
            if (junction_next) {
                if (count > 15)
                    break;
                candidates[count] = junction_point;
                neighbours[count] = junction_next;
                distances[count] = 1.0f;
                ++count;
            }
        }
    }

    s8 result;
    if (count == 0) {
        *flags |= 4;
        result = s32(data->progress) == 0 ? 1 : -1;
    } else {
        s32 chosen;
        if (dir && count >= 1) {
            f32 best = -FLT_MAX;
            chosen = -1;
            for (s32 i = 0; i < count; ++i) {
                const s32 idx = i > 15 ? 0 : i;
                const sead::Vector3f& from = candidates[idx]->getTranslate();
                const sead::Vector3f& to = neighbours[idx]->getTranslate();
                sead::Vector3f delta(to.x - from.x, 0.0f, to.z - from.z);
                delta.normalize();
                const f32 dot = delta.dot(*dir);
                if (dot > best) {
                    best = dot;
                    chosen = i;
                }
            }
        } else {
            chosen = s32(sead::GlobalRandom::instance()->getU32(u32(count)));
        }
        if (chosen < 0)
            chosen = s32(sead::GlobalRandom::instance()->getU32(u32(count)));

        const s32 idx = chosen > 15 ? 0 : chosen;
        result = s8(distances[idx]);
        data->sub_7100EEB3B4(candidates[idx]);
    }

    if (data->rail && data->rail->x_20()) {
        auto* current =
            static_cast<ksys::map::RailConnectablePoint*>(data->rail->getPoint(s32(data->progress)));
        if (current && current->getJunctionRail() != point->getJunctionRail())
            *flags |= 8;
    }
    return result;
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
