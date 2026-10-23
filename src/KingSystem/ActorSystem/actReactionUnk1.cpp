#include "KingSystem/ActorSystem/actReaction.h"
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

namespace ksys::act {

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

}  // namespace ksys::act
