#include "Game/Actor/Action/actionZoraHeroRescuePlayer.h"
#include <cmath>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_7102433970.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

void sub_71006F5538(ksys::phys::CharacterController* controller);

namespace uking::action {

static const sead::SafeString sUnk_71023CD668 = "DestinationAnchor";

ZoraHeroRescuePlayer::ZoraHeroRescuePlayer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ZoraHeroRescuePlayer::~ZoraHeroRescuePlayer() = default;

bool ZoraHeroRescuePlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original copies the player matrix with a 0x2c-byte memcpy (we copy three q registers)
// and places it at sp+8.
// Moves the actor (Mipha) to the player when the player is in the water; otherwise warps it to the water
// near the closest linked DestinationAnchor.
bool ZoraHeroRescuePlayer::oneShot_() {
    auto* actor = mActor;
    ksys::act::acc::PlayerBase player;
    if (player.getPlayerFromPlayerInfo()) {
        const sead::Vector3f player_pos = player.getActorMtx().getTranslation();
        sead::Vector3f pos;
        if (player.sub_7100D0FF48() && sub_71002C071C(player_pos, &pos)) {
            sead::Matrix34f mtx;
            if (auto* controller = actor->getCharacterController()) {
                mtx = player.getActorMtx();
                mtx.setTranslation(pos);
                controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
                controller->sub_7100F5F6FC(sead::Vector3f::zero);
                controller->sub_7100F5FB24(sead::Vector3f::zero);
                controller->sub_7100F5E7F0(0.0f);
            }
            ksys::act::sub_7100EE5AF8(actor, mtx);
            if (!actor->getConnectedCalcChild() && !player.hasConnectedCalcParent()) {
                player.setThisActorAsChild(actor, false);
                if (auto** unit = static_cast<Unk_71025afb58**>(mZoraHeroShowMsgUnit_a)) {
                    if (auto* message = sead::DynamicCast<Unk_7102433970>(*unit))
                        message->_8.sub_7100744200(6, true);
                }
            }
        } else {
            sub_71002C09E8(player_pos, &pos);
            sead::Vector3f target;
            if (sub_71002C071C(pos, &target)) {
                target.y += -1.5f;
                if (auto* controller = actor->getCharacterController()) {
                    controller->warpActorToPosition(target);
                    controller->sub_7100F5F6FC(sead::Vector3f::zero);
                    controller->sub_7100F5FB24(sead::Vector3f::zero);
                    controller->sub_7100F5E7F0(0.0f);
                    sub_71006F5538(controller);
                }
            }
        }
    }
    return true;
}

// NON_MATCHING: the original duplicates the navmesh query / validity check in the water branch (tail merge)
// and numbers the dx / dz registers the other way round.
// Finds a water position near `pos`: the water surface hit by a vertical ray (snapped to the navmesh), or
// the closest navmesh point. Moves `out` 0.65 further in the horizontal direction of the navmesh face point.
bool ZoraHeroRescuePlayer::sub_71002C071C(const sead::Vector3f& pos, sead::Vector3f* out) {
    auto* nav = mActor->m45();
    ksys::phys::RayCastBodyQuery query(
        sub_7100738C18(&uking::act::PlayerInfo::getSomeProcLink(), 0), ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityWater);
    query.setGroundHit(ksys::phys::GroundHit::HitAll);
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    query.enableLayer(ksys::phys::ContactLayer::EntityWater);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityHitOnlyGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    {
        const sead::Vector3f start = pos + sead::Vector3f(0, 10.0f, 0);
        const sead::Vector3f end = pos + sead::Vector3f(0, -10.0f, 0);
        query.setStartAndEnd(start, end);
    }

    const bool water = query.worldRayCast(ksys::phys::ContactLayerType::Entity) &&
                       query.getHitRigidBody() &&
                       query.getHitRigidBody()->getContactLayer() ==
                           ksys::phys::ContactLayer::EntityWater;
    sead::Vector3f hit_pos;
    if (water) {
        if (!nav) {
            query.getHitPosition(out);
            return true;
        }
        query.getHitPosition(&hit_pos);
    } else if (!nav) {
        return false;
    }

    ksys::phys::Unk_7100f7e9f0 result = water ? nav->sub_7100F76078(out, hit_pos, 5.0f) :
                                                nav->sub_7100F76078(out, pos, 3.0f);
    if (!result.sub_7100F7EB40() || !(result.sub_7100F7ED6C(nullptr) > 4.0f))
        return false;
    result.sub_7100F7EB60(&hit_pos);

    const f32 dx = hit_pos.x - out->x;
    const f32 dz = hit_pos.z - out->z;
    if (!(std::sqrt(dx * dx + dz * dz) > 0.65f))
        return false;
    sead::Vector3f offset(hit_pos.x - out->x, 0.0f, hit_pos.z - out->z);
    const f32 length = offset.length();
    if (length > 0.0f)
        offset *= 0.65f / length;
    *out += offset;
    return true;
}

// Writes the position of the linked DestinationAnchor closest to `pos` (horizontally) to `out`, or the
// actor's position without one.
void ZoraHeroRescuePlayer::sub_71002C09E8(const sead::Vector3f& pos, sead::Vector3f* out) {
    if (!out)
        return;
    auto* actor = mActor;
    *out = actor->getMtx().getTranslation();

    auto* map_object = actor->getMapObject();
    if (!map_object)
        return;
    auto* link_data = map_object->getLinkData();
    if (!link_data)
        return;
    if (link_data->mObjects.size() < 1)
        return;

    f32 min_distance = -1.0f;
    for (auto& object : link_data->mObjects) {
        if (sUnk_71023CD668 != object->getUnitConfigName())
            continue;
        const sead::Vector3f& translate = object->getTranslate();
        if (min_distance < 0.0f) {
            *out = translate;
            const f32 dx = pos.x - translate.x;
            const f32 dz = pos.z - translate.z;
            min_distance = dx * dx + dz * dz;
        } else {
            const f32 dx = pos.x - translate.x;
            const f32 dz = pos.z - translate.z;
            const f32 distance = dx * dx + dz * dz;
            if (distance < min_distance) {
                min_distance = distance;
                *out = translate;
            }
        }
    }
}

void ZoraHeroRescuePlayer::loadParams_() {
    getAITreeVariable(&mZoraHeroShowMsgUnit_a, "ZoraHeroShowMsgUnit");
}

}  // namespace uking::action
