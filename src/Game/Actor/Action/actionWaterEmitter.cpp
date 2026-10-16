#include "Game/Actor/Action/actionWaterEmitter.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/World/worldElementWater.h"
#include "gsys/gsysModelAccessKey.h"
#include "gsys/gsysModel.h"
#include "gsys/gsysModelUnit.h"

namespace uking::action {

WaterEmitter::WaterEmitter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterEmitter::~WaterEmitter() = default;

bool WaterEmitter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterEmitter::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mBindNodeName_s.isEmpty()) {
        if (auto* model = mActor->getModel())
            _70.search(model, mBindNodeName_s);
    }
    mTimer.rate = 1.0f;
    mTimer.value = 0;
    mTimer.previous_value = 0;
    mFlags.set(Flag::Changeable);
}

void WaterEmitter::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterEmitter::loadParams_() {
    getStaticParam(&mEffectType_s, "EffectType");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mInterval_s, "Interval");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getStaticParam(&mOffset_s, "Offset");
    getStaticParam(&mVelocityDir_s, "VelocityDir");
}

// NON_MATCHING: the original loads the whole actor matrix before the normalise NaN check and keeps it in
// callee-saved registers (40 bytes larger)
void WaterEmitter::calc_() {
    if (ksys::phys::System::instance()->isPaused())
        return;

    mTimer.update();
    if (!(mTimer.value >= *mInterval_s))
        return;

    mTimer.value = 0;
    mTimer.previous_value = 0;

    sead::Vector3f dir = *mVelocityDir_s;
    const sead::Matrix34f& mtx = mActor->getMtx();
    dir.normalize();
    dir.rotate(mtx);

    ElementWaterCreateArg arg;
    arg.actor = mActor;
    arg.position = sub_71002B464C(*mOffset_s);
    arg.direction = dir;
    arg._20 = *mRadius_s;
    arg._24 = *mSpeed_s * 30.0f;
    switch (*mEffectType_s) {
    case 1:
        arg.flags = 9;
        break;
    case 2:
        arg.flags = 0x11;
        break;
    case 3:
        arg.flags = 0x21;
        break;
    default:
        break;
    }
    ElementWater::create(&arg);
}

// NON_MATCHING: two translation loads (w8 / w9) swapped
sead::Vector3f WaterEmitter::sub_71002B464C(const sead::Vector3f& offset) const {
    sead::Matrix34f mtx = mActor->getMtx();
    if (_70.isValid()) {
        if (auto* model = mActor->getModel()) {
            sead::Matrix34f bone_mtx;
            model->getUnits()
                .unsafeAt(_70.getKey().model_unit_index)
                ->mModelUnit->getBoneWorldMatrix(&bone_mtx, _70.getKey().bone_index);
            mtx.setTranslation(bone_mtx.getTranslation());
        }
    }
    return mtx * offset;
}

}  // namespace uking::action
