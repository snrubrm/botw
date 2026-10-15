#include "Game/Actor/Behavior/behaviorFadeLeaf.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/System/VFR.h"

namespace uking::behavior {

FadeLeaf::FadeLeaf(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

FadeLeaf::~FadeLeaf() = default;

bool FadeLeaf::m6(sead::Heap* heap) {
    for (s32& idx : _38)
        idx = -1;
    return true;
}

void FadeLeaf::m9() {}

void FadeLeaf::loadParams() {
    getStaticParam(&mAlphaLower_s, "AlphaLower");
    getStaticParam(&mAlphaSpeed_s, "AlphaSpeed");
}

void FadeLeaf::m7() {
    sub_7100622AB0();
}

void FadeLeaf::m8() {
    auto* actor = mActor;
    auto* model = actor->getModel();
    ksys::act::sub_7100EE5330(actor, ksys::act::getStr_CameraCheck());
    if (!model || !model->getUnits()(0)->mModelUnit)
        return;
    sead::FixedSafeString<16> name;
    for (s32 i = 0; i < 6; ++i) {
        name.format("Mt_Treeleaf_");
        name.appendWithFormat("%02d", i);
        const auto key = model->searchMaterial(name);
        if (key.isValid())
            _38[i] = key.material_index;
    }
}

void FadeLeaf::sub_7100622AB0() {
    auto* model = mActor->getModel();
    if (!model)
        return;
    auto* unit = model->getUnits()(0)->mModelUnit;
    if (!unit)
        return;
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    const s32 index = physics->findCollisionInfo("Camera");
    if (index < 0)
        return;
    auto* info = physics->getCollisionInfoAt(index);
    if (!info)
        return;
    if (info->getCollidingBodies().size() != 0) {
        if (!(_50 > *mAlphaLower_s))
            return;
        ksys::VFR::chase(&_50, *mAlphaLower_s, *mAlphaSpeed_s);
    } else {
        if (!(_50 < 1.0f))
            return;
        ksys::VFR::chase(&_50, 1.0f, *mAlphaSpeed_s);
    }
    for (s32 i = 0; i < 6; ++i) {
        if (_38[i] >= 0)
            Unk_710260af28::instance()->sub_7100F1DFF0(unit, _38[i], _50, false);
    }
}

}  // namespace uking::behavior
