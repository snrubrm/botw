#include "Game/AI/AI/aiAddNodeNodeCarried.h"
#include <math/seadQuat.h>
#include "Game/AI/aiUnk_71005D6D10.h"

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

void AddNodeNodeCarried::m37(const sead::Matrix34f& mtx) {
    sead::Vector3f axis = *mNodeRotOffset_s;
    const f32 angle = axis.normalize();
    sead::Quatf q;
    q.setAxisRadian(axis, angle);
    sead::Matrix34f rot;
    rot.fromQuat(q);
    _c0._40.setMul(mtx, rot);
}

void AddNodeNodeCarried::m36() {
    const char* parent_node = sub_71005DC5AC(mActor).cstr();
    const char* my_node = mMyNode_s.cstr();
    _c0._28 = parent_node;
    _c0._30 = my_node;
    _c0._38 = -1;
    sead::Vector3f axis = *mNodeRotOffset_s;
    const f32 angle = axis.normalize();
    sead::Quatf q;
    q.setAxisRadian(axis, angle);
    sead::Matrix34f rot;
    rot.fromQuat(q);
    _c0._40 = rot;
}

}  // namespace uking::ai
