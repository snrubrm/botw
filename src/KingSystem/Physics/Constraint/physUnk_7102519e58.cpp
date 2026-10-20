#include "KingSystem/Physics/Constraint/physUnk_7102519e58.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

Unk_7102519e58::Unk_7102519e58() : sead::TListNode<Unk_7102519e58*>(this) {}

Unk_7102519e58::~Unk_7102519e58() {
    if (mConstraint) {
        ksys::phys::Constraint::destroy(mConstraint);
        mConstraint = nullptr;
    }
}

void Unk_7102519e58::sub_71012AD478(const sead::Matrix34f& matrix) {
    if ((!mConstraint || !(mConstraint->_50 & 1)) && mBodyB && mBodyA && mConstraint) {
        m5();
        mConstraint->sub_7100F6AAA4(mBodyA, mBodyB);
        mConstraint->sub_7100F69FF0();
    }
    m4(matrix);
}

bool Unk_7102519e58::sub_71012AD3CC(const ksys::phys::Constraint::Param&,
                                   sead::Matrix34f* matrix, const InitArg& arg, sead::Heap*) {
    if (!arg.instance || !arg.body_a)
        return false;
    mBodyA = arg.instance->findRigidBody(arg.body_a);
    if (!mBodyA || !arg.body_b)
        return false;
    mBodyB = arg.instance->findRigidBody(arg.body_b);
    if (!mBodyB)
        return false;
    mLinkIndex = arg.instance->sub_7100FC0698(this, matrix);
    return mLinkIndex >= 0;
}

