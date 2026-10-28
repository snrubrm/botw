#include "Game/gameHorseMgr.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actRideable.h"
#include "Game/Scene/gameScene.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapRail.h"
#include <geom/seadSegment.h>
#include <geom/seadGeometry.h>
#include <math/seadMathCalcCommon.h>

namespace uking {

namespace act {
extern const f32 sUnk_7101DA238C;
extern const f32 sUnk_7101DA23D4;
}  // namespace act

// 0x7100e8a080 (TU of its own: its address block starts right after the HorseMgr functions, and HorseMgr's
// dtor and sub_7100E87760 call these out of line).

Unk_7100e8a080::Unk_7100e8a080() = default;

// 0x7100e8a0c4 (was sub_7100E8A0C4): ~HorseMgr calls it for HorseMgr::_270; the link reset is _8's destructor.
Unk_7100e8a080::~Unk_7100e8a080() {
    if (mQuery) {
        ksys::phys::HavokAI::instance()->destroyQuery(mQuery);
        mQuery = nullptr;
    }
}

bool Unk_7100e8a080::sub_7100E8A100(HorseMgr* mgr, ksys::act::BaseProc* proc) {
    if (!_4c && !mQuery && !(_48 > 0.0f)) {
        if (!horseStuff(mgr))
            return false;
        _48 = 66.0f;
        _4c = 0;
        _8.acquire(proc, false);
    }
    return true;
}

// NON_MATCHING: the same calls and constants; this build hoists the SafeString temporary's vtable address point
// into a callee-saved register and pairs its two stores, while the original recomputes and stores them per check.
// 0x7100e8a16c (CSV horseStuff; does not use `this`): the game data checks on the owned horse of `mgr` (no stolen
// horse, not in Hyrule Castle, none of the Demo141/Demo142/Demo146 flags and no NakedIsland amiibo prohibition).
bool Unk_7100e8a080::horseStuff(HorseMgr* mgr) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(&mgr->mOwnedHorse, &accessor))
        return false;
    if (!act::sub_7100E6F010(accessor))
        return false;

    bool value;
    if (ksys::gdt::Manager::instance()->getParam().get().getBuffer()->getBool(
        &value, "IsGet_PlayerStole2",
        ksys::gdt::Manager::instance()->getParam().shouldCheckPermissions(), true) && value != 1)
        return false;
    if (ksys::gdt::Manager::instance()->getParam().get().getBuffer()->getBool(
        &value, "IsInHyruleCastleArea",
        ksys::gdt::Manager::instance()->getParam().shouldCheckPermissions(), true) && value)
        return false;
    if (ksys::gdt::Manager::instance()->getParam().get().getBuffer()->getBool(
        &value, "IsPlayed_Demo146_0",
        ksys::gdt::Manager::instance()->getParam().shouldCheckPermissions(), true) && value)
        return false;
    if (ksys::gdt::Manager::instance()->getParam().get().getBuffer()->getBool(
        &value, "IsPlayed_Demo142_0",
        ksys::gdt::Manager::instance()->getParam().shouldCheckPermissions(), true) && value)
        return false;
    if (ksys::gdt::Manager::instance()->getParam().get().getBuffer()->getBool(
        &value, "IsPlayed_Demo141_0",
        ksys::gdt::Manager::instance()->getParam().shouldCheckPermissions(), true) && value)
        return false;
    if (ksys::gdt::Manager::instance()->getParam().get().getBuffer()->getBool(
        &value, "IsPlayed_Demo141_1",
        ksys::gdt::Manager::instance()->getParam().shouldCheckPermissions(), true) && value)
        return false;
    if (ksys::gdt::Manager::instance()->getParam().get().getBuffer()->getBool(
        &value, "IsPlayed_Demo141_2",
        ksys::gdt::Manager::instance()->getParam().shouldCheckPermissions(), true) && value)
        return false;
    if (ksys::gdt::Manager::instance()->getParam().get().getBuffer()->getBool(
        &value, "IsPlayed_Demo141_3",
        ksys::gdt::Manager::instance()->getParam().shouldCheckPermissions(), true) && value)
        return false;
    if (!ksys::gdt::Manager::instance()->getParam().get().getBuffer()->getBool(
            &value, "NakedIsland_ProhibitAmiibo",
            ksys::gdt::Manager::instance()->getParam().shouldCheckPermissions(), true) ||
        !value)
        return true;
    return false;
}

// 0x7100e8a404 (placeholder name): the owned-horse link's per-frame state machine. While the link waits for its
// setup (_4c 1) or a processed query (_4c 2) it runs the query step; a processed query is torn down after its
// actor is checked, and the query timer starts the owned-horse call request.
void Unk_7100e8a080::sub_7100E8A404(HorseMgr* mgr) {
    if (_4c) {
        if (sub_7100E8A5D4(mgr)) {
            _4c = 0;
            _8.reset();
        }
        return;
    }

    if (mQuery && mQuery->_8 == 2) {
        if (sub_7100E8A7A8(mgr)) {
            if (sub_7100E8A5D4(mgr))
                _8.reset();
        } else {
            _8.reset();
            ksys::act::ActorLinkConstDataAccess accessor;
            if (ksys::act::acquireActor(&mgr->mOwnedHorse, &accessor)) {
                auto* rideable = accessor.getHorseOptions();
                if (!rideable || (rideable->Unk_7100e8b2b8::_8 & 0xff) != 1)
                    ksys::gdt::Manager::instance()->setS32(2, "Horse_UnreachableCause");
            }
        }
        ksys::phys::HavokAI::instance()->destroyQuery(mQuery);
        mQuery = nullptr;
        return;
    }

    if (_48 > 0.0f) {
        if (getSceneStatus() == 0) {
            ksys::Timer::update(&_48, -1.0f);
            if (_48 <= 0.0f) {
                if (!horseStuff(mgr) || !sub_7100E8AA6C(mgr)) {
                    _8.reset();
                    if (mgr->mOwnedHorse.hasProc())
                        ksys::gdt::Manager::instance()->setS32(2, "Horse_UnreachableCause");
                }
            }
        }
    }
}

