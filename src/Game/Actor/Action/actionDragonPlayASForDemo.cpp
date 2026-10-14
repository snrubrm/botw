#include "Game/Actor/Action/actionDragonPlayASForDemo.h"
#include "Game/Actor/actDragon.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

DragonPlayASForDemo::DragonPlayASForDemo(const InitArg& arg) : PlayASForDemo(arg) {}

DragonPlayASForDemo::~DragonPlayASForDemo() = default;

bool DragonPlayASForDemo::init_(sead::Heap* heap) {
    return PlayASForDemo::init_(heap);
}

void DragonPlayASForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForDemo::enter_(params);
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor)) {
        dragon->_14c8._8b8 = 0;
        sub_71000F7020();
    }
}

void DragonPlayASForDemo::leave_() {
    PlayASForDemo::leave_();
    if (auto* dragon = sead::DynamicCast<act::Dragon>(mActor))
        dragon->_14c8._8b8 = 1.0f;
}

void DragonPlayASForDemo::loadParams_() {
    PlayASForDemo::loadParams_();
    getStaticParam(&mPosition_s, "Position");
    getStaticParam(&mRotate_s, "Rotate");
}

void DragonPlayASForDemo::calc_() {
    PlayASForDemo::calc_();
    sub_71000F7020();
}

void DragonPlayASForDemo::sub_71000F7020() {
    auto* dragon = sead::DynamicCast<act::Dragon>(mActor);
    if (!dragon)
        return;
    auto* controller = dragon->getCharacterController();
    if (!controller)
        return;

    sead::Matrix34f mtx = sead::Matrix34f::ident;
    ksys::util::sub_71011EFCA8(&mtx, *mRotate_s);
    sead::Vector3f pos = *mPosition_s;
    if (dragon->_14c8._930 & 0x40) {
        sead::Vector3f offset;
        offset.setRotated(mtx, dragon->_14c8._8bc);
        pos += offset;
    }
    mtx.setTranslation(pos);
    dragon->x(mtx);

    sead::Matrix34f new_mtx = sead::Matrix34f::ident;
    new_mtx.setTranslation(pos);
    if ((mActor->getMtx().getTranslation() - pos).squaredLength() > 900.0f) {
        controller->sub_7100F60500(new_mtx);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    } else {
        controller->sub_7100F5F938(new_mtx);
    }
}

}  // namespace uking::action
