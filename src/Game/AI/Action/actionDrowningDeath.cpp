#include "Game/AI/Action/actionDrowningDeath.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"

namespace uking::action {

DrowningDeath::DrowningDeath(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DrowningDeath::~DrowningDeath() = default;

bool DrowningDeath::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DrowningDeath::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = false;
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (dynamic_actor->_868)
            _38 = dynamic_actor->_868->sub_71006ED9EC();
    }
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = 1;
    if (_38)
        playAS("Die", false, 0, 0, -1.0f);
    else
        playAS("Drown", false, 0, 0, -1.0f);
    if (auto* controller = mActor->getCharacterController())
        _30.changeMotionType(controller, ksys::act::MotionType::Hover);
    sub_71005D8748(mActor, sead::Vector3f::zero, true, false, nullptr, false);
}

void DrowningDeath::leave_() {
    _30.resetMotionType(_30.sub_710072ACF8(mActor));
}

void DrowningDeath::loadParams_() {
    getStaticParam(&mPosBaseRagdollRbName_s, "PosBaseRagdollRbName");
}

void DrowningDeath::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
