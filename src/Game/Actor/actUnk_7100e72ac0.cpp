#include <math/seadMathCalcCommon.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelNW.h>
#include <nn/g3d/SkeletonObj.h>
#include "Game/Actor/actMotorcycleStickControl.h"
#include "Game/Actor/actHorseBoneController.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/System/VFR.h"

namespace uking::act {

// NON_MATCHING: bone-count guards and buffer-allocation predicates use different branch tails.
bool Unk_71024eb5e0::BoneSet::init(gsys::Model* model, const gsys::BoneAccessKey& end,
        const gsys::BoneAccessKey& start, sead::Heap* heap) {
    mModel = model;
    const auto* skeleton = sead::DynamicCast<gsys::ModelNW>(
        model->getUnits()(start.model_unit_index)->mModelUnit)->getSkeletonObj()->GetRes();
    s32 count = 0;
    for (s32 bone = start.bone_index; bone > 0 && bone != end.bone_index;
         bone = skeleton->GetBone(bone)->GetParentIndex())
        ++count;
    if (count > 0)
        mKeys.tryAllocBuffer(count, heap);
    s32 remaining = count;
    for (s32 bone = start.bone_index; bone > 0 && bone != end.bone_index;
         bone = skeleton->GetBone(bone)->GetParentIndex()) {
        auto& key = mKeys[--remaining];
        key.model_unit_index = start.model_unit_index;
        key.bone_index = bone;
    }
    if (count > 0)
        mMatrices.tryAllocBuffer(count, heap);
    return true;
}

// NON_MATCHING: member initialization groups zeroing around the buffer constructors differently.
Unk_71024eb5e0* Unk_71024eb5e0::make(const InitArg& arg, sead::Heap* heap, f32 scale) {
    auto* holder = new (heap) Unk_71024eb5e0;
    holder->init(arg, heap, scale);
    return holder;
}

// NON_MATCHING: stack placement and inlined chain-argument/vector initialization differ.
bool Unk_71024eb5e0::init(const InitArg& arg, sead::Heap* heap, f32 scale) {
    mModel = arg.model;
    _1f8 = arg._8;
    _1fc = arg._c;
    _200 = arg._10;
    _1f0 = 0x400;
    for (s32 i = 0; i < 4; ++i) {
        _28[i] = 0;
        _38[i] = 0;
        _178[i].set(0, 0, 0);
        _1a8[i] = sead::Vector3f::ey;
        ksys::phys::Unk_71024f67c8::InitArg chain{};
        chain.model = arg.model;
        chain._3c = sead::Mathf::pi();
        chain._44 = -sead::Mathf::pi();
        chain._48 = sead::Mathf::pi();
        chain._4c = sead::Vector3f::ey;
        chain._58 = sead::Vector3f::ey;
        chain._8 = sead::Vector3f::zero;
        gsys::BoneAccessKey toe;
        f32 side;
        f32 weight = 0.54f;
        switch (i) {
        case 0:
            chain.bone_20 = "Arm_1_L";
            chain.bone_58 = "Arm_2_L";
            chain.bone_90 = "Wrist_L";
            chain._8.set(0, 0, -1);
            chain._38 = 1.65f;
            chain._3c = 2.88f;
            toe = arg.model->searchBone("Toe_2_FL");
            weight = 0.5f;
            side = -1;
            break;
        case 1:
            chain.bone_20 = "Arm_1_R";
            chain.bone_58 = "Arm_2_R";
            chain.bone_90 = "Wrist_R";
            chain._8.set(0, 0, -1);
            chain._38 = 1.65f;
            chain._3c = 2.88f;
            toe = arg.model->searchBone("Toe_2_FR");
            weight = 0.5f;
            side = 1;
            break;
        case 2:
            chain.bone_20 = "Leg_1_L";
            chain.bone_58 = "Leg_2_L";
            chain.bone_90 = "Ankle_L";
            chain._8.set(0, 0, 1);
            chain._38 = 1.4f;
            chain._3c = 2.26f;
            toe = arg.model->searchBone("Toe_2_BL");
            side = -1;
            break;
        case 3:
            chain.bone_20 = "Leg_1_R";
            chain.bone_58 = "Leg_2_R";
            chain.bone_90 = "Ankle_R";
            chain._8.set(0, 0, 1);
            chain._38 = 1.4f;
            chain._3c = 2.26f;
            toe = arg.model->searchBone("Toe_2_BR");
            side = 1;
            break;
        default:
            return false;
        }
        _48[i].set(side, 0, 0);
        _78[i] = weight;
        _88[i] = sead::Mathf::pi() / 4;
        _98[i] = -sead::Mathf::pi() / 4;
        _a8[i].set(0, scale * -0.15f, 0);
        mChains[i] = ksys::phys::Unk_71024f67c8::sub_7100F73640(chain, heap);
        mBoneSets[i].init(arg.model, mChains[i]->_90.getKey(), toe, heap);
        _1d8[i] = 0;
    }
    _1f0 |= 0x20;
    return true;
}

// The semicolon preserves the original vtable store, as in GameDataFlagSelector's destructor
// (upstream commit 96101229).
Unk_71024eb5e0::~Unk_71024eb5e0() { ; }

void Unk_71024eb5e0::destroy() {
    for (auto* chain : mChains) {
        if (chain)
            chain->sub_7100F73B7C();
    }
    delete this;
}

f32 Unk_7100e72ac0::motorcycleStickControlStuff(f32 target) {
    const f32 eps = sead::Mathf::epsilon();
    const f32 cur = _8;
    const f32 rate = (target < -eps ? cur < target : target < eps || cur > target) ? _0 : _4;
    _8 = sead::Mathf::clamp(target, cur - rate * ksys::VFR::instance()->getDeltaFrame(),
                            _8 + rate * ksys::VFR::instance()->getDeltaFrame());
    return _8;
}

}  // namespace uking::act
