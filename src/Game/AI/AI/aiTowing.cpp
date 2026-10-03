#include "Game/AI/AI/aiTowing.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

Towing::Towing(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

Towing::~Towing() = default;

bool Towing::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void Towing::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = 0;
    _40 = *mParams.mAddSpeed_s;
    _3c = *mParams.mInitSpeed_s;
    _44 = 0;
    _74 = false;
    _75 = false;
    _50 = ksys::Timer(*mParams.mStopTowingDef_s, *mParams.mStopTowingDef_s);
    _68 = ksys::Timer(30, 30);

    sead::Vector3f dir = mActor->getMtx().getBase(2);
    dir.normalize();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        controller->sub_7100F5EDBC(dir);
        controller->sub_7100F5E7F0(*mParams.mInitSpeed_s * 30.0f);
        controller->sub_7100F5FDF0(dir);
        controller->sub_7100F5EEB8(1.2f);
    } else {
        setFailed();
    }
    _48.set(0, 0);
    m37();
    changeChild("通常");
}

void Towing::leave_() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    controller->sub_7100F5FB24(sead::Vector3f::zero);
    controller->sub_7100F5E7F0(0.0f);
    controller->sub_7100F5F458(ksys::act::MotionType(1));
    controller->sub_7100F5EEB8(1.0f);
}

void Towing::loadParams_() {
    getStaticParam(&mParams.mKeepMaxTime_s, "KeepMaxTime");
    getStaticParam(&mParams.mStopTowingDef_s, "StopTowingDef");
    getStaticParam(&mParams.mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mParams.mInitSpeed_s, "InitSpeed");
    getStaticParam(&mParams.mAddSpeed_s, "AddSpeed");
    getStaticParam(&mParams.mStandardSpeed_s, "StandardSpeed");
    getStaticParam(&mParams.mBrakeDecSpeed_s, "BrakeDecSpeed");
    getStaticParam(&mParams.mAttFrontRate_s, "AttFrontRate");
    getStaticParam(&mParams.mSandCheckLength_s, "SandCheckLength");
    getStaticParam(&mParams.mSandCheckAngle_s, "SandCheckAngle");
}

void Towing::calc_() {
    if (_75) {
        _50.update();
        if (_50.value <= sead::Mathf::epsilon())
            setFinished();
    }
    m34();
    m35();
    m36();
    m37();
    m38();
}

void Towing::m34() {
    switch (_38) {
    case 1:
        if (_3c >= *mParams.mMaxSpeed_s) {
            _38 = 2;
            _5c = ksys::Timer(*mParams.mKeepMaxTime_s, *mParams.mKeepMaxTime_s);
        }
        break;
    case 2:
        _5c.update();
        if (_5c.value <= sead::Mathf::epsilon())
            _38 = 3;
        break;
    case 3:
        if (_3c <= *mParams.mStandardSpeed_s)
            _38 = 0;
        break;
    default:
        break;
    }
}

void Towing::m38() {}

}  // namespace uking::ai