// 0x7100e8a5d4 (placeholder name): the query state step. True when the linked actor is accepted, the owned horse
// is not in the calc state, or it stands more than 0.1 below the linked actor; otherwise the call request is sent
// with the query's matrix and the state moves to 1 (2 during an event).
// NON_MATCHING: the same instructions and calls; the original shares one return-true and one return-false block
// between the acquire failure, the AS request and the ground hit, while this build materialises the true / false
// return value in each predecessor.
bool Unk_7100e8a080::sub_7100E8A5D4(HorseMgr* mgr) {
    ksys::act::BaseProc* proc = _8.getProc(nullptr);
    if (!sead::IsDerivedFrom<ksys::act::Actor>(proc))
        return true;
    auto* actor = static_cast<ksys::act::Actor*>(proc);

    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(&mgr->mOwnedHorse, &accessor))
        return true;

    if (ksys::evt::Manager::instance()->hasActiveEvent()) {
        _4c = 2;
        return false;
    }
    if (accessor.isStateCalc()) {
        actor->sendMessage(*accessor.getMessageTransceiverId(),
                           ksys::MessageType(_4c == 1 ? 0x380001e : 0x380001d), &_18, false);
        return true;
    }
    if (_4c) {
        sead::Vector3f pos = _18.getTranslation();
        const f32 y = _18.m[1][3];
        if (sub_7100E8AEEC(&pos, 3.0f, 0.0f) && !(y - pos.y > -0.1f))
            return true;
    }
    auto* horse = mgr->getOwnedHorseBase();
    if (horse)
        horse->_b74.set(0x2008);
    accessor.setProperties(_18, nullptr, nullptr, nullptr, false, 0, -1);
    _4c = 1;
    return false;
}

// 0x7100e8afe8 (placeholder name): the squared distance from `pos` to the rail route `name` at the connectable
// point nearest to `pos`; false when the point, its junction rail or the route id is missing. Used by the climate
// check of sub_7100E8AA6C.
bool sub_7100E8AFE8(f32* out, const sead::Vector3f& pos, const sead::SafeString& name) {
    auto* point = ksys::map::PlacementMgr::instance()->sub_71011EA45C(&pos, name);
    if (!point)
        return false;
    const auto* rail = point->getJunctionRail();
    if (!rail)
        return false;
    const char* route_id = static_cast<const ksys::map::RailRoute*>(rail)->getRouteId();
    if (!route_id || name != route_id)
        return false;

    const s32 num_points = rail->getNumPoints();
    const s32 last = num_points - 1;
    for (s32 index = 0; index <= last; ++index) {
        if (rail->getPoint(index) != point)
            continue;

        const sead::Vector3f& translate = point->getTranslate();
        *out = INFINITY;
        f32 dist;
        if (index != 0) {
            const sead::Segment3f segment(translate, rail->getPoint(index - 1)->getTranslate());
            dist = sead::Geometry::calcSquaredDistancePointToSegment(pos, segment, nullptr);
            *out = dist;
        } else {
            dist = act::sUnk_7101DA23D4;
        }
        if (index != last) {
            const sead::Segment3f segment(translate, rail->getPoint(index + 1)->getTranslate());
            dist = sead::Mathf::min(
                sead::Geometry::calcSquaredDistancePointToSegment(pos, segment, nullptr), *out);
            *out = dist;
        }
        if (sead::Mathf::abs(dist) > act::sUnk_7101DA238C)
            *out = (translate - pos).squaredLength();
        return true;
    }
    return false;
}

// 0x7100e8aeec (placeholder name): casts a ray through `pos` from y + `up` down to y - `down` on the ground
// layers (ground object, ground, smooth ground, object) and writes the hit position back into `pos`.
bool Unk_7100e8a080::sub_7100E8AEEC(sead::Vector3f* pos, f32 up, f32 down) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);

    query.setStart(sead::Vector3f(pos->x, pos->y + up, pos->z));
    query.setEnd(sead::Vector3f(pos->x, pos->y - down, pos->z));

    bool hit = false;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(pos);
        hit = true;
    }
    return hit;
}

// 0x7100e8ae80 (placeholder name): the ground query above with a 3 unit upward / 0 unit downward sweep; false
// only when a ground was found at most 0.1 above the matrix's translation.
bool Unk_7100e8a080::sub_7100E8AE80(const sead::Matrix34f& mtx) {
    sead::Vector3f pos = mtx.getTranslation();
    const f32 y = mtx.m[1][3];
    if (!sub_7100E8AEEC(&pos, 3.0f, 0.0f))
        return true;
    return y - pos.y > -0.1f;
}

}  // namespace uking

namespace uking::act {
// 0x7101da238c (FLT_MAX) and 0x7101da23d4 (infinity): the range / initial distance of the rail query above.
extern const f32 sUnk_7101DA238C;
const f32 sUnk_7101DA238C = 3.402823466e+38f;
extern const f32 sUnk_7101DA23D4;
const f32 sUnk_7101DA23D4 = __builtin_inff();
}  // namespace uking::act
