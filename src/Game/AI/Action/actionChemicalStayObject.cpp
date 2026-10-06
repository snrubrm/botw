#include "Game/AI/Action/actionChemicalStayObject.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

ChemicalStayObject::ChemicalStayObject(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChemicalStayObject::~ChemicalStayObject() {
    if (_1a8.isBufferReady()) {
        for (s32 i = 0; i < _1a8.size(); ++i) {
            if (_1a8[i].hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&_1a8[i], &accessor);
                if (!accessor.isDeletedOrDeleting())
                    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            }
        }
        _1a8.freeBuffer();
    }
}

bool ChemicalStayObject::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChemicalStayObject::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChemicalStayObject::leave_() {
    if (*mIsBindToGeneratedActor_s)
        mActor->sub_71011DA834(&_f8);

    if (sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent()))
        mActor->resetConnectedCalcParent(false);
}

void ChemicalStayObject::loadParams_() {
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mDeleteTime_s, "DeleteTime");
    getStaticParam(&mCurveAng_s, "CurveAng");
    getStaticParam(&mReduceVelRate_s, "ReduceVelRate");
    getStaticParam(&mCurveAngRandomRange_s, "CurveAngRandomRange");
    getStaticParam(&mReduceVelRandomRange_s, "ReduceVelRandomRange");
    getStaticParam(&mSideAmplitude_s, "SideAmplitude");
    getStaticParam(&mIsBindToGeneratedActor_s, "IsBindToGeneratedActor");
    getStaticParam(&mIsChemicalAttack_s, "IsChemicalAttack");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getStaticParam(&mBindOffset_s, "BindOffset");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mCreateLimit_m, "CreateLimit");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
}

void ChemicalStayObject::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
