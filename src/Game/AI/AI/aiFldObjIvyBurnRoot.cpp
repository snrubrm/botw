#include "Game/AI/AI/aiFldObjIvyBurnRoot.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

FldObjIvyBurnRoot::FldObjIvyBurnRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FldObjIvyBurnRoot::~FldObjIvyBurnRoot() = default;

bool FldObjIvyBurnRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FldObjIvyBurnRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FldObjIvyBurnRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FldObjIvyBurnRoot::loadParams_() {}

void FldObjIvyBurnRoot::calc_() {
    sub_710072BA90(mActor);
    auto* unk = mActor->m135();
    if (unk->_4 == 1) {
        mActor->emitBasicSigOn();
    } else if (unk->_4 == 4) {
        mActor->emitGimmickSuccessSignal_1();
    } else {
        if (mActor->checkBasicSig())
            unk->_4 = 1;
        else if (mActor->checkGimmickSuccessSignal())
            unk->_4 = 4;
        else
            return;
        mActor->deleteAndEmit(0);
    }
}

}  // namespace uking::ai
