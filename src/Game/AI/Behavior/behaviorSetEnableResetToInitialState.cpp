#include "Game/AI/Behavior/behaviorSetEnableResetToInitialState.h"
#include <limits>
#include <gsys/gsysModel.h>
#include "Game/AI/aiUnk_7100D8C538.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::behavior {

SetEnableResetToInitialState::SetEnableResetToInitialState(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetEnableResetToInitialState::~SetEnableResetToInitialState() = default;

bool SetEnableResetToInitialState::m6(sead::Heap* heap) {
    return true;
}

void SetEnableResetToInitialState::m8() {
    _28.mTimer = ksys::Timer(30.0f, 30.0f);
}

// NON_MATCHING: the first home position retains a separate stack slot.
void SetEnableResetToInitialState::m7() {
    auto* object = mActor->getMapObject();
    if (!object || _28.mTimer.value <= std::numeric_limits<f32>::epsilon())
        return;
    auto* lod = mActor->getLodState();
    if (lod && lod->_1c >= 2) {
        const auto pos = mActor->getMtx().getTranslation();
        const auto& player = getPlayerPosition();
        const f32 dx = player.x - pos.x;
        const f32 dz = player.z - pos.z;
        if (dx * dx + dz * dz >= 400.0f) {
            sead::Vector3f home;
            mActor->getHomePos(&home);
            const auto& player_home = getPlayerPosition();
            const f32 hx = player_home.x - home.x;
            const f32 hz = player_home.z - home.z;
            if (hx * hx + hz * hz >= 400.0f) {
                sead::Vector3f home_pos;
                mActor->getHomePos(&home_pos);
                sead::BoundSphere3f bounding(sead::Vector3f::zero, 0.0f);
                mActor->getModel()->getBounding(&bounding);
                if (!visibilityCheckMaybe(home_pos, bounding.getRadius())) {
                    _28.sub_7100D3BCE4();
                    if (!(_28.mTimer.value <= std::numeric_limits<f32>::epsilon()))
                        return;
                    mActor->becomePreActor(ksys::act::Actor::DeleteType::_1,
                                           ksys::act::BaseProc::DeleteReason::_0);
                    object->resetFlags0(ksys::map::Object::Flag0::_400000);
                    return;
                }
            }
        }
    }
    _28.mTimer = ksys::Timer(30.0f, 30.0f);
}

void SetEnableResetToInitialState::m9() {}

void SetEnableResetToInitialState::loadParams() {

}

}  // namespace uking::behavior
