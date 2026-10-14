#include "Game/Actor/Action/actionOnEnterSwapActorBase.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"

namespace uking::action {

OnEnterSwapActorBase::OnEnterSwapActorBase(const InitArg& arg)
    : Fork(arg) {}

OnEnterSwapActorBase::~OnEnterSwapActorBase() {
    if (_38.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_38, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool OnEnterSwapActorBase::init_(sead::Heap* heap) {
    if (!Fork::init_(heap))
        return false;

    sead::FixedSafeString<64> actor_name;
    if (m32(&actor_name) && !actor_name.isEmpty()) {
        auto* actor = ksys::act::ActorCreator::instance()->createActor(
            actor_name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr,
            true, false);
        if (actor)
            _38.acquire(actor, false);
        else
            _38.reset();
    }
    return true;
}

void OnEnterSwapActorBase::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    _48 = mActor->getMtx();
    if (*mOnGroundPos_s) {
        if (isBgGroundHit(mActor, false)) {
            if (auto* entry = sub_71007A4948(mActor, 0))
                _48.setTranslation(entry->_0);
        }
    } else {
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        mActor->x_18(&pos);
        _48.setTranslation(pos);
    }
}

void OnEnterSwapActorBase::leave_() {
    Fork::leave_();
    _38.reset();
}

void OnEnterSwapActorBase::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mOnGroundPos_s, "OnGroundPos");
}

void OnEnterSwapActorBase::calc_() {
    Fork::calc_();
    if (_38.hasProc()) {
        auto* actor = mActor;
        auto* chemical = actor->getName().include("HangedLamp") ? actor->getChemicalStuff() : nullptr;
        if (chemical && chemical->_c0 != 2) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&_38, &accessor);
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        } else {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&_38, &accessor);
            accessor.setProperties(_48, nullptr, nullptr, nullptr, false, 0, -1);
            _38.reset();
        }
    }
    setEndState();
}

bool OnEnterSwapActorBase::m32(sead::BufferedSafeString* name) {
    return false;
}

}  // namespace uking::action
