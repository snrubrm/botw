#include <basis/seadNew.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/actArmorBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

Unk_71024e8738::Unk_71024e8738() = default;

bool Unk_71024e8738::m5(ksys::act::BaseProc* proc) {
    return false;
}

// NON_MATCHING: instruction scheduling only: the original builds the key of the second `search` call after the
// address of its pair (`mPairs[mNumPairs].mKeyB`), and moves the arguments to callee-saved registers after the frame
// setup
bool Unk_71024e8738::m4(ksys::act::BaseProc* proc) {
    auto* actor = sub_7100D3C5E0(proc);
    if (!actor)
        return false;
    auto* model = actor->getModel();
    if (!model)
        return false;

    auto* child = static_cast<ksys::act::Actor*>(proc);
    auto* child_model = child->getModel();
    child->mMtx = actor->mMtx;
    child->nullsub_4648();
    if (!_40) {
        child->mScale = actor->mScale;
        child_model->setScale(model->getScale());
    }
    child_model->setMatrix(actor->mMtx);

    const s32 num_pairs = mNumPairs;
    for (s32 i = 0; i < num_pairs; ++i) {
        if (!mPairs[i].mKeyA.isValid() || !mPairs[i].mKeyB.isValid()) {
            mState = 1;
            break;
        }
    }

    if (mState == 1) {
        mNumPairs = 0;
        for (s32 i = 0; i < child_model->getUnits().size(); ++i) {
            auto* unit = child_model->getUnits().unsafeAt(i)->mModelUnit;
            for (s32 j = 0; j < unit->getBoneNum(); ++j) {
                const auto key = model->searchBone(unit->getBoneName(j));
                if (key.isValid()) {
                    mPairs[mNumPairs].mKeyA.search(model, key);
                    gsys::BoneAccessKey child_key;
                    child_key.model_unit_index = i;
                    child_key.bone_index = j;
                    mPairs[mNumPairs].mKeyB.search(child_model, child_key);
                    ++mNumPairs;
                }
            }
        }
        mState = 2;
    }

    for (s32 i = 0; i < mNumPairs; ++i) {
        auto* unit = model->getUnits().unsafeAt(mPairs[i].mKeyA.getKey().model_unit_index)->mModelUnit;
        sead::Matrix34f matrix;
        sead::Vector3f scale;
        unit->getBoneLocalMatrix(&matrix, &scale, mPairs[i].mKeyA.getKey().bone_index);
        child_model->setBoneLocalMatrix(mPairs[i].mKeyB.getKey(), matrix, scale);
    }
    return true;
}

void Unk_71024e8738::sub_7100E4DA54(sead::Heap* heap, gsys::Model* model) {
    sub_7100E4DB7C();
    const s32 count = model->getTotalBoneNum();
    if (count > 0) {
        auto* pairs = new (heap, 8, std::nothrow) Pair[count];
        if (pairs)
            mPairs.setBuffer(count, pairs);
    }
    mState = 1;
}

void Unk_71024e8738::sub_7100E4DB7C() {
    if (mState != 0) {
        mPairs.freeBuffer();
        mState = 0;
    }
}

}  // namespace uking::act
