#include "Game/AI/AI/aiGuardianMiniBeamAttackMove.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGuardianMini.h"

namespace uking::ai {

GuardianMiniBeamAttackMove::GuardianMiniBeamAttackMove(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniBeamAttackMove::~GuardianMiniBeamAttackMove() = default;

void GuardianMiniBeamAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    changeToMove();
}

void GuardianMiniBeamAttackMove::requestCreateBeam() {
    auto* actor = mActor;
    if (!actor)
        return;

    ksys::act::InstParamPack pack;
    pack->addPosition(actor->getMtx().getTranslation());
    pack->add(actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(), "AttackPower");
    pack->add(3.0f, "ScaleTime");
    pack->add(actor->getParam()->getRes().mGParamList->getAttack()->mRange.ref(), "Range");
    ksys::act::ActorCreator::addScale(pack, 1.0f);

    sead::SafeString name;
    if (auto* params = mActor->getParam()->getRes().mGParamList) {
        if (auto* mini = params->getGuardianMini())
            name = mini->mBeamName.ref();
    }
    ksys::act::ActorCreator::instance()->requestCreateActor(
        name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_88, &pack, nullptr,
        1);
}

bool GuardianMiniBeamAttackMove::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void GuardianMiniBeamAttackMove::leave_() {
    _88.deleteProc();
    sub_71005DB498(mActor);
}

void GuardianMiniBeamAttackMove::loadParams_() {
    getStaticParam(&mMoveTime_s, "MoveTime");
    getStaticParam(&mAttackInterval_s, "AttackInterval");
    getStaticParam(&mBeamSpeed_s, "BeamSpeed");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mTargetDistOffset_s, "TargetDistOffset");
}

void GuardianMiniBeamAttackMove::changeToMove() {
    _70 = ksys::Timer(*mMoveTime_s, *mMoveTime_s);
    _7c = ksys::Timer(*mAttackInterval_s, *mAttackInterval_s);
    requestCreateBeam();
    _98 = sub_71005DB4DC(mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

void GuardianMiniBeamAttackMove::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }

    _70.update();
    if (_70.value <= sead::Mathf::epsilon()) {
        sub_7100418694();
        setFinished();
        return;
    }

    if (sub_710041889C())
        sub_710041896C();
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    sub_7100418694();
}

bool GuardianMiniBeamAttackMove::sub_710041889C() {
    if (*mAttackInterval_s < 0)
        return false;

    if (!(_7c.value <= sead::Mathf::epsilon()))
        _7c.update();

    if (_88.hasProcCreationFailed()) {
        _88.deleteProcIfFailed();
        return false;
    }

    if (!_88.isAllocatedOrFailed()) {
        requestCreateBeam();
        _7c = ksys::Timer(*mAttackInterval_s, *mAttackInterval_s);
        return false;
    }

    if (!_88.isProcReady())
        return false;
    return _7c.value <= sead::Mathf::epsilon();
}

}  // namespace uking::ai
