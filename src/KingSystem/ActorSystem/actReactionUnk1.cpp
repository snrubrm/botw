#include "KingSystem/ActorSystem/actReaction.h"
#include <basis/seadNew.h>
#include <prim/seadSafeString.h>
#include <xlink2/xlink2Locator.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actReactionSLinkLimiter.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace ksys::eft {
xlink2::UserInstanceSLink* sub_710105DE68(const char* name, act::Actor* actor, act::Actor* other,
                                          xlink2::Locator* locator);
}

// Original enum ownership and source namespace are unknown; declaration only.
const char* sub_7100E367C0(s32 index);

namespace ksys::act {

namespace {
// 0x71024efe80: the extra labels the reaction XLinks are given by Unk1::init.
const char* const sReactionLabels[] = {
    "Default",        "PlayerHit",     "EnemyHit",       "Guard",     "PlayerGuardJust",
    "EnemyGuardJust", "ArrowHit",      "ArrowDamage",    "HorseStep", "HorseWildStep",
    "Woodcutter",     "Land",          "PlayerFootStep", "TreeSplit", "OreHit",
};
}  // namespace

Reaction::Unk1::Unk1() = default;

void Reaction::Unk1::init(sead::Heap* heap) {
    setExtraLabels(_8, sReactionLabels, 15);
    setExtraLabels(_10, sReactionLabels, 15);
    mSLinkLimiter = new (heap, 8) Unk_71024f02a8();
    mSLinkLimiter->init(heap);
    mReactions.init(heap, "GrassTrackLoop");
}

void Reaction::Unk1::sub_7100EC30C4() {
    if (mSLinkLimiter)
        mSLinkLimiter->calc();
    mReactions.calc();
    _108 = 0;
    _10c = 0;
    if (_110 > 0)
        --_110;
    if (_114 > 0)
        --_114;
    if (_118 > 0)
        --_118;
    if (_103)
        --_103;
    _104 = 0;
}

bool Reaction::Unk1::sub_7100EC6DD0(Actor* actor) {
    auto& reactions = mReactions;
    const sead::CoreId core = sead::CoreInfo::getCurrentCoreId();
    return reactions.queue(actor, core);
}

void Reaction::Unk1::sub_7100EC6E30(DamageReactionRequest* request) {
    {
        xlink2::HandleSLink obj_hit_handle;
        sub_7100EC539C(request, &obj_hit_handle, "ObjHit");
    }

    if ((request->_c4 & 1) || ((request->_94 & ~1) == 10))
        return;

    if (StageInfo::sIsFinalTrial && request->_b8) {
        if (request->_b8->getName() == "Priest_Boss_IronBall" &&
            request->mSource.getName() == "PriestBossThunder")
            return;
    }

    xlink2::HandleSLink handle;
    const s32 kind = request->_94;
    sead::FixedSafeString<32> name;
    name.appendWithFormat("Obj%s", kind != 3 ? "Damage" : "Hit");

    const s32 material = int(request->_60.getMaterial());
    switch (material) {
    case phys::Material::Metal:
    case phys::Material::Wood:
    case phys::Material::Bone:
        name.appendWithFormat("_%s", phys::Material::text(material));
        break;
    default:
        name.append("_Metal");
        break;
    }

    if (kind != 3) {
        if (_104 & 2)
            return;
        Actor* actor = request->_b8;
        if (!actor)
            return;
        auto* xlink = actor->getXLink();
        if (!xlink)
            return;
        auto* user = xlink->_50;
        if (!user)
            return;
        const s32 material_78 = int(request->_78.getMaterial());
        const s32 sub_material_idx = request->_78.getSubMaterialIdx();
        const s32 sub_material = xlink::Manager::instance()->getSubMaterialIndex(
            material_78, sub_material_idx);
        user->setPropertyValue(0, material_78);
        user->setPropertyValue(1, sub_material);
        handle = user->searchAndEmit(name.cstr());
        eft::sub_710105E060(&handle, request->mtx);
        _104 |= 2;
    } else {
        if (_104 & 1)
            return;
        sub_7100EC447C(_10, request, &handle, name.cstr());
        _104 |= 1;
    }
}

// NON_MATCHING: same body and instruction order; clang if-converts the water/depth test as branches
// instead of cset+orr, folds the 9/8 list-type select to cinc, and keeps the WaterTrack literal in
// x24 for the fallback comparison (the target derives the fallback from the control flow).
void Reaction::Unk1::sub_7100EC6708(Actor* actor, DamageReactionRequest* request) {
    if (!actor)
        return;

    bool grudge = false;
    if (auto* xlink = actor->getXLink()) {
        if (auto* user = xlink->_50)
            grudge = user->getPropertyValue(0).valueInt == int(phys::Material::GrudgeSlow);
    }

    const bool is_player = isPlayerProfile(actor);

    f32 chemical_value = 0.0f;
    if (is_player) {
        if (auto* chemical = actor->sub_71011D8A44(0)) {
            if (!(chemical->_c & 0x1000000))
                chemical_value = chemical->_190;
        }
    }

    f32 property_value = 0.0f;
    if (auto* xlink = actor->getXLink()) {
        if (auto* user = xlink->_50) {
            const auto* values = user->getPropertyValues();
            if (values)
                property_value = values[7].valueFloat;
        }
    }

    if (property_value > chemical_value)
        chemical_value = property_value;

    if (!(grudge || actor->get68f() || 0.4f <= chemical_value))
        return;

    xlink2::Locator locator;
    const char* name = "WaterTrack";
    if (grudge) {
        name = "WaterTrackGrudge";
    } else if (actor->get68f()) {
        const int material = actor->get6fc();
        if (material == int(phys::Material::GrudgeSlow))
            name = "WaterTrackGrudge";
        else if (material == int(phys::Material::Bog))
            name = "WaterTrackBog";
        else if (material == int(phys::Material::Lava))
            name = "WaterTrackLava";
    }

    auto* user = eft::sub_710105DE68(name, actor, _8, &locator);
    if (!user && name != "WaterTrack")
        user = eft::sub_710105DE68("WaterTrack", actor, _8, &locator);
    if (!user)
        return;

    sead::Vector3f position;
    request->mtx.getTranslation(position);

    const s32 list_type = is_player ? 9 : 8;

    if (mSLinkLimiter) {
        if (!mSLinkLimiter->sub_7100EC9D84(list_type, position, false))
            return;
    }

    xlink2::HandleSLink handle;
    user->emit(locator, &handle);
    if (!handle.isActive())
        return;

    handle.setPosition(position);
    eft::sub_710105E114(&handle, actor);
    if (mSLinkLimiter)
        mSLinkLimiter->sub_7100ECA2A0(list_type, position, handle);
}

// 0x7100ec313c (placeholder name): dispatches a reaction request to the handler of its damage kind.
// NON_MATCHING: four load placements differ (cases 8 and 10 hoist `_8` / `_10` into a callee-saved
// register before the calls in the original). `Actor* actor = _8;` / `= _10;` at the top of those
// two cases reproduces them and makes the row match, but a local used once only to steer a load is
// borderline, so it is not applied.
void Reaction::Unk1::sub_7100EC313C(DamageReactionRequest* request) {
    xlink2::HandleSLink handle;

    if (StageInfo::sIsFinalTrial && request->_98 == 3) {
        if (Actor* actor = request->_b8) {
            if (actor->getName() == "Priest_Boss_ShadowClone")
                return;
        }
    }

    if (request->_c4 & 0x40) {
        if (request->_98 == 3)
            sub_7100EC447C(_10, request, &handle, "ObjHit_Metal");
        else
            sub_7100EC447C(_10, request, &handle, "EnemyHit_S");
        return;
    }

    switch (request->_90) {
    case 0: {
        const s32 material = int(request->_60.getMaterial());
        const s32 sub_material = request->_60.getSubMaterialIdx();
        auto* manager = xlink::Manager::instance();
        if (manager->getSubMaterialIndex(material, sub_material) !=
            manager->getHolyWallSubMaterialIndex())
            return;
        if (_103)
            return;
        sub_7100EC447C(_10, request, &handle, "HolyWallHit");
        _103 = 5;
        return;
    }
    case 1:
        sub_7100EC4594(request);
        return;
    case 2:
        if (request->_98 != 5)
            sub_7100EC4594(request);
        return;
    case 3:
        sub_7100EC4880(request);
        return;
    case 4:
        sub_7100EC4C00(&handle, request);
        return;
    case 5: {
        xlink2::HandleSLink obj_hit_handle;
        if (request->_b8) {
            if (auto* xlink = request->_b8->getXLink()) {
                if (auto* user = xlink->_50) {
                    user->searchAndEmit(sub_7100E367C0(5), &obj_hit_handle);
                    if (obj_hit_handle.isActive())
                        return;
                }
            }
        }
        sub_7100EC447C(_10, request, &obj_hit_handle, sub_7100E367C0(request->_90));
        return;
    }
    case 6:
        if (_114)
            return;
        sub_7100EC447C(_10, request, &handle, sub_7100E367C0(6));
        _114 = 2;
        return;
    case 7:
        if (request->_98 != 1)
            return;
        sub_7100EC447C(_10, request, &handle, sub_7100E367C0(7));
        return;
    case 8: {
        xlink2::HandleSLink ground_handle;
        if (request->mSource.mActor || request->mSource.mLink) {
            sub_7100EC539C(request, &ground_handle, "ReactionEnemyHitGround");
            if (ground_handle.isActive())
                return;
        }
        sub_7100EC447C(_8, request, &ground_handle, "ReactionEnemyHitGround");
        return;
    }
    case 9:
        sub_7100EC513C(request);
        return;
    case 10: {
        const char* name = sub_7100E367C0(10);
        xlink2::HandleSLink ground_handle;
        if (request->mSource.mActor || request->mSource.mLink) {
            sub_7100EC539C(request, &ground_handle, name);
            if (ground_handle.isActive())
                return;
        }
        sub_7100EC447C(_10, request, &ground_handle, name);
        return;
    }
    case 12:
    case 13:
    case 17:
    case 22:
    case 23: {
        if (!_8)
            return;
        auto* xlink = _8->getXLink();
        if (!xlink || !xlink->_50)
            return;
        sub_7100EC6708(request->_b8, request);
        return;
    }
    case 15: {
        if (_102)
            return;
        if (_18) {
            if (auto* xlink = _18->getXLink()) {
                if (auto* user = xlink->_50)
                    user->setPropertyValue(0xe, request->_a0);
            }
        }
        if (_8) {
            if (auto* xlink = _8->getXLink()) {
                if (xlink->_50)
                    sub_7100EC6708(request->_b8, request);
            }
        }
        if (mIsPlayerBarefoot)
            sub_7100EC447C(_18, request, &handle, "PlayerFootStepNaked");
        else
            sub_7100EC447C(_18, request, &handle, sub_7100E367C0(request->_90));
        return;
    }
    case 19: {
        if (_102)
            return;
        if (_18) {
            if (auto* xlink = _18->getXLink()) {
                if (auto* user = xlink->_50)
                    user->setPropertyValue(0xe, request->_a0);
            }
        }
        if (mIsPlayerBarefoot) {
            sead::FixedSafeString<64> name("PlayerLandNaked");
            if (request->_54 > 100.0f)
                name.append("_Large");
            else if (request->_54 > 10.0f)
                name.append("_Normal");
            else
                name.append("_Small");
            if (request->_94 == 0x18)
                name.append("First");
            else
                name.append("Following");
            sub_7100EC447C(_18, request, &handle, name.cstr());
            sub_7100EC5294(request->_b8, request);
            return;
        }
        if (request->_94 == 0x18) {
            if (request->_54 > 100.0f)
                sub_7100EC447C(_18, request, &handle, "FirstLand_Large");
            else if (request->_54 > 10.0f)
                sub_7100EC447C(_18, request, &handle, "FirstLand_Normal");
            else
                sub_7100EC447C(_18, request, &handle, "FirstLand_Small");
        }
        sub_7100EC5294(request->_b8, request);
        return;
    }
    case 20: {
        if (_18) {
            if (auto* xlink = _18->getXLink()) {
                if (auto* user = xlink->_50)
                    user->setPropertyValue(0xe, request->_a0);
            }
        }
        if (mIsPlayerBarefoot)
            sub_7100EC447C(_18, request, &handle, "PlayerLadderStepNaked");
        else
            sub_7100EC447C(_18, request, &handle, "PlayerLadderStep");
        return;
    }
    case 24: {
        sead::FixedSafeString<64> name("PlayerClimb");
        switch (request->_c0) {
        case 1:
            name.append("Weak");
            break;
        case 2:
            name.append("Strong");
            break;
        case 3:
            name.append("Hard");
            break;
        }
        switch (request->_94) {
        case 0xe:
            name.append("FootL");
            break;
        case 0xf:
            name.append("FootR");
            break;
        case 0x1a:
            name.append("HandL");
            break;
        case 0x1b:
            name.append("HandR");
            break;
        }
        sub_7100EC539C(request, &handle, name.cstr());
        return;
    }
    case 27:
    case 28:
        sub_7100EC545C(&handle, request);
        return;
    }
}

// 0x7100ec4c00 (placeholder name): the guard reaction. Emits "Guarded" and the chemical
// hit-additional event for the request source, then "Guard_<material>" for the guarded actor.
void Reaction::Unk1::sub_7100EC4C00(xlink2::HandleSLink* handle, DamageReactionRequest* request) {
    if (request->mSource.mActor || request->mSource.mLink) {
        if (auto* xlink = request->mSource.getXLink()) {
            if (auto* user = xlink->_50) {
                user->searchAndEmit("Guarded", handle);
                xlink2::Locator locator;
                if (user->searchAsset(&locator, "HitAdditional_ChemicalToActor")) {
                    user->setPropertyValue(0x19, 3);
                    user->emit(locator);
                }
            }
        }
        if (handle->isActive())
            return;
    }

    if (!request->_b8)
        return;

    sead::FixedSafeString<19> name("Guard_");
    sead::FixedSafeString<7> material;
    if (request->_60.getMaterial() == phys::Material::Wood)
        material = "Wood";
    else if (request->_60.getMaterial() == phys::Material::Bone)
        material = "Bone";
    else if (request->_60.getMaterial() == phys::Material::Metal)
        material = "Metal";
    else {
        auto* xlink = request->_b8->getXLink();
        if (!xlink || !xlink->_50)
            return;
        xlink->_50->searchAndEmit("Guard", handle);
        return;
    }

    name.append(material);

    auto* xlink = request->_b8->getXLink();
    if (!xlink || !xlink->_50)
        return;
    xlink->_50->searchAndEmit(name.cstr(), handle);
}

}  // namespace ksys::act
