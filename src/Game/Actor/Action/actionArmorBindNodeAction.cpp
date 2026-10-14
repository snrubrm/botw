#include "Game/Actor/Action/actionArmorBindNodeAction.h"
#include "Game/Actor/actArmorBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::action {

ArmorBindNodeAction::ArmorBindNodeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ArmorBindNodeAction::~ArmorBindNodeAction() = default;

void ArmorBindNodeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    if (auto* armor = sead::DynamicCast<act::ArmorBase>(mActor)) {
        if (auto* bind = m32()) {
            bind->x(armor->getOwner());
            bind->_28 = mBoneName_d.cstr();
            bind->_30.getKey().reset();
            const sead::Vector3f rotation = *mRotOffsetXyz_d;
            bind->_68.makeRT(rotation, *mPosOffset_d);
            if (!armor->getModelBindInfo())
                mActor->sub_71011DA824(bind);
        }
    }
}

void ArmorBindNodeAction::leave_() {
    if (auto* bind = m32())
        mActor->sub_71011DA834(bind);
}

void ArmorBindNodeAction::loadParams_() {
    getDynamicParam(&mBoneName_d, "BoneName");
    getDynamicParam(&mPosOffset_d, "PosOffset");
    getDynamicParam(&mRotOffsetXyz_d, "RotOffsetXyz");
}

void ArmorBindNodeAction::calc_() {
    if (auto* bind = m32()) {
        const sead::Vector3f rotation = *mRotOffsetXyz_d;
        bind->_68.makeRT(rotation, *mPosOffset_d);
    }
}

ksys::act::ModelBindInfo* ArmorBindNodeAction::m32() {
    auto* actor = mActor;
    return sead::IsDerivedFrom<act::ArmorBase>(actor) ? &static_cast<act::ArmorBase*>(actor)->_8f8 :
                                                         nullptr;
}

}  // namespace uking::action
