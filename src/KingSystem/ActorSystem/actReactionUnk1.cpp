#include "KingSystem/ActorSystem/actReaction.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace ksys::act {

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

}  // namespace ksys::act
