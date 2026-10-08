#include "Game/AI/Action/actionGiantAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>

namespace uking::action {

GiantAttack::GiantAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GiantAttack::~GiantAttack() = default;

bool GiantAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GiantAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mRotBaseBoneName_s.isEmpty())
        return;
    _90.setName(mRotBaseBoneName_s);
    _90.sub_7100743414(0, true, 0);
}

void GiantAttack::leave_() {
    if (mRotBaseBoneName_s.isEmpty())
        return;
    mActor->sub_71011DA868(&_90);
}

void GiantAttack::loadParams_() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mRotBaseBoneName_s, "RotBaseBoneName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GiantAttack::sub_71002A182C() {
    if (sub_71005DD5B0(mActor, 0x29, nullptr, 0, 0))
        sub_71002A1A08();
    if (sub_71005DD798(mActor, 0x29, nullptr, 0, 0)) {
        sub_71002A1C38();
        return;
    }
    auto* controller = mActor->getCharacterController();
    if (controller) {
        sub_7100737C0C(controller, *mStopSpeedRatio_s, -sead::Vector3f::ey);
        sub_7100738660(controller, *mStopRotSpeedRatio_s);
    }
}

void GiantAttack::calc_() {
    sub_71002A182C();
}

void GiantAttack::sub_71002A1A08() {
    _8c = mActor->getAngVelocity().length();
    if (*mRotBaseBoneName_s.getStringTop() == sead::SafeString::cNullChar) {
        _5c = sead::Vector3f::zero;
        const sead::Matrix34f& mtx = mActor->getMtx();
        _50.x = mtx.m[0][3];
        _50.y = mtx.m[1][3];
        _50.z = mtx.m[2][3];
        return;
    }
    if (_90._8)
        mActor->sub_71011DA868(&_90);
    auto* model = mActor->getModel();
    const gsys::BoneAccessKey key = model->searchBone(mRotBaseBoneName_s);
    if (key.isValid()) {
        sead::Matrix34f bone_mtx;
        model->getUnits()
            .unsafeAt(key.model_unit_index)
            ->mModelUnit->getBoneWorldMatrix(&bone_mtx, key.bone_index);
        _50.x = bone_mtx.m[0][3];
        _50.y = bone_mtx.m[1][3];
        _50.z = bone_mtx.m[2][3];
        sead::Matrix34f inv;
        sead::Matrix34CalcCommon<f32>::inverse(inv, mActor->getMtx());
        const f32 px = _50.x;
        const f32 py = _50.y;
        const f32 pz = _50.z;
        _5c.x = px * inv.m[0][0] + py * inv.m[0][1] + pz * inv.m[0][2] + inv.m[0][3];
        _5c.y = px * inv.m[1][0] + py * inv.m[1][1] + pz * inv.m[1][2] + inv.m[1][3];
        _5c.z = px * inv.m[2][0] + py * inv.m[2][1] + pz * inv.m[2][2] + inv.m[2][3];
    } else {
        _5c = sead::Vector3f::zero;
        const sead::Matrix34f& mtx = mActor->getMtx();
        _50.x = mtx.m[0][3];
        _50.y = mtx.m[1][3];
        _50.z = mtx.m[2][3];
    }
    mActor->boneHandleStuff(&_90, false);
}

}  // namespace uking::action
