#include <limits>
#include "Game/AI/Action/actionNavMeshConnectAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

NavMeshConnectAction::NavMeshConnectAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NavMeshConnectAction::~NavMeshConnectAction() = default;

bool NavMeshConnectAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original tests `size == 0` and `size < 2` in two separate branches (ours folds them
// into one ccmp) and adds the (0, 1.5, 0) offset to the translation after the sin/cos calls of makeRT
void NavMeshConnectAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _4c = std::numeric_limits<f32>::infinity();
    _50 = false;
    _51 = false;
    auto* body = mActor->getPhysics()->findBodyByName("NavMeshConnect");
    if (!body)
        return;
    auto* object = mActor->getMapObject();
    auto* link_data = object ? object->getLinkData() : nullptr;
    if (link_data && link_data->mObjects.size() != 0) {
        if (link_data->mObjects.size() < 2) {
            _1c.makeRT(link_data->mObjects[0]->getRotate(),
                       link_data->mObjects[0]->getTranslate() + sead::Vector3f{0, 1.5f, 0});
            _50 = true;
            return;
        }
    }
    body->removeFromWorld();
}

void NavMeshConnectAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void NavMeshConnectAction::loadParams_() {}

// NON_MATCHING: identical except that ours sinks the two `_51` stores into one (mov w8 / strb after the join); the original stores
// `_51` in each arm and only shares `_4c = 0`
void NavMeshConnectAction::calc_() {
    if (!_50)
        return;
    ksys::Timer::update(&_4c, 1.0f);
    if (_4c < 30.0f)
        return;
    auto* body = mActor->getPhysics()->findBodyByName("NavMeshConnect");
    if (!body)
        return;
    if (mActor->checkBasicSig()) {
        if (!_51)
            return;
        body->removeFromWorld();
        _51 = false;
    } else {
        if (_51)
            return;
        body->setTransform(_1c);
        body->addToWorld();
        _51 = true;
    }
    _4c = 0;
}

}  // namespace uking::action
