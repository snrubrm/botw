#include "Game/AI/AI/aiViewfrustumCheckTagRoot.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_7100D8C538.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/System/CameraMgr.h"

namespace uking::ai {

ViewfrustumCheckTagRoot::ViewfrustumCheckTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ViewfrustumCheckTagRoot::~ViewfrustumCheckTagRoot() = default;

bool ViewfrustumCheckTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ViewfrustumCheckTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// 0x71005e47a0
// NON_MATCHING: position-load scheduling across the player lookup and stack placement differ.
void ViewfrustumCheckTagRoot::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (!actor || !child)
        return;
    actor->m107();
    if (!_48 || actor->checkBasicSig()) {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        bool visible = visibilityCheckMaybe(pos, mActor->getScale().x);
        if (!visible && *mAllwaysOnDisFromPlayer_m != -1.0f) {
            const auto& matrix = mActor->getMtx();
            const auto& player = getPlayerPosition();
            visible = sead::Vector2f(matrix.m[0][3] - player.x, matrix.m[2][3] - player.z).length() <
                      *mAllwaysOnDisFromPlayer_m;
        }
        if (visible || sub_71005E4698()) {
            if (isCurrentChild("Off"))
                changeChild("On");
            return;
        }
    }
    if (isCurrentChild("On"))
        changeChild("Off");
}

void ViewfrustumCheckTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ViewfrustumCheckTagRoot::loadParams_() {
    getMapUnitParam(&mAllwaysOnDisFromPlayer_m, "AllwaysOnDisFromPlayer");
    getMapUnitParam(&mAllwaysOnCamDir_m, "AllwaysOnCamDir");
}

// NON_MATCHING: operation order / float register allocation of the flattened cross and dot products (the
// original needs one callee-saved float register only)
// 0x71005e4698
bool ViewfrustumCheckTagRoot::sub_71005E4698() {
    if (*mAllwaysOnCamDir_m == -1.0f)
        return false;

    sead::Vector3f camera_pos;
    cam::getCameraPositionMaybe(&camera_pos);
    sead::Vector3f camera_dir;
    ksys::sub_7100D8C7FC(&camera_dir);
    camera_dir.y = 0;
    sead::Vector3f diff;
    diff.x = mActor->getMtx().m[0][3] - camera_pos.x;
    diff.y = 0;
    diff.z = mActor->getMtx().m[2][3] - camera_pos.z;
    sead::Vector3f cross;
    cross.setCross(diff, camera_dir);
    const f32 angle = std::atan2(cross.length(), diff.dot(camera_dir));
    return angle < sead::Mathf::deg2rad(*mAllwaysOnCamDir_m);
}

}  // namespace uking::ai
