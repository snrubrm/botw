#include "Game/Actor/Action/actionRestorePlayerPosAndRotate.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

RestorePlayerPosAndRotate::RestorePlayerPosAndRotate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RestorePlayerPosAndRotate::~RestorePlayerPosAndRotate() = default;

bool RestorePlayerPosAndRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original builds the rotate-translate matrix with the translation in vector lanes (ld1) and
// copies the scale with one 8-byte load; same calls and arithmetic.
bool RestorePlayerPosAndRotate::oneShot_() {
    _70 = mActor->getScale();
    sead::Vector3f pos = sead::Vector3f::zero;
    if (!ksys::gdt::Manager::instance()->getParam().get().getVec3f(&pos, mGameDataVec3fPlayerPos_d))
        return false;
    f32 dir_y = 0.0f;
    if (!ksys::gdt::Manager::instance()->getParam().get().getF32(&dir_y,
                                                                 mGameDataFloatPlayerDirectionY_d))
        return false;

    _40.makeS(_70);
    sead::Matrix34f rt;
    rt.makeRT({sead::Vector3f::zero.x, dir_y, sead::Vector3f::zero.z}, pos);
    _40.setMul(rt, _40);

    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (!player.hasProc())
        return false;
    player.setMtx(_40);
    return true;
}

void RestorePlayerPosAndRotate::loadParams_() {
    getDynamicParam(&mGameDataVec3fPlayerPos_d, "GameDataVec3fPlayerPos");
    getDynamicParam(&mGameDataFloatPlayerDirectionY_d, "GameDataFloatPlayerDirectionY");
}

}  // namespace uking::action
