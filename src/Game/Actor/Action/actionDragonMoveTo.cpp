#include "Game/Actor/Action/actionDragonMoveTo.h"
#include "Game/Actor/actDragon.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
// TU statics (static initialiser 0x71000f5910); the bone names are what init_ searches.
ksys::util::InitTimeInfo sInitTimeInfo;
ksys::util::InitConstants sInitConstants;
sead::SafeString sBoneNames[18] = {
    "Head",     "Spine_2",  "Spine_4",  "Spine_6",  "Spine_8",  "Spine_10",
    "Spine_12", "Spine_14", "Spine_16", "Spine_18", "Spine_20", "Spine_22",
    "Spine_24", "Spine_26", "Spine_28", "Spine_30", "Spine_32", "Spine_34",
};
}  // namespace

DragonMoveTo::DragonMoveTo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DragonMoveTo::~DragonMoveTo() {
    _f8.freeBuffer();
}

// NON_MATCHING: the bone name table sits 0x158 into the merged TU statics in the original (0x140 bytes of
// other statics before it are not declared here); ours is at 0x18.
bool DragonMoveTo::init_(sead::Heap* heap) {
    if (!mActor->getModel())
        return true;
    _f8.tryAllocBuffer(18, heap);
    for (s32 i = 0; i < 18; ++i)
        _f8[i].search(mActor->getModel(), sBoneNames[i]);
    return true;
}

void DragonMoveTo::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;
    mContacts[0]._24 = false;
    mContacts[0]._20 = -1.0f;
    mContacts[1]._20 = -1.0f;
    mContacts[1]._24 = false;
    mContacts[2]._20 = -1.0f;
    mContacts[2]._24 = false;
    _108 = dragon->sub_710001014C();
    _138 = dragon->sub_710001014C().getBase(1);
    if (mActor->getCharacterController())
        mFlags.set(Flag::Changeable);
}

void DragonMoveTo::leave_() {
    mContacts[0].handle.fadeXLink();
    mContacts[1].handle.fadeXLink();
    mContacts[2].handle.fadeXLink();
}

void DragonMoveTo::loadParams_() {
    getStaticParam(&mRollMax_s, "RollMax");
    getStaticParam(&mRollSpeed_s, "RollSpeed");
    getStaticParam(&mRollMaxSpeed_s, "RollMaxSpeed");
    getStaticParam(&mRollAmount_s, "RollAmount");
    getStaticParam(&mRestoreUp_s, "RestoreUp");
    getStaticParam(&mBackAdjustAngle_s, "BackAdjustAngle");
    getStaticParam(&mBackAdjustRestoreUp_s, "BackAdjustRestoreUp");
    getStaticParam(&mFixAngle_s, "FixAngle");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mFrontDir_d, "FrontDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void DragonMoveTo::calc_() {
    ksys::act::ai::Action::calc_();
}

// NON_MATCHING: stack slots and register allocation (the original reuses the ground height slot for the
// contact position).
bool DragonMoveTo::sub_71000F693C(int index, const sead::Vector3f* pos) {
    f32 water_height = -1.0f;
    bool in_water = false;
    bool on_ground = false;
    f32 ground_height = -1.0f;
    const u32 has_ground = sub_710072C21C(&ground_height, pos);
    const u32 has_water = sub_710072C494(&water_height, pos);
    if (!has_ground || !has_water)
        return false;

    const f32 height = ground_height > water_height ? ground_height : water_height;
    const f32 diff = pos->y - height;
    const bool is_water = water_height > ground_height;
    (is_water ? in_water : on_ground) = diff > (is_water ? -10.0f : 0.0f) && diff < 10.0f;
    if (!in_water && !on_ground)
        return false;

    sead::Vector3f contact_pos = *pos;
    contact_pos.y = height;
    sub_71000F6C18(index, in_water, false, &contact_pos);
    return true;
}

// NON_MATCHING: the original keeps a separate _20 store per branch (ours merges the water ones and keeps
// the constant in d8); register allocation.
void DragonMoveTo::sub_71000F6C18(int index, bool in_water, bool unused, const sead::Vector3f* pos) {
    auto* handle = &mContacts[index].handle;
    if (in_water) {
        if (index != 0) {
            if (!mContacts[index]._24) {
                xlinkSearchAndEmit(mActor, "ContactGround_Water", 2, handle);
                mContacts[index]._24 = true;
            }
            mContacts[index]._20 = 0.0f;
        } else {
            xlinkSearchAndEmit(mActor, "ContactGround_InWater", 2, handle);
            mContacts[index]._20 = 120.0f;
        }
    } else {
        u32 material = -1;
        if (sub_710072C388(&material, pos, 10.0f)) {
            const sead::SafeString name = ksys::tera::Terrain::instance()->sub_710114DE20(material);
            if (name.findIndex("雪") != -1)
                xlinkSearchAndEmit(mActor, "ContactGround_Snow", 0, handle);
            else
                xlinkSearchAndEmit(mActor, "ContactGround_Common", 2, handle);
            mContacts[index]._20 = s32(sead::GlobalRandom::instance()->getU32(30) + 30);
        }
    }
    handle->sub_71012419B4(*pos);
}

}  // namespace uking::action
