#include "Game/AI/AI/aiMoveAndFreeFallGondola.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "Game/gameStasisMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/Thread/Message.h"
#include <cfloat>
#include <cmath>

namespace uking::ai {

MoveAndFreeFallGondola::MoveAndFreeFallGondola(const InitArg& arg) : RailMove(arg) {}

MoveAndFreeFallGondola::~MoveAndFreeFallGondola() = default;

bool MoveAndFreeFallGondola::init_(sead::Heap* heap) {
    return RailMove::init_(heap);
}

void MoveAndFreeFallGondola::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!_f0) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        return;
    }
    RailMove::enter_(params);
}

void MoveAndFreeFallGondola::calc_() {
    RailMove::calc_();
    // called through a pointer in the original (not devirtualised)
    if (!isCurrentChild("停止") && (&_40)->m3()) {
        _c0.sub_710070DC38(sead::DynamicCast<ksys::act::Actor>(_b0.getProc(nullptr, nullptr)), false);
        changeChild("停止");
    }
}

void MoveAndFreeFallGondola::sub_71004AFD30(ksys::act::BaseProc* proc) {
    _b0.acquire(proc, false);
}

void MoveAndFreeFallGondola::sub_71004AFD3C(ksys::map::Rail* rail) {
    _f0 = rail;
    _f8 = *mGondolaRailOffsetTime_m;
}

void MoveAndFreeFallGondola::m34() {}
void MoveAndFreeFallGondola::m37() {
    if (!_40.sub_7100EEBB74())
        return;

    // called through a pointer in the original (not devirtualised)
    if (!_40.sub_7100EEBE88() && (&_40)->m3() && m40())
        _40.sub_7100EEBE9C(-_40._58);

    if (!sub_710032C5AC()) {
        _40.x(-1.0f);
        return;
    }
    f32 speed;
    if (!(_f8 <= FLT_EPSILON) || !(_f8 >= -FLT_EPSILON))
        speed = m35() * (_f8 / ksys::VFR::instance()->getRawDeltaTime());
    else
        speed = 0.0f;
    speed += m35() * ksys::VFR::instance()->getDeltaFrame();

    const sead::Vector3f* pos = &_40._30.sub_7100EEB370();
    if (speed > 0.0f) {
        f32 total = 0.0f;
        do {
            const sead::Vector3f prev = *pos;
            const f32 step = fminf(speed - total, 0.01f);
            if (step < sub_7100EEBE90())
                break;
            _40.x(step);
            // called through a pointer in the original (not devirtualised)
            if ((&_40)->m3())
                break;
            pos = &_40._30.sub_7100EEB370();
            total += (*pos - prev).length();
            pos = &_40._30.sub_7100EEB370();
        } while (total < speed);
    }
    _f8 = 0.0f;
}ksys::map::Rail* MoveAndFreeFallGondola::m36() {
    if (sub_7100EEF034(mActor, 0))
        return RailMove::m36();
    return _f0;
}

f32 MoveAndFreeFallGondola::m35() {
    return *mRailMoveSpeed_m;
}

bool MoveAndFreeFallGondola::m40() {
    return false;
}

void MoveAndFreeFallGondola::leave_() {
    RailMove::leave_();
}

void MoveAndFreeFallGondola::loadParams_() {
    RailMove::loadParams_();
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
    getMapUnitParam(&mGondolaRailOffsetTime_m, "GondolaRailOffsetTime");
}

bool MoveAndFreeFallGondola::handleMessage_(const ksys::Message* message) {
    const ksys::MessageType type = message->getType();
    if (type == 0x3000003 || type == 0x3000004) {
        if (!isCurrentChild("停止"))
            sub_71004AF894(message);
    }
    return false;
}

// NON_MATCHING: logic matches, but we keep the address of `accessor` in a callee-saved register across the
// call (extra x22/x23 and a bigger frame); the original rematerializes it for the destructor
void MoveAndFreeFallGondola::sub_71004AF894(const ksys::Message* message) {
    if (!_b0.hasProc())
        return;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_b0, &accessor);
    if (accessor.hasProc()) {
        const auto& source = message->getSource();
        const auto& dest = *accessor.getMessageTransceiverId();
        if (source.isRegistered() && dest.isRegistered() &&
            !(source.queue_id == dest.queue_id && source.id == dest.id)) {
            auto* sender = ksys::act::ActorSystem::instance()->getStasisMessageSender();
            sender->sendMessage(sead::DynamicCast<ksys::act::Actor>(_b0.getProc(nullptr, nullptr)),
                                message->getType(), true);
        }
    }
}

}  // namespace uking::ai
