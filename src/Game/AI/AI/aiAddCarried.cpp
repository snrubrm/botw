#include "Game/AI/AI/aiAddCarried.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AddCarried::AddCarried(const InitArg& arg) : AddCarriedBase(arg) {}

AddCarried::~AddCarried() = default;

bool AddCarried::init_(sead::Heap* heap) {
    return AddCarriedBase::init_(heap);
}

void AddCarried::enter_(ksys::act::ai::InlineParamPack* params) {
    AddCarriedBase::enter_(params);
}

void AddCarried::leave_() {
    AddCarriedBase::leave_();
}

void AddCarried::loadParams_() {
    AddCarriedBase::loadParams_();
}

void AddCarried::m36() {
    auto* actor = mActor;
    _c0._28 = sub_71005DC5AC(actor).cstr();
    _c0._30.getKey().reset();
    _c0._68 = sub_71005DC57C(actor);
    _c0._98 = 0;
}


}  // namespace uking::ai
