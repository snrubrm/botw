#include "Game/AI/AI/aiGiantArmorRoot.h"
#include "Game/Actor/actGiantArmor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

GiantArmorRoot::GiantArmorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GiantArmorRoot::~GiantArmorRoot() = default;

bool GiantArmorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantArmorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* armor = sead::DynamicCast<act::GiantArmor>(mActor)) {
        if (sead::DynamicCast<ksys::act::Actor>(armor->_be8.getProc(nullptr, nullptr))) {
            sub_71003F5F6C();
            return;
        }
    }
    auto* body = mActor->getMainBody();
    auto* physics = mActor->getPhysics();
    if (body && physics)
        physics->sub_7100FBAF18(body);
    changeChild("非装備", nullptr);
}

void GiantArmorRoot::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        auto* actor = mActor;
        auto* body = actor->getMainBody();
        auto* physics = actor->getPhysics();
        if (body && physics)
            physics->sub_7100FBAF18(body);
        changeChild("非装備", nullptr);
        return;
    }
    if (!child->isChangeable())
        return;
    bool missing_owner = true;
    if (auto* armor = sead::DynamicCast<act::GiantArmor>(mActor))
        missing_owner = !sead::DynamicCast<ksys::act::Actor>(armor->_be8.getProc(nullptr, nullptr));
    if (isCurrentChild("装備")) {
        if (missing_owner) {
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            auto* actor = mActor;
            auto* body = actor->getMainBody();
            if (body) {
                auto* physics = actor->getPhysics();
                if (physics)
                    physics->sub_7100FBAF18(body);
            }
            changeChild("非装備", nullptr);
        }
    } else if (!missing_owner) {
        sub_71003F5F6C();
    }
}

void GiantArmorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantArmorRoot::loadParams_() {}

}  // namespace uking::ai
