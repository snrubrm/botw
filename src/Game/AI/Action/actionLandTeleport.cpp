#include "Game/AI/Action/actionLandTeleport.h"
#include <algorithm>
#include <cmath>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/System/CameraMgr.h"
#include "KingSystem/Utils/MathUtil.h"
#include "math/seadMathCalcCommon.h"
#include "random/seadGlobalRandom.h"

namespace uking::action {

LandTeleport::LandTeleport(const InitArg& arg) : TeleportBase(arg) {}

LandTeleport::~LandTeleport() = default;

bool LandTeleport::init_(sead::Heap* heap) {
    return TeleportBase::init_(heap);
}

void LandTeleport::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsNormalizeAxisY_s) {
        if (auto* controller = mActor->getCharacterController()) {
            sead::Matrix34f mtx;
            const sead::Vector3f front = mActor->getMtx().getBase(2);
            const sead::Vector3f up = -controller->_7c;
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            ksys::util::sub_71011F00EC(&mtx, front, up, pos, false);
            controller->sub_7100F60500(mtx);
        }
    }
    _b0 = mActor->getMtx().getTranslation();
    TeleportBase::enter_(params);
    m40();
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* handler = actor->_868) {
            if (handler->sub_71006ED9EC())
                handler->sub_71006EDCB8();
        }
    }
}

void LandTeleport::leave_() {
    TeleportBase::leave_();
}

void LandTeleport::loadParams_() {
    TeleportBase::loadParams_();
    getStaticParam(&mDistXZ_s, "DistXZ");
    getStaticParam(&mDistY_s, "DistY");
    getStaticParam(&mSearchClosestPointRadius_s, "SearchClosestPointRadius");
    getStaticParam(&mIsNormalizeAxisY_s, "IsNormalizeAxisY");
}

void LandTeleport::calc_() {
    TeleportBase::calc_();
}

sead::Vector3f& LandTeleport::m33() {
    return _98;
}

void LandTeleport::m36() {
    auto* actor = mActor;
    sead::Vector3f fallback = sead::Vector3f::zero;
    auto* nav = actor->m45();
    if (nav && (nav->_2a4 & 0xffff) == 0x17) {
        _98.set(_b0);
        return;
    }
    _98 = sub_71002955BC() + _a4;
    if (m41()) {
        m40();
        _98 = sub_71002955BC() + _a4;
    }
    const sead::Vector3f start = _b0;
    if ((_b0 - _98).length() > 0.1f) {
        const bool found = sub_710072F788(actor, start, _98, &fallback);
        auto* mgr = ksys::map::AutoPlacementMgr::instance();
        if (found) {
            if (!mgr || !mgr->isNonAutoPlacement(_98, true)) {
                _b0.set(_98);
                return;
            }
        } else {
            if (!mgr || !mgr->isNonAutoPlacement(fallback, true)) {
                _98.set(fallback);
                _b0.set(fallback);
                return;
            }
        }
    }
    _98.set(_b0);
}

void LandTeleport::m37() {
    const f32 height = sead::Mathf::max(*mDistY_s + *mDistY_s, 10.0f);
    sead::Vector3f hit_pos;
    const sead::Vector3f from = mActor->getMtx().getTranslation();
    sead::Vector3f hit_normal;
    if (sub_710072E928(from, sead::Vector3f{from.x, from.y - height, from.z}, &hit_pos,
                       &hit_normal, nullptr, 0.2f)) {
        if (*mDistY_s > 0) {
            sead::Vector3f axis;
            f32 angle;
            ksys::util::sub_71011EEB08(&axis, &angle, hit_normal, sead::Vector3f::ey,
                                       sead::Vector3f::ey);
            hit_pos.y += *mDistY_s + std::min(std::tan(angle), 1.0f);
        }
        sub_7100294F68(hit_pos, m34());
    } else {
        TeleportBase::m37();
    }
}

// NON_MATCHING: the original loads the radius parameter pointer separately in both arms (after the
// navmesh character test); ours hoists the load above the test, which also swaps x19 / x20.
bool LandTeleport::m39(const sead::Vector3f& in, sead::Vector3f* out) {
    auto* nav = mActor->m45();
    bool found;
    {
        ksys::phys::Unk_7100f7e9f0 result =
            nav ? nav->sub_7100F76078(out, in, *mSearchClosestPointRadius_s) :
                  ksys::phys::HavokAI::instance()->sub_7100F87ED0(out, in, *mSearchClosestPointRadius_s);
        found = result.sub_7100F7EB40();
    }
    if (!found)
        return false;
    auto* mgr = ksys::map::AutoPlacementMgr::instance();
    if (mgr && mgr->isNonAutoPlacement(*out, true))
        return false;
    _b0.set(*out);
    return true;
}

void LandTeleport::m40() {
    _a4 = sead::Vector3f::zero;
    const f32 angle = s32(sead::GlobalRandom::instance()->getU32(360)) / 360.0f * sead::Mathf::pi2();
    _a4.x = sead::Mathf::cos(angle) * *mDistXZ_s;
    _a4.z = sead::Mathf::sin(angle) * *mDistXZ_s;
    _a4.y = 1.0f;
}

bool LandTeleport::sub_71001CDF68(const sead::Vector3f& pos) {
    if (auto* mgr = ksys::map::AutoPlacementMgr::instance()) {
        if (mgr->isNonAutoPlacement(pos, true))
            return true;
    }
    return false;
}

bool LandTeleport::m41() {
    if (!ksys::sub_7100D8C4F8(_98))
        return true;
    if (auto* mgr = ksys::map::AutoPlacementMgr::instance()) {
        if (mgr->isNonAutoPlacement(_98, true))
            return true;
    }
    return false;
}

}  // namespace uking::action
