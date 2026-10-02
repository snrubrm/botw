#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include <controller/seadController.h>
#include "Game/gameMaskController.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/MathUtil.h"

bool sub_71009269F8(const sead::Vector3f& pos, f32* out) {
    return sub_7100926430(pos, 3, out, 1.0f, 1.0f, 5.0f);
}

ksys::act::PlayerBase* sub_7100926A14() {
    if (auto* info = ksys::act::PlayerInfo::instance())
        return info->getPlayer();
    return nullptr;
}

// NON_MATCHING: the original calls getPlayer_ with bl + ret instead of a tail call (return types
// differ somehow)
ksys::act::PlayerBase* sub_7100926A2C() {
    if (auto* info = ksys::act::PlayerInfo::instance())
        return info->getPlayer_();
    return nullptr;
}

void sub_7100926A50(ksys::act::ActorConstDataAccess* accessor) {
    if (auto* info = ksys::act::PlayerInfo::instance())
        ksys::act::acquireActor(&info->getPlayerLink(), accessor);
}

bool sub_7100926A74(ksys::act::ActorConstDataAccess* accessor) {
    if (auto* info = ksys::act::PlayerInfo::instance())
        return ksys::act::acquireActor(&info->getHorseLink(), accessor);
    return false;
}

bool sub_7100926A9C(ksys::act::ActorConstDataAccess* accessor) {
    if (auto* info = ksys::act::PlayerInfo::instance())
        return ksys::act::acquireActor(&info->getHorseLink(), accessor);
    return false;
}

bool sub_7100926CB0() {
    ksys::act::acc::PlayerBase accessor;
    sub_7100926A50(&accessor);
    return accessor.m190() || accessor.m191();
}

bool sub_7100926D24() {
    ksys::act::acc::PlayerBase accessor;
    sub_7100926A50(&accessor);
    if (!accessor.hasProc())
        return false;
    if (accessor.isRidingHorse())
        return true;
    if (accessor.x_15())
        return true;
    if (accessor.x_17())
        return true;
    if (accessor.x_16() && !accessor.x_17())
        return !accessor.x_18();
    return false;
}

bool sub_7100926FD0() {
    return false;
}

void sub_7100927054(sead::Vector2f* stick) {
    stick->set(0, 0);
    auto* controller =
        uking::MaskController::getControllerSafe(uking::MaskController::ControllerIdx::_1);
    if (!controller)
        return;
    sead::Vector2f left_stick = controller->getLeftStick();
    if (ksys::util::sub_71011F0FC8(left_stick))
        return;
    *stick = left_stick;
}

bool sub_71009270A4() {
    sead::Vector2f stick;
    sub_7100927054(&stick);
    if (stick.x == 0.0f && stick.y == 0.0f)
        return false;
    return true;
}


namespace uking::act {

Root6* Root6::getInstance() {
    return Root6::instance();
}

void Root6::sub_7100927198(ksys::act::ActorLinkConstDataAccess* accessor) {
    if (accessor)
        accessor->acquire(mCamera);
}

}  // namespace uking::act

f32 sub_7100927228() {
    return -1.0f;
}

f32 sub_7100927230() {
    return -1.0f;
}

f32 sub_7100927238() {
    s32 value = 2;
    if (auto* gdm = ksys::gdt::Manager::instance())
        gdm->getParam().get().getS32(&value, "StickSensitivity");
    return sub_71009220FC(value);
}

f32 sub_71009272A8() {
    s32 value = 2;
    if (auto* gdm = ksys::gdt::Manager::instance())
        gdm->getParam().get().getS32(&value, "StickSensitivity");
    return sub_71009220FC(value) * sub_7100922120();
}
