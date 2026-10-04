#include "Game/AI/Action/actionCarried.h"
#include "Game/AI/aiUnk_7100739498.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Carried::Carried(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Carried::~Carried() = default;

bool Carried::init_(sead::Heap* heap) {
    if (*mIsUseConstraint_s) {
        if (!_110.init(heap))
            return false;
    }
    return true;
}

void Carried::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Carried::leave_() {
    ksys::act::ai::Action::leave_();
}

void Carried::loadParams_() {
    getStaticParam(&mBindType_s, "BindType");
    getStaticParam(&mFailDistance_s, "FailDistance");
    getStaticParam(&mIsCreateItem_s, "IsCreateItem");
    getStaticParam(&mIsRecoverCharCtrlAxis_s, "IsRecoverCharCtrlAxis");
    getStaticParam(&mIsUseConstraint_s, "IsUseConstraint");
    getStaticParam(&mIsOnBaseLink_s, "IsOnBaseLink");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mHoldOnXLinkKey_s, "HoldOnXLinkKey");
}

void Carried::calc_() {
    ksys::act::ai::Action::calc_();
}

bool Carried::hasUpdateForPreDeleteCb() {
    return true;
}

bool Carried::updateForPreDelete() {
    return _110.sub_71006F8AB4();
}

bool Carried::m32() {
    if (*mFailDistance_s > 0.0f) {
        sead::Matrix34f mtx;
        sub_7100739498(mActor, &mtx);
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        sead::Vector3f target;
        mtx.getTranslation(target);
        const sead::Vector3f diff = pos - target;
        if (diff.squaredLength() > *mFailDistance_s * *mFailDistance_s)
            return true;
    }
    return false;
}

}  // namespace uking::action
