#include "Game/AI/Action/actionMoveMainRidigBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

MoveMainRidigBody::MoveMainRidigBody(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveMainRidigBody::~MoveMainRidigBody() = default;

bool MoveMainRidigBody::init_(sead::Heap* heap) {
    return _68.acquire(heap, static_cast<Unk_71025afb58**>(mRefPosVibrateChecker_a));
}

void MoveMainRidigBody::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    if (auto* body = mActor->getMainBody()) {
        _60 = !body->hasFlag(ksys::phys::RigidBody::Flag::_2000000);
        body->clearFlag2000000(false);
    } else {
        setFailed();
    }
    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_68._0)) {
            if (*mVibrateMemoryStep_s > 0.0f)
                checker->_84 = *mVibrateMemoryStep_s;
            if (*mVibrateCheckFrame_s > 0.0f)
                checker->_88 = *mVibrateCheckFrame_s;
            checker->_78 = checker->_88;
            checker->_7c = 0;
            checker->_80 = 0;
            checker->_90.setUndef();
            checker->_8c = false;
        }
    }
}

void MoveMainRidigBody::leave_() {
    if (auto* body = mActor->getMainBody())
        body->clearFlag2000000(_60);
}

void MoveMainRidigBody::loadParams_() {
    getStaticParam(&mFinLength_s, "FinLength");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mVibrateStopCheck_s, "VibrateStopCheck");
    getStaticParam(&mVibrateCheckFrame_s, "VibrateCheckFrame");
    getStaticParam(&mVibrateMemoryStep_s, "VibrateMemoryStep");
    getStaticParam(&mTargetPosOffset_s, "TargetPosOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void MoveMainRidigBody::calc_() {
    ksys::act::ai::Action::calc_();
}

bool MoveMainRidigBody::isFinished() const {
    if (ksys::act::ai::Action::isFinished())
        return true;
    const sead::Vector3f target = *mTargetPos_d + *mTargetPosOffset_s;
    return (mActor->getMtx().getTranslation() - target).length() < *mFinLength_s;
}

}  // namespace uking::action
