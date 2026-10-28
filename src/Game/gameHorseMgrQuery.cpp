#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking {

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

// NON_MATCHING: horseStuff ignores `this`, so the original does not re-set x0 for the call (same-TU dead argument).
bool Unk_7100e8a080::sub_7100E8A100(HorseMgr* mgr, ksys::act::BaseProc* proc) {
    if (!_4c && !mQuery && !(_48 > 0.0f)) {
        if (!horseStuff(mgr))
            return false;
        _48 = 66.0f;
        _4c = false;
        _8.acquire(proc, false);
    }
    return true;
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
