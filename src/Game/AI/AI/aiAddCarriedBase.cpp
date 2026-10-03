#include "Game/AI/AI/aiAddCarriedBase.h"
#include "Game/AI/aiUnk_7100739498.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AddCarriedBase::AddCarriedBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddCarriedBase::~AddCarriedBase() = default;

bool AddCarriedBase::init_(sead::Heap* heap) {
    if (*mIsUseConstraint_s) {
        if (!_68.init(heap))
            return false;
    }
    return true;
}

void AddCarriedBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool AddCarriedBase::hasUpdateForPreDeleteCb() {
    return true;
}

void AddCarriedBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

bool AddCarriedBase::m34() {
    if (*mFailDistance_s > 0.0f) {
        sead::Matrix34f mtx;
        sub_7100739498(mActor, &mtx);
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - mtx.getTranslation();
        if (diff.squaredLength() > *mFailDistance_s * *mFailDistance_s)
            return true;
    }
    return false;
}

bool AddCarriedBase::m38() {
    return true;
}

void AddCarriedBase::loadParams_() {
    getStaticParam(&mFailDistance_s, "FailDistance");
    getStaticParam(&mIsRecoverCharCtrlAxis_s, "IsRecoverCharCtrlAxis");
    getStaticParam(&mIsUseConstraint_s, "IsUseConstraint");
    getStaticParam(&mHoldOnXLinkKey_s, "HoldOnXLinkKey");
}

}  // namespace uking::ai
