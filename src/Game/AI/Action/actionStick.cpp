#include "Game/AI/Action/actionStick.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"

namespace uking::action {

Stick::Stick(const InitArg& arg) : ActionEx(arg) {}

Stick::~Stick() = default;

void Stick::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Stick::leave_() {
    auto* actor = mActor;
    if (_160 == 3)
        actor->sub_71011DA834(&_c0);
    else
        actor->sub_71011DA834(&_48);
}

void Stick::loadParams_() {
    if (!mActor->getParam())
        return;
    getDynamicParam(&mStickPos_d, "StickPos");
    getDynamicParam(&mStickPosDiv_d, "StickPosDiv");
    getDynamicParam(&mStickActor_d, "StickActor");
    getDynamicParam(&mStickBodyName_d, "StickBodyName");
}

// NON_MATCHING: the original makes a real vtable call for the bind's m10 (ours devirtualises the empty ActorBind::m10).
bool Stick::sub_710027D3AC() {
    if (!mStickActor_d)
        return false;
    if (mStickActor_d->isAccessingSpecifiedProcUnsafe(nullptr))
        return false;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mStickActor_d->getProc(nullptr, nullptr));
    if (!actor)
        return false;
    auto& parent_link = actor->getParentLinkMaybe();
    if (!parent_link.hasProc())
        return false;
    if (!parent_link.isAccessingSpecifiedProcUnsafe(nullptr))
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&parent_link, &accessor);
    if (accessor.isStateCalc()) {
        _48._58 = parent_link;
        _48._8.acquire(nullptr, false);
        _48.m10(&_48._8);
        return true;
    }
    return false;
}

void Stick::calc_() {
    switch (_160) {
    case 2:
    case 3: {
        {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&_48._58, &accessor);
            if (!accessor.hasProc() || !accessor.isStateCalc()) {
                mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                return;
            }
        }
        if (_160 == 3) {
            if (_164) {
                ksys::act::acc::WeaponBase accessor;
                ksys::act::acquireActor(mStickActor_d, &accessor);
                if (accessor.hasProc() && accessor.sub_7100EFB338()) {
                    if (auto* info = accessor.getBindInfo()) {
                        if (_c0._28 != info->_28) {
                            _c0._28 = info->_28;
                            _c0._30.getKey().reset();
                        }
                    }
                }
            }
            auto* actor = _c0.sub_7100D3C5E0(mActor);
            if (!actor || !actor->getModel() || !actor->isCalc())
                mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
        break;
    }
    case 1:
        if (sub_710027D3AC()) {
            _160 = 2;
        } else {
            auto* actor = _48.sub_7100D3C5E0(mActor);
            if (!actor || !actor->getModel() || !actor->isCalc())
                mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        }
        break;
    }
}

}  // namespace uking::action
