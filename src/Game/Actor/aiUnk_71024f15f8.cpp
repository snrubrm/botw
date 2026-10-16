#include "Game/Actor/aiUnk_71024f15f8.h"
#include "KingSystem/Map/mapRail.h"

const char* Unk_71024f15f8::sub_7100EEBF24() const {
    auto* route = _28 && _28->x_20() ? static_cast<ksys::map::RailRoute*>(_28) : nullptr;
    return route ? route->getRouteId() : nullptr;
}

// NON_MATCHING: store order only (member types are placeholders)
Unk_71024f15f8::Unk_71024f15f8() = default;

// NON_MATCHING: store scheduling of the three zero vectors.
void Unk_71024f15f8::sub_7100EEBFBC() {
    _20 = 0;
    _28 = nullptr;
    _8 = sead::Vector3f::zero;
    _58 = true;
    _48 = 0;
    _50 = nullptr;
    _14 = sead::Vector3f::zero;
    _30 = sead::Vector3f::zero;
    _3c = sead::Vector3f::zero;
    _60 = sead::SafeString::cEmptyString;
}
