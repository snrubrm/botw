#include "Game/AI/Action/actionForkGanonBeastHeadBarrier.h"
#include <geom/seadGeometry.h>
#include <geom/seadSegment.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

ForkGanonBeastHeadBarrier::ForkGanonBeastHeadBarrier(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkGanonBeastHeadBarrier::~ForkGanonBeastHeadBarrier() = default;

bool ForkGanonBeastHeadBarrier::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGanonBeastHeadBarrier::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkGanonBeastHeadBarrier::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGanonBeastHeadBarrier::loadParams_() {
    getStaticParam(&mBarrierRad_s, "BarrierRad");
    getStaticParam(&mBarrierFront_s, "BarrierFront");
    getStaticParam(&mBarrierBack_s, "BarrierBack");
    getStaticParam(&mBarrierHeight_s, "BarrierHeight");
    getStaticParam(&mBarrierHeightMax_s, "BarrierHeightMax");
}

// NON_MATCHING: register allocation only — the original parks the direction components in
// integer regs (w22/w20 with fmov both ways) and keeps actor x/z in s9/s8 from the start;
// ours keeps the direction in s-regs and loads actor x/z late, cascading into different
// spill slots and segment-store order. All calls, branches, constants and the segment/point
// structure match.
bool ForkGanonBeastHeadBarrier::sub_7100154628() {
    auto* actor = mActor;
    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
    bool result = false;
    if (!accessor.isGroundForEvent()) {
        const auto& player_mtx = accessor.getActorMtx();
        sead::Vector3f point(player_mtx(0, 3), player_mtx(1, 3), player_mtx(2, 3));
        const f32 diff = player_mtx(1, 3) - actor->getMtx()(1, 3);
        if (diff < *mBarrierHeight_s) {
            result = false;
        } else if (*mBarrierHeightMax_s < diff) {
            result = false;
        } else {
            point.y = 0.0f;
            const auto& mtx = actor->getMtx();
            const f32 actor_x = mtx(0, 3);
            const f32 actor_z = mtx(2, 3);
            f32 dx = mtx(0, 2);
            f32 dz = mtx(2, 2);
            const f32 len = sead::Vector3f(dx, 0.0f, dz).length();
            if (len > 0.0f) {
                const f32 inv = 1.0f / len;
                dx *= inv;
                dz *= inv;
            }
            const sead::Vector3f start(actor_x + dx * *mBarrierBack_s, 0.0f,
                                       actor_z + dz * *mBarrierBack_s);
            const sead::Vector3f end(actor_x + dx * *mBarrierFront_s, 0.0f,
                                      actor_z + dz * *mBarrierFront_s);
            const sead::Segment3f segment(start, end);
            const f32 dist_sq =
                sead::Geometry::calcSquaredDistancePointToSegment(point, segment, nullptr);
            result = dist_sq <= *mBarrierRad_s * *mBarrierRad_s;
        }
    }
    return result;
}

// NON_MATCHING: identical instructions; the original computes `this + 0x48` (the sender) after the lock address and spin
// load, we compute it before.
void ForkGanonBeastHeadBarrier::calc_() {
    if (!sub_7100154628())
        return;

    auto* actor = mActor;
    _48.x(actor, actor->getMtx().getTranslation());
    _48.sub_710070DCC0(&ksys::act::PlayerInfo::getSomeProcLink(), false);

    Unk_71012419b4 handle;
    xlinkSearchAndEmit(mActor, "Shockwave", 2, &handle);
    handle.sub_71012419B4(getPlayerPosition());
}

}  // namespace uking::action
