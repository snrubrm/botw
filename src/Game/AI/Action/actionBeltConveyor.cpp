#include "Game/AI/Action/actionBeltConveyor.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

BeltConveyor::BeltConveyor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeltConveyor::~BeltConveyor() = default;

bool BeltConveyor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BeltConveyor::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = 0;
    if (auto* body = mActor->getMainBody()) {
        sead::BoundBox3f aabb;
        body->getAabbInLocal(&aabb);
        _40 = aabb.getHalfSizeY() + aabb.getCenter().y;
    }
    sub_71000C48C0();
    auto* unk = sead::DynamicCast<ksys::act::Unk_7102459df8>(mActor->m126());
    if (unk && unk->_20)
        unk->_20->_588 = sub_71000C4560;
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    mActor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163100,
                             *mRotateSpeed_m * *mASRate_s);}

void BeltConveyor::leave_() {
    auto* unk = sead::DynamicCast<ksys::act::Unk_7102459df8>(mActor->m126());
    if (unk && unk->_20)
        unk->_20->_588 = nullptr;
}

void BeltConveyor::loadParams_() {
    getStaticParam(&mASRate_s, "ASRate");
    getStaticParam(&mIsReverse_s, "IsReverse");
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mRotateSpeed_m, "RotateSpeed");
}

void BeltConveyor::sub_71000C48C0() {
    mActor->getMtx().getBase(_1c, 0);
    _1c.normalize();
    mActor->getMtx().getBase(_34, 1);
    _34.normalize();
    const f32 rate = (*mIsReverse_s ? -*mRotateSpeed_m : *mRotateSpeed_m) / 30;
    _1c *= rate;
    _28 = _1c * ksys::VFR::instance()->getRawDeltaFrame();
}

void BeltConveyor::calc_() {
    sub_71000C48C0();
}

}  // namespace uking::action
