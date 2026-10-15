#include "Game/Actor/AI/aiNPCArtistRoot.h"
#include "Game/Actor/actNPC.h"
#include "Game/Actor/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

namespace uking::ai {

static const sead::SafeString sUnk_710240AAB8 = "Hair_Root";

NPCArtistRoot::NPCArtistRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCArtistRoot::~NPCArtistRoot() {
    mActor->sub_71011DA868(&_248);
}

// NON_MATCHING: the original loads sead::Vector3f::zero once, before the sin/cos calls; ours
// reloads it after each call
bool NPCArtistRoot::init_(sead::Heap* heap) {
    if (!NPCRoot::init_(heap))
        return false;
    _308 = sead::DynamicCast<act::NPC>(mActor);
    _248.setName(sUnk_710240AAB8);
    mActor->boneHandleStuff(&_248, false);
    _248._68.makeRT(sead::Vector3f::zero, sead::Vector3f::zero);
    return true;
}

// NON_MATCHING: Timer stores and matrix construction are scheduled differently.
void NPCArtistRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
    if (!mActor->isCalc())
        return;
    const bool sleeping = _308 && _308->_1028 == "Sleep";
    const bool bad_weather = wm::callIsRainingOrSnowingOrThunderStorm(true);
    if (sleeping || !bad_weather) {
        _2f0 = false;
        _2f4 = 0.0f;
        _2f8 = ksys::Timer(50.0f, 50.0f);
        const sead::Vector3f zero = sead::Vector3f::zero;
        _248._68.makeRT(zero, zero);
    } else {
        _2f0 = true;
        _2f4 = 1.0f;
        _2f8 = ksys::Timer(60.0f, 60.0f);
        _248._68.makeRT({0.0f, 0.0f, -sead::Mathf::deg2rad(35.0f)},
                       {-0.0147f, -0.0298f, 0.0f});
    }
}

void NPCArtistRoot::leave_() {
    if (mActor->getRootAi()->getNewChildIdx() != 0) {
        if (auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild())) {
            mActor->resetConnectedCalcChild(false);
            child->deleteEx(ksys::act::Actor::DeleteType::_1,
                            ksys::act::BaseProc::DeleteReason::_0, nullptr);
        }
    }
    NPCRoot::leave_();
}

void NPCArtistRoot::loadParams_() {
    NPCRoot::loadParams_();
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai
