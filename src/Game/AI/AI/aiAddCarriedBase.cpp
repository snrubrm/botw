#include "Game/AI/AI/aiAddCarriedBase.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AddCarriedBase::AddCarriedBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddCarriedBase::~AddCarriedBase() = default;

bool AddCarriedBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddCarriedBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool AddCarriedBase::updateForPreDelete() {
    return _68.sub_71006F8AB4();
}

bool AddCarriedBase::m34() {
    if (*mFailDistance_s > 0) {
        sead::Matrix34f mtx;
        sub_7100739498(mActor, &mtx);
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - mtx.getTranslation();
        if (diff.squaredLength() > *mFailDistance_s * *mFailDistance_s)
            return true;
    }
    return false;
}

bool AddCarriedBase::hasUpdateForPreDeleteCb() {
    return true;
}

void AddCarriedBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddCarriedBase::loadParams_() {
    getStaticParam(&mFailDistance_s, "FailDistance");
    getStaticParam(&mIsRecoverCharCtrlAxis_s, "IsRecoverCharCtrlAxis");
    getStaticParam(&mIsUseConstraint_s, "IsUseConstraint");
    getStaticParam(&mHoldOnXLinkKey_s, "HoldOnXLinkKey");
}

}  // namespace uking::ai
