#include "Game/AI/Action/actionGelJumpTackle.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actGelEnemy.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

GelJumpTackle::GelJumpTackle(const InitArg& arg) : JumpTackle(arg) {}

GelJumpTackle::~GelJumpTackle() = default;

bool GelJumpTackle::init_(sead::Heap* heap) {
    return JumpTackle::init_(heap);
}

void GelJumpTackle::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpTackle::enter_(params);
}

void GelJumpTackle::leave_() {
    JumpTackle::leave_();
}

void GelJumpTackle::loadParams_() {
    JumpTackle::loadParams_();
    getStaticParam(&mSubASSlot_s, "SubASSlot");
    getStaticParam(&mBodyRotSpeed_s, "BodyRotSpeed");
    getStaticParam(&mIsEnableCloth_s, "IsEnableCloth");
    getStaticParam(&mSubAS_s, "SubAS");
    getStaticParam(&mLeaveSubAS_s, "LeaveSubAS");
}

// NON_MATCHING: the original copies the bone matrix with 128-bit loads and multiplies with scalar
// lane extracts; the rotation (Matrix33 makeR + setMul) and the sin/cos sequence match
void GelJumpTackle::calc_() {
    if (_90 && !isFailed() && !isFinished() && isBgGroundHit(mActor, false))
        ksys::eft::searchAndEmitSLink(mActor, "JumpAttackLand", false);

    if (*mBodyRotSpeed_s > sead::Mathf::epsilon() || *mBodyRotSpeed_s < -sead::Mathf::epsilon()) {
        if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor)) {
            const sead::Matrix34f mtx = gel->_14c8._68;
            sead::Vector3f rot = sead::Vector3f::zero;
            rot.x += *mBodyRotSpeed_s * ksys::VFR::instance()->getDeltaFrame();
            sead::Matrix33f rot_mtx;
            rot_mtx.makeR(rot);
            gel->_14c8._68.setMul(rot_mtx, mtx);
        }
    }

    JumpTackle::calc_();
}

}  // namespace uking::action
