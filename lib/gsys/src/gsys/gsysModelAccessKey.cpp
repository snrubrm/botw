#include "gsys/gsysModelAccessKey.h"
#include <basis/seadRawPrint.h>
#include <prim/seadMemUtil.h>
#include <prim/seadScopedLock.h>
#include "gsys/gsysModel.h"

namespace gsys {

IModelAccesssHandle::IModelAccesssHandle() = default;

IModelAccesssHandle::~IModelAccesssHandle() {
    ;
}

bool IModelAccesssHandle::search(const Model* p_model, const sead::SafeString& name) {
    SEAD_ASSERT(p_model != nullptr);
    SEAD_ASSERT_MSG(!sead::MemUtil::isStack(name.cstr()), "String[%s] is on stack.", name.cstr());

    if (mModel != p_model) {
        remove();
        p_model->add_(this);
        mModel = p_model;
    }

    mName = name;
    return search();
}

void IModelAccesssHandle::remove() {
    if (!mModel)
        return;

    auto lock = sead::makeScopedLock(mModel->getCS());
    if (!mListNode.isLinked())
        return;

    SEAD_ASSERT(mModel != nullptr);
    mModel->remove_(this);
    mModel = nullptr;
    removeImpl_();
}

bool IModelAccesssHandle::search() {
    if (!mListNode.isLinked())
        return false;

    SEAD_ASSERT(mModel != nullptr);
    return searchImpl_();
}

// NON_MATCHING: the original stores the two key halves separately (bone_index first) ahead of the
// vtable stores; ours merges them into one store at the end.
BoneAccessKeyEx::BoneAccessKeyEx() = default;

BoneAccessKeyEx::~BoneAccessKeyEx() {
    remove();
}

void BoneAccessKeyEx::removeImpl_() {
    mKey.reset();
}

// NON_MATCHING: same as BoneAccessKeyEx::BoneAccessKeyEx() (the key halves are stored separately,
// material_index first, ahead of the vtable stores).
MaterialAccessKeyEx::MaterialAccessKeyEx() = default;

MaterialAccessKeyEx::~MaterialAccessKeyEx() {
    remove();
}

bool MaterialAccessKeyEx::searchImpl_() {
    mKey = mModel->searchMaterial(mName);
    return mKey.isValid();
}

void MaterialAccessKeyEx::removeImpl_() {
    mKey.reset();
}

}  // namespace gsys
