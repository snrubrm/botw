#include "Game/AI/Action/actionBeltConveyor.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BeltConveyor::BeltConveyor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeltConveyor::~BeltConveyor() = default;

bool BeltConveyor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BeltConveyor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

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

void BeltConveyor::calc_() {
    sub_71000C48C0();
}

}  // namespace uking::action
