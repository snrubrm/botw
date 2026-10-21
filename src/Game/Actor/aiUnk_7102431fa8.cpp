#include "Game/Actor/aiUnk_7102431fa8.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWizzrobe.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_7100742478.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <limits>

// NON_MATCHING: cancellation and animation-state stores are scheduled differently.
void Unk_7102431fa8::sub_7100741C24() {
    if (_10) {
        const auto* life = _d0->getLife();
        if ((life && *life < 1) || !sub_71005D8F28(_d0) ||
            !uking::act::DamageInfoMgr::instance()->get790().sub_71006726DC(_14[0]) ||
            !uking::act::DamageInfoMgr::instance()->get790().sub_7100672B00(_d0))
            sub_7100741E14();
    }
    if (_8 == 2)
        _8 = 0;
    if (_c == 0)
        return;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(_d0)) {
        if (enemy->m151(3))
            return;
    }
    auto* as_list = _d0->getASList();
    if (!as_list)
        return;
    if (_c == 1) {
        switch (_8) {
        case 0:
            _8 = 1;
            _c = 0;
            as_list->startAnimationMaybe(-1.0f, -1.0f, _20, _14[1], 0, true);
            break;
        case 1:
            _c = 0;
            break;
        }
    }
    if (_c == 2) {
        switch (_8) {
        case 0:
        case 2:
            _c = 0;
            break;
        case 1:
            _8 = 2;
            _c = 0;
            as_list->startAnimationMaybe(-1.0f, -1.0f, _78, _14[1], 0, true);
            break;
        }
    }
}

void Unk_7102431fa8::sub_7100741E14() {
    uking::act::DamageInfoMgr::instance()->get790().sub_7100672888(_d0);
    _c = 2;
    _10 = false;
}

void Unk_7102431fa8::sub_7100741E54(s32 weather_type) {
    auto& unk790 = uking::act::DamageInfoMgr::instance()->get790();
    uking::act::DamageInfoMgr::Unk790Params params;
    if (const auto* wizzrobe = _d0->getParam()->getRes().mGParamList->getWizzrobe()) {
        params.mActorName = wizzrobe->mMagicFallActorName.ref();
        params.mCenterOffsetXZ = wizzrobe->mMagicFallCenterOffsetXZ.ref();
        params.mOffsetY = wizzrobe->mMagicFallOffsetY.ref();
        params.mIgniteRotSpd = sead::Mathf::deg2rad(wizzrobe->mMagicFallIgniteRotSpd.ref()) / 30.0f;
        params.mRandRadius = wizzrobe->mMagicFallRandRadius.ref();
        params.mIntervalMax = wizzrobe->mMagicFallIntervalMax.ref();
        params.mIntervalMin = wizzrobe->mMagicFallIntervalMin.ref();
    }
    if (!unk790.sub_710067298C(_d0, params))
        return;
    xlinkSearchAndEmit(_d0, "WeatherFlash", 2, nullptr);
    _14[0] = weather_type;
    _10 = true;
}

void Unk_7102431fa8::sub_71007420B8(const sead::SafeString& start_as_name,
                                   const sead::SafeString& stop_as_name, s32 target_idx) {
    _20.copy(start_as_name);
    _78.copy(stop_as_name);
    _14[1] = target_idx;
    _8 = 0;
    _c = 0;
}

namespace {
constexpr f32 cNaN = std::numeric_limits<f32>::quiet_NaN();
}

// 0x7100742278: the HavokAI closest-point query for `out`, then the character's material filter.
bool sub_7100742278(f32 radius, void* a2, ksys::phys::NavMeshCharacter* nav,
                    const sead::Vector3f* pos) {
    const auto query = ksys::phys::HavokAI::instance()->sub_7100F87ED0(
        static_cast<sead::Vector3f*>(a2), *pos, radius);
    if (!query.sub_7100F7EB40())
        return false;
    return nav->isMaterialUsableMaybe(query.sub_7100F7EEE4());
}

