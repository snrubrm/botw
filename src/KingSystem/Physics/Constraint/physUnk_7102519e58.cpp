#include "KingSystem/Physics/Constraint/physUnk_7102519e58.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

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
