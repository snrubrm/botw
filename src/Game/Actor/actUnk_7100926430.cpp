#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include <algorithm>
#include <cmath>
#include "Game/gameUnk_71024739d0.h"
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

bool sub_7100927110() {
    auto* root = uking::act::Root6::getInstance();
    if (!root)
        return false;
    ksys::act::acc::Camera accessor;
    root->sub_7100927198(&accessor);
    if (!accessor.hasProc())
        return false;
    return accessor.sub_7100799F60();
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

bool sub_71009271B0() {
    auto* root = uking::act::Root6::getInstance();
    if (!root)
        return false;
    ksys::act::acc::Camera accessor;
    root->sub_7100927198(&accessor);
    if (!accessor.hasProc())
        return false;
    return accessor.sub_710079A05C();
}

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

// NON_MATCHING: one fadd has swapped operands (dir.y * 2 + start.y, where start.y was just set)
f32 sub_710092738C(const sead::Vector3f& pos, const sead::Vector3f& target) {
    uking::Unk_71024739d0 ray(ksys::phys::GroundHit::HitAll);
    ray.sub_710090D73C();

    sead::Vector3f start = pos;
    ray.setStart(start);
    sead::Vector3f end;
    end.x = start.x;
    end.z = start.z;
    end.y = start.y + 10.0f;
    ray.setEnd(end);
    f32 top;
    if (ray.worldRayCast()) {
        ray.getHitPosition(&end);
        top = end.y;
    } else {
        top = start.y + 10.0f;
    }

    ray.mQuery.resetCastResult();
    ray.setStart(start);
    end.x = start.x;
    end.z = start.z;
    end.y = start.y - 10.0f;
    ray.setEnd(end);
    f32 bottom;
    if (ray.worldRayCast()) {
        ray.getHitPosition(&end);
        bottom = end.y;
    } else {
        bottom = start.y - 10.0f;
    }

    f32 result;
    if (top - bottom < 4.0f) {
        result = 0.0f;
    } else {
        sead::Vector3f dir = {pos.x - target.x, 0.0f, pos.z - target.z};
        dir.normalize();
        start.y = bottom;

        end = start + dir * 2.0f;
        end.y += 1.0f;
        ray.mQuery.resetCastResult();
        ray.setStart(pos);
        ray.setEnd(end);
        if (ray.worldRayCast()) {
            sead::Vector3f hit_pos;
            sead::Vector3f hit_normal;
            ray.getHitPosition(&hit_pos);
            ray.getHitNormal(&hit_normal);
            hit_normal.normalize();
            end = hit_pos + hit_normal * 0.3f;
        }
        ray.mQuery.resetCastResult();
        ray.setStart(end);
        ray.setEnd(sead::Vector3f(end.x, end.y - 10.0f, end.z));
        f32 near_y;
        if (ray.worldRayCast()) {
            sead::Vector3f hit_pos;
            ray.getHitPosition(&hit_pos);
            near_y = hit_pos.y;
        } else {
            near_y = start.y;
        }
        end.y = near_y;
        const sead::Vector3f near_diff = end - start;
        const f32 near_angle = sead::Mathf::rad2deg(std::atan2(
            near_diff.y, std::sqrt(near_diff.x * near_diff.x + near_diff.z * near_diff.z)));
        const f32 a = near_angle * (near_angle >= 0.0f ? 0.2f : 0.6f);

        sead::Vector3f mid = dir * 10.0f + start;
        mid.y += 8.0f;
        ray.mQuery.resetCastResult();
        ray.setStart(pos);
        ray.setEnd(mid);
        if (ray.worldRayCast()) {
            sead::Vector3f hit_pos;
            sead::Vector3f hit_normal;
            ray.getHitPosition(&hit_pos);
            ray.getHitNormal(&hit_normal);
            hit_normal.normalize();
            mid = hit_pos + hit_normal * 0.3f;
        }
        ray.mQuery.resetCastResult();
        ray.setStart(mid);
        ray.setEnd(sead::Vector3f(mid.x, mid.y - 10.0f, mid.z));
        f32 mid_y;
        if (ray.worldRayCast()) {
            sead::Vector3f hit_pos;
            ray.getHitPosition(&hit_pos);
            mid_y = hit_pos.y;
        } else {
            mid_y = start.y;
        }

        sead::Vector3f far = dir * 9.1f + start;
        far.y += 8.0f;
        ray.mQuery.resetCastResult();
        ray.setStart(pos);
        ray.setEnd(far);
        if (ray.worldRayCast()) {
            sead::Vector3f hit_pos;
            sead::Vector3f hit_normal;
            ray.getHitPosition(&hit_pos);
            ray.getHitNormal(&hit_normal);
            hit_normal.normalize();
            far = hit_pos + hit_normal * 0.3f;
        }
        ray.mQuery.resetCastResult();
        ray.setStart(far);
        ray.setEnd(sead::Vector3f(far.x, far.y - 10.0f, far.z));
        f32 far_y;
        if (ray.worldRayCast()) {
            sead::Vector3f hit_pos;
            ray.getHitPosition(&hit_pos);
            far_y = hit_pos.y;
        } else {
            far_y = start.y;
        }

        mid.y = (mid_y + far_y) * 0.5f;
        const sead::Vector3f far_diff = mid - start;
        f32 b = sead::Mathf::rad2deg(
            std::atan2(far_diff.y, std::sqrt(far_diff.x * far_diff.x + far_diff.z * far_diff.z)));
        b *= b >= 0.0f ? 0.45f : 0.25f;

        if (a > 0.0f && b > 0.0f)
            result = b <= a ? a : b;
        else if (a <= 0.0f && b <= 0.0f)
            result = a <= b ? a : b;
        else
            result = a * 0.75f + b * 0.25f;
        result = -result;
    }
    return result;
}

const sead::Vector3f& sub_7100928868(const sead::Vector3f& vec) {
    return vec;
}
