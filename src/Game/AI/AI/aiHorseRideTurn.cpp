#include "Game/AI/AI/aiHorseRideTurn.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HorseRideTurn::HorseRideTurn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideTurn::~HorseRideTurn() = default;

bool HorseRideTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    _80.x();
    _48.x();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("指令", &pack);
}

void HorseRideTurn::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("指令")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("待機", &pack);
        } else if (child->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    } else if (child->isChangeable()) {
        const sead::Matrix34f& mtx = mActor->getMtx();
        const sead::Vector3f pos = mtx.getTranslation();
        sead::Vector3f front;
        mtx.getBase(front, 2);
        front.normalize();
        sead::Vector3f dir = *mTargetPos_d;
        dir -= pos;
        dir.normalize();
        if (front.dot(dir) >= sead::Mathf::cos(*mFinAngle_s) || _48._30) {
            setFinished();
        } else if (_80._30) {
            setFailed();
        }
    }

    child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void HorseRideTurn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideTurn::loadParams_() {
    getStaticParam(&mFinAngle_s, "FinAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool HorseRideTurn::handleMessage_(const ksys::Message* message) {
    return _48.m2(*message) || _80.m2(*message);
}

}  // namespace uking::ai
