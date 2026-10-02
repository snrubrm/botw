#include "Game/AI/Action/actionForkOnEnterSwapDropTableActorBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"

namespace uking::action {

ForkOnEnterSwapDropTableActorBase::ForkOnEnterSwapDropTableActorBase(const InitArg& arg)
    : Fork(arg) {}

ForkOnEnterSwapDropTableActorBase::~ForkOnEnterSwapDropTableActorBase() {
    if (_38.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_38, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool ForkOnEnterSwapDropTableActorBase::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkOnEnterSwapDropTableActorBase::enter_(ksys::act::ai::InlineParamPack* params) {
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

void ForkOnEnterSwapDropTableActorBase::leave_() {
    Fork::leave_();
    _38.reset();
}

void ForkOnEnterSwapDropTableActorBase::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mOnGroundPos_s, "OnGroundPos");
}

void ForkOnEnterSwapDropTableActorBase::calc_() {
    Fork::calc_();
}

bool ForkOnEnterSwapDropTableActorBase::m32(sead::BufferedSafeString* name) {
    return false;
}

}  // namespace uking::action
