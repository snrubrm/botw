#include "Game/AI/Action/actionSiteBossSwordAfterImageAction.h"
#include "Game/AI/Action/actionSiteBossSwordAfterImageMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

SiteBossSwordAfterImageAction::SiteBossSwordAfterImageAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossSwordAfterImageAction::~SiteBossSwordAfterImageAction() = default;

bool SiteBossSwordAfterImageAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSwordAfterImageAction::enter_(ksys::act::ai::InlineParamPack* params) {
    switch (*mCount_m) {
    case 0:
        playAS("Run_Start", false, 0, 0, -1.0f);
        break;
    case 1:
        playAS("Run_Start_NoShield", false, 0, 0, -1.0f);
        break;
    case 2:
    case 4:
        playAS("Run_End_L", false, 0, 0, -1.0f);
        break;
    case 3:
        playAS("Run_End_R", false, 0, 0, -1.0f);
        break;
    case 5:
        playAS("Back_Run_Start", false, 0, 0, -1.0f);
        break;
    case 6:
        playAS("Back_Run_Start_NoShield", false, 0, 0, -1.0f);
        break;
    case 7:
    case 8:
    case 9:
        playAS("Attack_Jump_Start", false, 0, 0, -1.0f);
        break;
    default:
        playAS("BugCheck_Run_Start", false, 0, 0, -1.0f);
        break;
    }
    if (*mCount_m != 4) {
        auto* var = static_cast<Unk_71025afb58**>(mSiteBossSwordAfterImageUnit_a);
        if (auto* obj = *var) {
            if (auto* unit = sead::DynamicCast<SiteBossSwordAfterImageMove::Unit>(obj)) {
                if (unit->_8)
                    _30 = ksys::eft::searchAndEmitELink(mActor, "Elec_Sword");
                else if (unit->_9)
                    _40 = ksys::eft::searchAndEmitELink(mActor, "Elec_Shield");
            }
        }
    }
    if (auto* body = mActor->getMainBody())
        body->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
}

void SiteBossSwordAfterImageAction::leave_() {
    _30.kill();
    _40.kill();
}

void SiteBossSwordAfterImageAction::loadParams_() {
    getMapUnitParam(&mCount_m, "Count");
    getAITreeVariable(&mSiteBossSwordAfterImageUnit_a, "SiteBossSwordAfterImageUnit");
}

void SiteBossSwordAfterImageAction::calc_() {
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