// 0x7100742588: a navmesh point query around `pos` with `radius`; writes the hit to `out`.
// NON_MATCHING: scheduling only; the original saves `out` and the result pointer later and orders a few
// constant stores differently.
bool sub_7100742588(sead::Vector3f* out, ksys::phys::NavMeshCharacter* nav,
                    const sead::Vector3f* pos, f32 radius) {
    ksys::phys::HavokAI::Unk1 result;
    ksys::phys::HavokAI::Unk2 query;
    query.from = sead::Vector3f(cNaN, cNaN, cNaN);
    query.dir = sead::Vector3f::ex;
    query.distance = -4.0f;
    query._30 = 0xff;
    query._10 = *pos;
    query.radius = radius;
    query.tolerance = 0.1f;

    ksys::phys::HavokAI* havok = nav->_18 ? nav->_18 : ksys::phys::HavokAI::instance();
    const bool hit = havok->sub_7100F86324(nav, query, &result);
    if (out)
        out->set(result._18);
    return hit;
}

// 0x7100742664: a line-of-sight probe of `length` from `position` along the character's direction;
// `tolerance` becomes the query radius.
// NON_MATCHING: scheduling only, like sub_7100742588.
bool sub_7100742664(sead::Vector3f* hit, ksys::phys::NavMeshCharacter* nav,
                    const sead::Vector3f* position, f32 length, f32 tolerance) {
    ksys::phys::HavokAI::Unk1 result;
    ksys::phys::HavokAI::Unk2 query;
    query.from = sead::Vector3f(cNaN, cNaN, cNaN);
    query.tolerance = 0.1f;
    query._10 = sead::Vector3f::zero;
    query.dir = *position;
    query.distance = length;
    query.radius = tolerance;
    query._30 = 0xff;

    ksys::phys::HavokAI* havok = nav->_18 ? nav->_18 : ksys::phys::HavokAI::instance();
    const bool found = havok->sub_7100F86324(nav, query, &result);
    if (hit)
        hit->set(result._18);
    return found;
}

// 0x7100742478: navmesh query from `pos` down by `height` along Vector3f::ey; true when the hit material
// cost is finite. Writes Vector3f::zero to `out` without a HavokAI.
// NON_MATCHING: the type argument is narrowed to 32 bits earlier than in the original and the vector
// subtraction is scheduled as a pair load.
bool sub_7100742478(sead::Vector3f* out, const sead::Vector3f& pos, f32 height, s32 a3) {
    sead::Vector3f from = sead::Vector3f::ey;
    from *= height;
    from.x = pos.x - from.x;
    from.y = pos.y - from.y;
    from.z = pos.z - from.z;
    ksys::phys::HavokAI* havok = ksys::phys::HavokAI::instance();
    if (!havok) {
        out->set(sead::Vector3f::zero);
        return false;
    }

    const ksys::phys::Unk_7100f7e9f0 query = havok->sub_7100F87A80(out, pos, from);
    if (!query.sub_7100F7EB40())
        return false;
    const f32 cost = ksys::phys::NavMeshCharacter::sub_7100F74FD8(
        ksys::phys::NavMeshCharacterType(a3), query.sub_7100F7EEE4());
    return !(sead::Mathf::abs(cost) > std::numeric_limits<f32>::max());
}

// 0x7100742334: whether the position is at most `height` above the navmesh two metres below it.
// NON_MATCHING: the two vector additions / subtractions are scheduled differently.
bool sub_7100742334(const sead::Vector3f* position, f32 height) {
    sead::Vector3f from = *position;
    from.y += 2.0f;
    const sead::Vector3f to = from - sead::Vector3f::ey * (height + 2.0f);

    ksys::phys::HavokAI* havok = ksys::phys::HavokAI::instance();
    if (!havok)
        return false;

    sead::Vector3f hit;
    const ksys::phys::Unk_7100f7e9f0 query = havok->sub_7100F87A80(&hit, from, to);
    if (!query.sub_7100F7EB40())
        return false;
    const f32 cost = ksys::phys::NavMeshCharacter::sub_7100F74FD8(
        ksys::phys::NavMeshCharacterType::WolfLink, query.sub_7100F7EEE4());
    if (sead::Mathf::abs(cost) > std::numeric_limits<f32>::max())
        return false;
    if (position->y <= hit.y)
        return true;
    return position->y - hit.y <= height;
}
