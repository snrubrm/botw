#include "Game/Actor/AI/aiZoraHeroRelicBattleNormal.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

static const sead::SafeString sUnk_7102433600 = "DestinationAnchor";

ZoraHeroRelicBattleNormal::ZoraHeroRelicBattleNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ZoraHeroRelicBattleNormal::~ZoraHeroRelicBattleNormal() = default;

bool ZoraHeroRelicBattleNormal::init_(sead::Heap* heap) {
    _9c = -1;
    sub_710061223C();
    return true;
}

void ZoraHeroRelicBattleNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    _a0 = {std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
           std::numeric_limits<f32>::quiet_NaN()};
    if (ksys::gdt::getFlag_Water_Relic_firstPrinceRide()) {
        _98 = false;
        sub_7100612434();
    } else {
        _98 = true;
        sub_710061288C();
    }
}

void ZoraHeroRelicBattleNormal::calc_() {
    if (_98)
        return;
    sub_7100612434();
}

void ZoraHeroRelicBattleNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ZoraHeroRelicBattleNormal::loadParams_() {
    getStaticParam(&mWarpDistanceXZ_s, "WarpDistanceXZ");
    getStaticParam(&mNearPlayerDistanceXZ_s, "NearPlayerDistanceXZ");
}

void ZoraHeroRelicBattleNormal::sub_710061223C() {
    for (auto& anchor : _38)
        anchor._c = false;

    auto* map_object = mActor->getMapObject();
    if (!map_object)
        return;

    auto* link_data = map_object->getLinkData();
    if (!link_data)
        return;

    if (link_data->mObjects.size() < 1)
        return;

    int count = 0;
    for (auto& object : link_data->mObjects) {
        if (sUnk_7102433600 != object->getUnitConfigName())
            continue;

        auto& anchor = _38[count];
        anchor._c = true;
        const sead::Vector3f pos = object->getTranslate();
        anchor.pos = pos;
        if (++count >= 5)
            return;
    }
}

void ZoraHeroRelicBattleNormal::sub_710061288C() {
    if (auto* controller = mActor->getCharacterController())
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);

    ksys::act::ai::InlineParamPack params;
    params.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("待機", &params);
}

// 0x71006129e8
void ZoraHeroRelicBattleNormal::sub_71006129E8(const sead::Vector3f& pos) {
    if (auto* controller = mActor->getCharacterController())
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("プレイヤ水中", &pack);
}

// 0x7100612ad4
void ZoraHeroRelicBattleNormal::sub_7100612AD4(const sead::Vector3f& pos) {
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("プレイヤ上空", &pack);
}

// 0x7100612bc0
void ZoraHeroRelicBattleNormal::sub_7100612BC0(const sead::Vector3f& pos) {
    if (auto* controller = mActor->getCharacterController())
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("エリア外移動", &pack);
}

// 0x7100612cac
void ZoraHeroRelicBattleNormal::sub_7100612CAC(const sead::Vector3f& pos) {
    if (auto* controller = mActor->getCharacterController())
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("エリア外待機", &pack);
}

// 0x7100612d98
void ZoraHeroRelicBattleNormal::sub_7100612D98(const sead::Vector3f& pos) {
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("水中ワープ", &pack);
}

// NON_MATCHING: only the order of the argument copies at the start (the original moves `pos` after the two floats)
// 0x7100613404
bool ZoraHeroRelicBattleNormal::sub_7100612E84(f32 top, f32 bottom, const sead::Vector3f& pos, bool direct,
                                               sead::Vector3f* out) {
    sead::Vector3f hit;
    if (!sub_7100613404(top, bottom, pos, &hit))
        return false;

    auto* nav = mActor->m45();
    if (!nav) {
        out->set(hit);
        return true;
    }

    sead::Vector3f reach;
    const auto path = nav->sub_7100F76078(&reach, hit, 3.0f);
    const bool found = path.sub_7100F7EB40();
    if (direct) {
        if (found && sub_7100613404(3.0f, -3.0f, reach, &hit)) {
            out->set(hit);
            return true;
        }
        return false;
    }

    if (!found)
        return false;

    if (path.sub_7100F7ED6C(nullptr) > 5.0f) {
        sead::Vector3f next;
        sead::Vector3f start = reach;
        path.sub_7100F7EB60(&next);
        if (sead::Vector2f(next.x - start.x, next.z - start.z).length() > 1.0f) {
            sead::Vector3f dir{next.x - start.x, 0.0f, next.z - start.z};
            dir.normalize();
            start += dir;
            if (sub_7100613404(3.0f, -3.0f, start, &hit)) {
                out->set(hit);
                return true;
            }
        }
    }

    if (_a0.isNan())
        return false;
    out->set(_a0);
    return true;
}

// NON_MATCHING: the original keeps branches per anchor where ours selects (csel / fcsel) and merges conditions
s32 ZoraHeroRelicBattleNormal::sub_71006130C4(f32 max_dist, const sead::Vector3f& pos) {
    const f32 max_dist_sq = max_dist * max_dist;
    s32 best = -1;
    f32 best_dist_sq = -1.0f;
    for (s32 i = 0; i < 5; ++i) {
        const auto& anchor = _38[i];
        if (!anchor._c)
            continue;
        const f32 dx = anchor.pos.x - pos.x;
        const f32 dz = anchor.pos.z - pos.z;
        const f32 dist_sq = dx * dx + dz * dz;
        if (max_dist > 0.0f && dist_sq > max_dist_sq)
            continue;
        if (best < 0 || dist_sq < best_dist_sq) {
            best = i;
            best_dist_sq = dist_sq;
        }
    }
    return best;
}

bool ZoraHeroRelicBattleNormal::sub_7100613404(f32 top, f32 bottom, const sead::Vector3f& pos,
                                               sead::Vector3f* hit_pos) {
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
    const sead::Vector3f start = pos + sead::Vector3f(0, top, 0);
    const sead::Vector3f end = pos + sead::Vector3f(0, bottom, 0);
    query.setStartAndEnd(start, end);
    if (!query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        return false;
    auto* body = query.getHitRigidBody();
    if (!body || body->getContactLayer() != ksys::phys::ContactLayer::EntityWater)
        return false;
    if (hit_pos)
        query.getHitPosition(hit_pos);
    return true;
}

}  // namespace uking::ai
