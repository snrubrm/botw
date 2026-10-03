#include "Game/AI/AI/aiGolemWeakPointRoot.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

GolemWeakPointRoot::GolemWeakPointRoot(const InitArg& arg) : WeakPointRoot(arg) {}

GolemWeakPointRoot::~GolemWeakPointRoot() {
    GolemWeakPointRoot::m37();
}

bool GolemWeakPointRoot::init_(sead::Heap* heap) {
    if (!WeakPointRoot::init_(heap))
        return false;
    m36();
    _1f4 = 0;
    return true;
}

void GolemWeakPointRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeakPointRoot::enter_(params);
    auto* actor = mActor;
    _1e8 = actor->getMtx().m[0][3];
    _1ec = actor->getMtx().m[1][3];
    _1f0 = actor->getMtx().m[2][3];
    sub_71007A439C(actor, &_1f8);
    if (auto* proc = sead::DynamicCast<ksys::act::Actor>(_60.getProc(nullptr, mActor)))
        mActor->sub_71011CCB1C(proc->m139());
}

bool GolemWeakPointRoot::handleMessage_(const ksys::Message* message) {
    if (_1b0.m2(*message))
        return true;
    return WeakPointRoot::handleMessage_(message);
}

void GolemWeakPointRoot::calc_() {
    WeakPointRoot::calc_();

    if (auto* pos = sub_7100739578(mActor)) {
        _1e8 = pos->_0.x;
        _1ec = pos->_0.y;
        _1f0 = pos->_0.z;
    }

    if (_1b0._30) {
        _1b0.x();
        sead::Matrix34f mtx;
        mtx.makeIdentity();
        mtx.m[0][3] = _1e8;
        mtx.m[1][3] = _1ec;
        mtx.m[2][3] = _1f0;
        m38(_1f4, mtx);
        ++_1f4;
    }

    auto* attacker = sead::DynamicCast<ksys::act::Actor>(_60.getProc(nullptr, nullptr));
    if (attacker) {
        if (hasAttackInfo(attacker)) {
            const s32 num = getNumAttackInfoMaybe(attacker);
            for (s32 i = 0; i < num; ++i) {
                auto* info = getAttackInfo(attacker, i);
                if (info && ksys::act::isPlayerProfile(&info->_50)) {
                    mActor->sub_71011CCB1C(attacker->m139());
                    if (auto* body = mActor->getMainBody()) {
                        body->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
                        body->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
                    }
                    return;
                }
            }
        }
        mActor->sub_71011CCB1C(attacker->m139());
    }

    auto* player_link = &ksys::act::PlayerInfo::getSomeProcLink();
    ksys::act::acc::PlayerBase player;
    ksys::act::acquireActor(player_link, &player);
    if (!player.x_23()) {
        if (auto* body = mActor->getMainBody()) {
            body->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            body->disableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
        }
    }
}

bool GolemWeakPointRoot::m36() {
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&_60, &accessor))
        return false;

    const sead::SafeString table = "Milestone";
    for (auto& link : _180) {
        const sead::SafeString& drop = golemWeakPointGetOneDrop(accessor, table);
        auto* actor = ksys::act::ActorCreator::instance()->createActor(
            drop.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr, true,
            false);
        if (actor)
            link.acquire(actor, false);
    }
    return true;
}

void GolemWeakPointRoot::m37() {
    for (auto& link : _180) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.hasProc() && accessor.isStateSleep())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

void GolemWeakPointRoot::m38(s32 idx, const sead::Matrix34f& mtx) {
    if (u32(idx) > 2)
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_180[idx], &accessor);
    if (accessor.hasProc() && accessor.isStateSleep())
        accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
}

void GolemWeakPointRoot::leave_() {
    WeakPointRoot::leave_();
    sub_71007A4440(mActor, &_1f8);
}

void GolemWeakPointRoot::loadParams_() {
    WeakPointRoot::loadParams_();
}

}  // namespace uking::ai
