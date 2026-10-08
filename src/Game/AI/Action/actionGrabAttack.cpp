#include "Game/AI/Action/actionGrabAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"

namespace uking::action {

GrabAttack::GrabAttack(const InitArg& arg) : Grab(arg) {}

GrabAttack::~GrabAttack() = default;

void GrabAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtRigidBodyName_s.cstr())) {
        sub_71007A2B64(body, nullptr);
        sub_71007A3258(body, nullptr);
    }
    _70 = false;
    Grab::enter_(params);
}

void GrabAttack::leave_() {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtRigidBodyName_s.cstr()))
        sub_71007A2D34(body);
    if (sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
        mActor->resetConnectedCalcChild(false);
    Grab::leave_();
}

void GrabAttack::loadParams_() {
    Grab::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAtRigidBodyName_s, "AtRigidBodyName");
}

// NON_MATCHING: scheduling only — the original loads the Atk string top into x21 before
// the member vtable (pre-indexed) load; ours loads the member vtable first and the Atk top
// straight into x1. Forcing the order needs a single-use local for the Atk top (borderline,
// not applied). All calls, branches and constants match.
void GrabAttack::calc_() {
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0)) {
        sub_7100190184(&query);
    } else if (sub_71005DD74C(mActor, nullptr, 0, 0)) {
        auto* actor = mActor;
        auto* atk = sub_71007A24BC();
        atk->cstr();
        mAtRigidBodyName_s.cstr();
        if (auto* body = actor->findPhysicsBodyByName(atk->getStringTop(),
                                                      mAtRigidBodyName_s.getStringTop())) {
            sub_71007A3258(body, nullptr);
        }
    }
    Grab::calc_();
    if (m33() && m34()) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild())) {
            sub_71005DC41C(actor);
            _70 = true;
        }
    }
    if (isFinishedAS(0, 0) && _70) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild())) {
            actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            mActor->resetConnectedCalcChild(false);
        }
    }
}

void GrabAttack::m32() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

// Whether the grabbed actor (the connected calc child) hit this one.
bool GrabAttack::m33() {
    if (auto* actor = mActor) {
        auto* child = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcChild());
        if (child && hasAttackInfo(actor)) {
            const s32 count = getNumAttackInfoMaybe(actor);
            for (s32 i = 0; i < count; ++i) {
                auto* info = getAttackInfo(actor, i);
                if (info && info->_50.hasProcById(child))
                    return true;
            }
        }
    }
    return false;
}

}  // namespace uking::action
