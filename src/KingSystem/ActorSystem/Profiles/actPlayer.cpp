#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include <basis/seadNew.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/gameUnk_71024739d0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace ksys::act {

BaseProc* Player::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Player(arg);
}

// NON_MATCHING: members are not declared yet
Player::~Player() = default;

bool Player::sub_710087F168(const sead::Vector3f& start, const sead::Vector3f& end,
                            phys::WallCode wall, sead::Vector3f* hit_pos,
                            sead::Vector3f* hit_normal) {
    uking::Unk_71024739d0 ray(phys::GroundHit::HitAll);
    ray.sub_710090D73C();
    ray.setStart(start);
    ray.setEnd(end);
    ray.worldRayCast();
    if (!ray.hasHit())
        return false;

    const auto& mask = ray.mQuery.getMaterialMask();
    if (wall == phys::WallCode::NoClimb) {
        if (int(mask.getWallCode()) == phys::WallCode::NoClimb ||
            int(mask.getWallCode()) == phys::WallCode::NoDashUpAndNoClimb) {
            return false;
        }
    } else if (wall == phys::WallCode::NoDashUpAndNoClimb) {
        if (int(mask.getWallCode()) == phys::WallCode::NoDashUpAndNoClimb)
            return false;
    } else if (int(mask.getWallCode()) != int(wall)) {
        return false;
    }

    if (hit_pos)
        ray.getHitPosition(hit_pos);
    if (hit_normal)
        ray.getHitNormal(hit_normal);
    return true;
}

bool Player::isSurfingOnGround() const {
    return _cfc.isOnBit(0);
}

bool Player::sub_710087F360(const sead::Vector3f& start, const sead::Vector3f& end,
                            sead::Vector3f* hit_pos, sead::Vector3f* hit_normal) {
    return sub_710072E928(start, end, hit_pos, hit_normal, nullptr, 0.0f);
}

bool Player::sub_710087F43C(const sead::Vector3f& start, const sead::Vector3f& end,
                            sead::Vector3f* hit_pos, sead::Vector3f* hit_normal) {
    uking::Unk_71024739d0 ray(phys::GroundHit::HitAll);
    ray.sub_710090D73C();
    ray.sub_710090D784();
    ray.setStart(start);
    ray.setEnd(end);
    ray.worldRayCast();
    if (!ray.hasHit())
        return false;

    if (hit_pos)
        ray.getHitPosition(hit_pos);
    if (hit_normal)
        ray.getHitNormal(hit_normal);
    return true;
}

bool Player::sub_710087F4F8(const sead::Vector3f& start, const sead::Vector3f& end,
                            sead::Vector3f* hit_pos, sead::Vector3f* hit_normal) {
    uking::Unk_71024739d0 ray(phys::GroundHit::HitAll);
    ray.sub_710090D784();
    ray.setStart(start);
    ray.setEnd(end);
    ray.worldRayCast();
    if (!ray.hasHit())
        return false;

    const auto& mask = ray.mQuery.getMaterialMask();
    if (int(mask.getMaterial()) != phys::Material::Water)
        return false;
    const sead::SafeString sub_material = mask.getSubMaterialName();
    if (sub_material == "Water_Ice" || sub_material == "Water_Poison")
        return false;

    if (hit_pos)
        ray.getHitPosition(hit_pos);
    if (hit_normal)
        ray.getHitNormal(hit_normal);
    return true;
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: operand order of the XZ length addition (z*z + x*x in the original)
Player::Unk1 Player::x_5() {
    sead::Vector3f dir;
    _1b18.getBase(dir, 2);
    dir.normalize();
    if (sead::Vector2f(dir.x, dir.z).length() == 0.0f) {
        _1b18.getBase(dir, 1);
        dir.normalize();
    }
    return Unk1(sead::Mathf::atan2Idx(dir.x, dir.z));
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: x_5() gets inlined here (it is defined in this file; the original calls it), and the
// original selects the stored speed with an integer csel
void Player::sub_7100877BD8() {
    const sead::Vector3f& translation = getASList()->sub_710115D2D4();
    f32 speed = translation.length();
    if (speed < 0.001f)
        speed = 0.0f;
    f32 value = speed;
    if (_cf4.isOnBit(27))
        value = 0.0f;
    _20bc.value = value;
    _20bc.prev_value = value;
    if (speed == 0.0f)
        return;
    const u32 angle = sead::Mathf::atan2Idx(translation.x, translation.z);
    _1c68 = (x_5().value + angle) & util::sUnk_7101EC6BA0;
}

void Player::sub_71008697E4() {
    _20bc.value = 0;
    _20bc.prev_value = 0;
    if (auto* controller = getCharacterController())
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
}

s32 Player::playerWeapons_return0() {
    return 0;
}

s32 Player::playerWeapons_return1() {
    return 1;
}

s32 Player::playerWeapons_return2() {
    return 2;
}

bool playerIsReloadingBow(Player* player) {
    return player->getASList()->x_1(1, 1) == "BowReload" ||
           player->getASList()->x_1(1, 1) == "SquatBowReload" ||
           player->getASList()->x_1(0, 0) == "WallBowReloadL" ||
           player->getASList()->x_1(0, 0) == "WallBowReloadR";
}

bool playerIsChargingBow(Player* player) {
    return player->getASList()->x_1(1, 1) == "BowCharge" ||
           player->getASList()->x_1(1, 1) == "SquatBowCharge" ||
           player->getASList()->x_1(0, 0) == "WallBowChargeL" ||
           player->getASList()->x_1(0, 0) == "WallBowChargeR";
}

bool playerIsReloadingOrChargingOrShootingBow(Player* player) {
    return playerIsReloadingBow(player) || playerIsChargingBow(player) || player->isShootingBow();
}

// NON_MATCHING: load order / register allocation of the velocity components
void Player::sub_7100892100(const sead::Vector3f& pos) {
    auto* controller = getCharacterController();
    if (!controller)
        return;
    const f32 factor = 1.0f / _20f0;
    const sead::Vector3f velocity = (pos - _1770) * 30.0f * factor;
    controller->sub_7100F5F6FC(velocity);
    controller->sub_7100F5FC8C(_1b18);
}

}  // namespace ksys::act
