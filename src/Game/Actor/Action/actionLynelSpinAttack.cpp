#include "Game/Actor/Action/actionLynelSpinAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

LynelSpinAttack::LynelSpinAttack(const InitArg& arg) : ForkWeaponAttack(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
LynelSpinAttack::~LynelSpinAttack() {
    ;
}

bool LynelSpinAttack::init_(sead::Heap* heap) {
    return ForkWeaponAttack::init_(heap);
}

// NON_MATCHING: the original computes &mStartASName_s before the m132() call (scheduling)
void LynelSpinAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkWeaponAttackBase::enter_(params);
    mFlags.reset(Flag::Changeable);
    if (auto* rideable = mActor->m132())
        rideable->_18.sub_7100E786F0(mStartASName_s);
    playAS(mStartASName_s.cstr(), false, *mTargetBone_s, *mSeqBank_s, -1.0f);
    _cc = 0;
    _d0 = 0;
}

void LynelSpinAttack::leave_() {
    ForkWeaponAttack::leave_();
}

void LynelSpinAttack::loadParams_() {
    ForkWeaponAttack::loadParams_();
    getStaticParam(&mMinLoopTime_s, "MinLoopTime");
    getStaticParam(&mLoopEndAngle_s, "LoopEndAngle");
    getStaticParam(&mStartASName_s, "StartASName");
    getStaticParam(&mLoopASName_s, "LoopASName");
    getStaticParam(&mEndASName_s, "EndASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: the two "switch AS" sequences (loop / end) are tail-merged here; the original keeps both.
void LynelSpinAttack::calc_() {
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    if (auto* rideable = mActor->m132(); as_list && controller && rideable)
        act::sub_7100E7F698(rideable, as_list, controller);

    switch (_cc) {
    case 0:
        if (isFinishedAS(0, 0)) {
            _cc = 1;
            if (auto* rideable = mActor->m132())
                rideable->_18.sub_7100E786F0(mLoopASName_s);
            playAS(mLoopASName_s.cstr(), false, *mTargetBone_s, *mSeqBank_s, -1.0f);
            _c0.reset(*mMinLoopTime_s);
        }
        break;
    case 1:
        if (_c0.value <= sead::Mathf::epsilon()) {
            sead::Vector3f dir;
            sub_71000891C8(&dir, mActor);
            ksys::util::sub_71011EF010(&dir, -*mLoopEndAngle_s);
            const auto& pos = mActor->getMtx();
            sead::Vector3f to_target(mTargetPos_d->x - pos(0, 3), 0.0f, mTargetPos_d->z - pos(2, 3));
            to_target.normalize();
            int side;
            if (to_target.dot(dir) > 0.0f)
                side = to_target.x * dir.z - to_target.z * dir.x < 0.0f ? 2 : 1;
            else
                side = 3;
            if ((side == 2 && _d0 == 1) || (side == 1 && _d0 == 2)) {
                _cc = 2;
                if (auto* rideable = mActor->m132())
                    rideable->_18.sub_7100E786F0(mEndASName_s);
                playAS(mEndASName_s.cstr(), false, *mTargetBone_s, *mSeqBank_s, -1.0f);
            }
            _d0 = side;
        } else {
            _c0.update();
        }
        break;
    default:
        if (isFinishedAS(0, 0))
            setFinished();
        break;
    }
    ForkWeaponAttackBase::calc_();
}

}  // namespace uking::action
