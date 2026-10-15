#include "Game/Actor/Action/actionSwitchWindmill.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

SwitchWindmill::SwitchWindmill(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwitchWindmill::~SwitchWindmill() = default;

bool SwitchWindmill::init_(sead::Heap* heap) {
    _130 = 0;
    _134 = 0;
    return true;
}

void SwitchWindmill::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _58.setName(mTargetNodeName_s);
    if (auto* model = actor->getModel()) {
        actor->boneHandleStuff(&_58, false);
        _20.search(model, mTargetNodeName_s);
    }
}

void SwitchWindmill::leave_() {
    mActor->sub_71011DA868(&_58);
    _20.remove();
}

void SwitchWindmill::loadParams_() {
    getStaticParam(&mSwRadTh_s, "SwRadTh");
    getStaticParam(&mSwRadAllowance_s, "SwRadAllowance");
    getStaticParam(&mRotAccel_s, "RotAccel");
    getStaticParam(&mMaxRotSpeed_s, "MaxRotSpeed");
    getStaticParam(&mTargetNodeName_s, "TargetNodeName");
}

// NON_MATCHING: the motion Z component loads later.
void SwitchWindmill::calc_() {
    auto* actor = mActor;
    auto* chemical = actor->getChemicalStuff();
    f32 speed = 0.0f;
    if (chemical) {
        const sead::Vector3f& motion = chemical->_c & (1 << 24) ? sead::Vector3f::zero : chemical->_f0;
        speed = motion.length();
    }
    const f32 step = speed > 0.0f ? speed : *mRotAccel_s;
    const f32 target = speed > 0.0f ? *mMaxRotSpeed_s : 0.0f;
    ksys::VFR::chase(&_134, target, step);
    if (auto* model = actor->getModel()) {
        sead::Matrix34f matrix = sead::Matrix34f::ident;
        sead::Vector3f scale = sead::Vector3f::ones;
        const auto& key = _20.getKey();
        if (key.isValid()) {
            model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneLocalMatrix(
                &matrix, &scale, key.bone_index);
            sead::Matrix34f rotation;
            rotation.makeR(matrix.getBase(1) * _134);
            _58._68 = rotation;
        }
    }
    if (_134 >= *mSwRadTh_s) {
        playAS("On", true, 0, 0, -1.0f);
        actor->emitBasicSigOn();
    } else if (_134 <= *mSwRadTh_s - *mSwRadAllowance_s) {
        playAS("Off", true, 0, 0, -1.0f);
        actor->emitBasicSigOff();
    }
}

bool SwitchWindmill::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003)
        mActor->emitBasicSigOff();
    return false;
}

}  // namespace uking::action
