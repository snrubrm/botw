#include "Game/AI/AI/aiAddNodeNodeCarried.h"
#include <math/seadQuat.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AddNodeNodeCarried::AddNodeNodeCarried(const InitArg& arg) : AddCarriedBase(arg) {}

AddNodeNodeCarried::~AddNodeNodeCarried() = default;

bool AddNodeNodeCarried::init_(sead::Heap* heap) {
    return AddCarriedBase::init_(heap);
}

void AddNodeNodeCarried::enter_(ksys::act::ai::InlineParamPack* params) {
    AddCarriedBase::enter_(params);
}

void AddNodeNodeCarried::leave_() {
    AddCarriedBase::leave_();
}

void AddNodeNodeCarried::loadParams_() {
    AddCarriedBase::loadParams_();
    getStaticParam(&mMyNode_s, "MyNode");
    getStaticParam(&mNodeRotOffset_s, "NodeRotOffset");
}

ksys::act::ActorBind* AddNodeNodeCarried::m35() {
    return &_c0;
}

// NON_MATCHING: the original reads both string tops after the second assureTermination vcall; scheduling of
// the quaternion math differs
void AddNodeNodeCarried::m36() {
    _c0._28 = sub_71005DC5AC(mActor).cstr();
    _c0._30 = mMyNode_s.cstr();
    _c0._38 = -1;

    sead::Vector3f axis = *mNodeRotOffset_s;
    const f32 angle = axis.normalize();
    sead::Quatf q;
    q.setAxisRadian(axis, angle);
    _c0._40.fromQuat(q);
}

// NON_MATCHING: the original multiplies with the generic 3x4 NEON sequence (translation lane kept); ours
// folds the zero translation of the rotation matrix
void AddNodeNodeCarried::m37(const sead::Matrix34f& mtx) {
    sead::Vector3f axis = *mNodeRotOffset_s;
    const f32 angle = axis.normalize();
    sead::Quatf q;
    q.setAxisRadian(axis, angle);
    sead::Matrix34f rot;
    rot.fromQuat(q);
    _c0._40.setMul(rot, mtx);
}

bool AddNodeNodeCarried::m38() {
    return false;
}

}  // namespace uking::ai
