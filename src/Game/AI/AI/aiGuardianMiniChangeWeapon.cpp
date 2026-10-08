#include "Game/AI/AI/aiGuardianMiniChangeWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

GuardianMiniChangeWeapon::GuardianMiniChangeWeapon(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniChangeWeapon::~GuardianMiniChangeWeapon() {
    if (_a0) {
        delete _a0;
        _a0 = nullptr;
    }
}

bool GuardianMiniChangeWeapon::init_(sead::Heap* heap) {
    _a0 = new (heap) Unk_71023f83e8(mActor, 0x8000021);
    return _a0 != nullptr;
}

// NON_MATCHING: scheduling of the rotation vector math around the payload lock (the original loads the
// vector first and interleaves the multiplications with the lock acquisition).
void GuardianMiniChangeWeapon::sub_710041A6DC() {
    sead::Vector3f dir = sead::Vector3f::ey * static_cast<f32>(*mRotValue_s) * 2.0943952f;
    _a0->_18.set(dir, *mRotSpeed_s);
    _a0->sub_710070DBB0(*mActor->getMessageTransceiver().getId(), true);
    changeChild("武器切替");
    if (auto* as_list = mActor->getASList()) {
        if (as_list->x_1(1, 0) != mDamageASName_s)
            sub_710041AA18();
    }
}

void GuardianMiniChangeWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getDamageMgr();
    setDamageCallbackTiming(mActor, 4, &_78);
    changeChild("切替開始");
}

// NON_MATCHING: the two damage-type cases share a later tail-call block.
void GuardianMiniChangeWeapon::sub_710041A554() {
    if (!mActor)
        return;
    auto* manager = sub_710072BA90(mActor);
    if (!manager)
        return;
    if (manager->_216.isOff(2) || manager->getField54() == 12) {
        if (!mActor)
            return;
        auto* as_list = mActor->getASList();
        if (as_list && as_list->x_4(1, 0) && as_list->x_1(1, 0) == mDamageASName_s)
            sub_710041AA18();
    } else {
        const u32 type = manager->getField50();
        if (type < 3 || (type == 3 && manager->checkDamageFlags(0)))
            sub_710041ABD4();
    }
}

void GuardianMiniChangeWeapon::calc_() {
    sub_710041A554();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("切替開始")) {
            sub_710041A6DC();
            return;
        }
    }

    child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("切替終了"))
            setFinished();
    }
}

bool GuardianMiniChangeWeapon::isChangeable() const {
    return false;
}

void GuardianMiniChangeWeapon::leave_() {
    sub_71005DA114(mActor, &_78);
    if (mActor) {
        if (auto* as_list = mActor->getASList()) {
            as_list->sub_710115C11C();
            as_list->sub_710115BED4(true);
        }
    }
}

void GuardianMiniChangeWeapon::loadParams_() {
    getStaticParam(&mRotValue_s, "RotValue");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mDamageNodeName_s, "DamageNodeName");
    getStaticParam(&mDamageASName_s, "DamageASName");
}

bool GuardianMiniChangeWeapon::isFinished() const {
    return ActionBase::isFinished() ||
           (isCurrentChild("切替終了") && getCurrentChild()->isFinished());
}

void GuardianMiniChangeWeapon::sub_710041AA18() {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;
    as_list->startAnimationMaybe(-1.0f, -1.0f, as_list->x_1(0, 0).cstr(), 1, 0, true);
    as_list->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163298,
                 as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8));
}

void GuardianMiniChangeWeapon::sub_710041AAD4() {
    changeChild("切替終了");
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;
    if (as_list->x_1(1, 0) != mDamageASName_s)
        sub_710041AA18();
}

// NON_MATCHING: the original keeps `dir` stack-resident (int-copy init, float reloads,
// sunk writebacks, checkpoint stores, bigger frame); ours SROA-promotes it to regs.
// Snippet-proven only an escaping use reproduces it, and no call in the real code
// takes dir's address (EEB08 takes rot, which is provably distinct).
void GuardianMiniChangeWeapon::sub_710041ABD4() {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* model = actor->getModel();
    if (!model)
        return;
    auto* as_list = actor->getASList();
    if (!as_list)
        return;
    const auto root_key = model->searchBone(mRootNodeName_s.cstr());
    const auto damage_key = actor->getModel()->searchBone(mDamageNodeName_s.cstr());
    if (!root_key.isValid() || !damage_key.isValid())
        return;
    as_list->sub_710115C9E0(1);
    as_list->mSlots[1].sub_7101165008(root_key, 0, true);
    as_list->mSlots[1].sub_7101165008(damage_key, 3, true);
    as_list->mSlots[1].sub_7101164E38(false);
    as_list->sub_710115C9E0(0);
    as_list->mSlots[0].sub_7101165008(root_key, 3, true);
    as_list->mSlots[0].sub_7101165008(damage_key, 0, true);
    as_list->mSlots[0].sub_7101164E38(false);
    if (auto* damage_mgr = sub_710072BA90(actor)) {
        sead::Vector3f pos;
        if (damage_mgr->getPosition(&pos)) {
            sead::Vector3f dir = pos;
            dir.y = 0.0f;
            dir.x = dir.x - actor->getMtx().m[0][3];
            dir.z = dir.z - actor->getMtx().m[2][3];
            dir.normalize();
            sead::Vector3f rot;
            const sead::Matrix34f& mtx = actor->getMtx();
            rot.x = dir.x * mtx.m[0][0] + dir.y * mtx.m[1][0] + dir.z * mtx.m[2][0];
            rot.y = dir.x * mtx.m[0][1] + dir.y * mtx.m[1][1] + dir.z * mtx.m[2][1];
            rot.z = dir.x * mtx.m[0][2] + dir.y * mtx.m[1][2] + dir.z * mtx.m[2][2];
            sead::Vector3f axis;
            f32 angle;
            ksys::util::sub_71011EEB08(&axis, &angle, rot, sead::Vector3f::ez,
                                       sead::Vector3f::ey);
            as_list->x_6(9, 0, axis.y * angle * 57.295776f);
        }
    }
    as_list->startAnimationMaybe(-1.0f, -1.0f, mDamageASName_s.cstr(), 1, 0, true);
}

bool GuardianMiniChangeWeapon::handleMessage_(const ksys::Message* message) {
    if (_a8.m2(*message) && _a8._34._10) {
        _a8.x();
        sub_710041AAD4();
        return true;
    }
    return false;
}

}  // namespace uking::ai
