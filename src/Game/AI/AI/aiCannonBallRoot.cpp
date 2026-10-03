#include "Game/AI/AI/aiCannonBallRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

CannonBallRoot::CannonBallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CannonBallRoot::~CannonBallRoot() = default;

bool CannonBallRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CannonBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (actor->getCreateArgBaseProcLink().hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&actor->getCreateArgBaseProcLink(), &accessor);
        if (accessor.hasProc()) {
            if (auto* physics = actor->getPhysics())
                physics->sub_7100FBDFA4(accessor.x(0));
        }
    }
    changeChild("通常");
}

void CannonBallRoot::calc_() {}

void CannonBallRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CannonBallRoot::loadParams_() {}

}  // namespace uking::ai
