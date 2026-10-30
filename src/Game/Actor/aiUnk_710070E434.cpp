#include "Game/Actor/aiUnk_710070E434.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"

void Unk_710070e434::sub_710070E434(const sead::SafeString& name) {
    if (name.isEmpty()) {
        _c = false;
        _70.setName(name);
        return;
    }
    _c = true;
    _70.setName(name);
    _70._68 = sead::Matrix34f::ident;
    mActor->boneHandleStuff(&_70, false);
}

void Unk_710070e434::sub_710070E4C0() {
    mActor->sub_71011DA868(&_70);
    _c = false;
}

// NON_MATCHING: matrix/vector copies and multiply loads are paired and scheduled differently.
void Unk_710070e434::sub_710070E4EC(const sead::SafeString& name) {
    _8 = mActor->getAngVelocity().length();
    if (!name.isEmpty()) {
        auto* model = mActor->getModel();
        const auto key = model->searchBone(name);
        if (key.isValid()) {
            sead::Matrix34f bone_mtx;
            model->getBoneWorldMatrix(key, &bone_mtx);
            _10 = bone_mtx.getTranslation();
            sead::Matrix34f inverse;
            inverse.setInverse(mActor->getMtx());
            _40.setMul(inverse, _10);
            _1c = sead::Matrix33f(bone_mtx);
            return;
        }
    }
    _40 = sead::Vector3f::zero;
    _10 = mActor->getMtx().getTranslation();
    _1c.makeIdentity();
}

void Unk_710070e434::sub_710070E714() {
    _10.setMul(mActor->getMtx(), _40);
}
