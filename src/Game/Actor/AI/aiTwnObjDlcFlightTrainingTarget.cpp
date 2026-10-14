#include "Game/Actor/AI/aiTwnObjDlcFlightTrainingTarget.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

TwnObjDlcFlightTrainingTarget::TwnObjDlcFlightTrainingTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

TwnObjDlcFlightTrainingTarget::~TwnObjDlcFlightTrainingTarget() = default;

bool TwnObjDlcFlightTrainingTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TwnObjDlcFlightTrainingTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("待機");
    mActor->getModel()->x(true, 0);
    sub_71007A3540(mActor);
    mActor->emitBasicSigOff();
    if (ksys::gdt::getFlag_BalladOfHeroRito_TargetEffect(false))
        xlinkSearchAndEmit(mActor, "FlightTrainingTarget_Open", 2, nullptr);
}

void TwnObjDlcFlightTrainingTarget::calc_() {
    if (!_45 && !ksys::gdt::getFlag_BalladOfHeroRito_TargetEffect(false)) {
        sub_710124127C(mActor, 2);
        _45 = true;
    }

    if (isCurrentChild("待機")) {
        auto* life = mActor->getLife();
        if (life && *life <= 0) {
            changeChild("壊れ");
            sub_71005D34D8();
            _40 = *mLimitTime_s;
        }
    } else if (isCurrentChild("壊れ")) {
        if (ksys::gdt::getFlag_BalladOfHeroRito_TargetEffect(false))
            _44 = !ksys::gdt::getFlag_BalladOfHeroRito_TargetHittingSuccess(false);
        else
            _44 = false;
        if (!_44) {
            if (auto* object = mActor->getMapObject())
                object->setFlags0(ksys::map::Object::Flag0::_100000);
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        } else {
            _40 -= ksys::VFR::instance()->getDeltaTime();
            if (_40 < 0.0f) {
                changeChild("復活");
                auto* actor = mActor;
                const s32 max_life = actor->getMaxLife();
                if (auto* life = actor->getLife())
                    *life = max_life;
                if (auto* body = mActor->getMainBody())
                    body->addToWorld();
            }
        }
    } else if (isCurrentChild("復活")) {
        changeChild("待機");
        mActor->getModel()->x(true, 0);
        sub_71007A3540(mActor);
        mActor->emitBasicSigOff();
        if (ksys::gdt::getFlag_BalladOfHeroRito_TargetEffect(false))
            xlinkSearchAndEmit(mActor, "FlightTrainingTarget_Open", 2, nullptr);
    }
}

void TwnObjDlcFlightTrainingTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TwnObjDlcFlightTrainingTarget::loadParams_() {
    getStaticParam(&mLimitTime_s, "LimitTime");
}

// 0x71005d34d8
void TwnObjDlcFlightTrainingTarget::sub_71005D34D8() {
    sub_71005D35A8();
    sub_710124127C(mActor, 2);
    if (ksys::gdt::getFlag_BalladOfHeroRito_TargetEffect(false))
        xlinkSearchAndEmit(mActor, "FlightTrainingTarget_End", 2, nullptr);
    mActor->emitDisappearEffect();
    mActor->getModel()->x(false, 0);
    if (auto* body = mActor->getMainBody())
        body->removeFromWorld();
    sub_71007A36BC(mActor);
    mActor->emitBasicSigOn();
}

// 0x71005d35a8: deletes the actors linked to the sensor entries with flag 8
void TwnObjDlcFlightTrainingTarget::sub_71005D35A8() {
    const s32 count = sub_71007A26AC(mActor);
    for (s32 i = 0; i < count; ++i) {
        auto* entry = sub_71007A255C(mActor, i);
        if (!entry || !entry->sub_71007A1F68(8))
            continue;
        if (!entry->_e8.hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&entry->_e8, &accessor);
        accessor.deleteEx(ksys::act::BaseProc::DeleteReason(0));
    }
}

}  // namespace uking::ai
