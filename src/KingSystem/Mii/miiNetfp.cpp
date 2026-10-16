#include "KingSystem/Mii/miiNetfp.h"
#include "KingSystem/Mii/miiUMii.h"

namespace ksys::mii {

// NON_MATCHING: register allocation (arg / umii swapped) and some block order.
void sub_7100F5A708(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii) {
    const auto& face = umii.getFace();
    switch (arg.type) {
    case 0:
        sub_7100F5B5B8(out, umii);
        return;
    case 1: {
        const char* name;
        const bool found = ModelCreator::instance()->sub_7100F4C9FC(&name, *face.mouth.type, arg);
        const char* part = sUnk_710260D1A0[arg.type].cstr();
        const char* mouth = sUnk_710260DC50[umii.sub_7100F4BF0C()].cstr();
        if (found)
            out->format("%s_%s_%s", part, mouth, name);
        else
            out->format("%s_%s_%03d", part, mouth, *face.mouth.type);
        return;
    }
    case 2:
        out->format("%s_%03d", sUnk_710260D1A0[arg.type].cstr(), *face.nose.type);
        return;
    case 3: {
        const auto& body = umii.getBody();
        const s32 hat = *umii.getCommon().hat;
        if ((hat >= 0 &&
             (*body.race != 0 || *body.type == 1 || *body.type == 4 || hat != 0)) ||
            *face.hair.type == 0x1e) {
            out->clear();
            return;
        }
        if (umii.getAge() != UMii::Personal::Age_Child) {
            const char* name;
            const bool found = ModelCreator::instance()->sub_7100F4C9FC(&name, *face.hair.type, arg);
            const char* part = sUnk_710260D1A0[arg.type].cstr();
            if (found)
                out->format("%s_C_%s", part, name);
            else
                out->format("%s_C_%03d", part, *face.hair.type);
            return;
        }
        const char* part = sUnk_710260D1A0[arg.type].cstr();
        const char* hair = sUnk_710260D7A0[umii.getAge()].cstr();
        s32 type = *face.hair.type;
        if (type > 6)
            type = 0;
        out->format("%s_%s_%03d", part, hair, type);
        return;
    }
    case 4:
        if (*face.glass.type == 0) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D1A0[arg.type].cstr(), *face.glass.type);
        return;
    case 5: {
        const s32 type = *face.beard.mustache;
        if (type == 0 || umii.isFemale() || umii.getAge() == UMii::Personal::Age_Child) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D1A0[arg.type].cstr(), type);
        return;
    }
    case 6: {
        const s32 type = *face.beard.type;
        if (u32(type - 1) > 2 || umii.isFemale() || umii.getAge() == UMii::Personal::Age_Child) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D1A0[arg.type].cstr(), type);
        return;
    }
    case 7:
        if (*umii.getCommon().backpack != 0) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D1A0[arg.type].cstr(), 0);
        return;
    case 8:
        sub_7100F5B774(out, umii);
        return;
    case 11:
        if (*face.hair.type == 0x1e && *umii.getCommon().hat < 0) {
            out->clear();
            return;
        }
        break;
    case 12:
        if (*face.glass.type == 0) {
            out->clear();
            return;
        }
        break;
    case 13:
        if ((*face.beard.type == 0 && *face.beard.mustache == 0) || umii.isFemale() ||
            umii.getAge() == UMii::Personal::Age_Child) {
            out->clear();
            return;
        }
        break;
    default:
        break;
    }
    out->format("%s", sUnk_710260D1A0[arg.type].cstr());
}

// NON_MATCHING: the plant checks compile to cmp 0 / b.le instead of cmp 1 / b.lt.
void sub_7100F5AB68(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii) {
    const auto& korok = umii.getKorok();
    switch (arg.type) {
    case 0:
        out->format("%s%s_%s_%03d", sUnk_710260D3A0[arg.type].cstr(),
                    sUnk_710260DB50[*umii.getBody().type].cstr(),
                    sUnk_710260D7A0[umii.getSexAge()].cstr(), *umii.getBody().number);
        return;
    case 1:
        out->format("%s_%s_%03d", sUnk_710260D3A0[arg.type].cstr(),
                    sUnk_710260D7A0[umii.getSexAge()].cstr(), *korok.mask);
        return;
    case 2:
        if (*korok.left_plant < 1) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D3A0[arg.type].cstr(), *korok.left_plant - 1);
        return;
    case 3:
        if (*korok.right_plant < 1) {
            out->clear();
            return;
        }
        out->format("%s_%03d", sUnk_710260D3A0[arg.type].cstr(), *korok.right_plant - 1);
        return;
    default:
        out->format("%s", sUnk_710260D3A0[arg.type].cstr());
        return;
    }
}

// NON_MATCHING: block order (the original tests 2, 1, then 0).
void sub_7100F5ADA8(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii) {
    const s32 type = arg.type;
    if (type == 2) {
        sub_7100F5BA04(out, umii);
        return;
    }
    if (type != 1) {
        if (type == 0) {
            out->format("%s%s_%s_%03d", sUnk_710260D480[type].cstr(),
                        sUnk_710260DB50[*umii.getBody().type].cstr(),
                        sUnk_710260D7A0[umii.getSexAge()].cstr(), *umii.getBody().number);
            return;
        }
        out->format("%s", sUnk_710260D480[type].cstr());
        return;
    }
    if (*umii.getCommon().backpack != 0) {
        out->clear();
        return;
    }
    out->format("%s_%03d", sUnk_710260D480[type].cstr(), 0);
}

void sub_7100F5AF44(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii) {
    const s32 type = arg.type;
    const char* part = sUnk_710260D510[type].cstr();
    if (type != 0) {
        out->format("%s", part);
        return;
    }
    out->format("%s%s_%s_%03d", part, sUnk_710260DB50[*umii.getBody().type].cstr(),
                sUnk_710260D7A0[umii.getSexAge()].cstr(), *umii.getBody().number);
}

// NON_MATCHING: the original tests the age for 2, then 1, then 0 (ours tests 0 first).
void sub_7100F5B5B8(sead::BufferedSafeString* out, const UMii& umii) {
    const auto& body = umii.getBody();
    if (*body.type == UMii::Body::Type_N) {
        const auto age = umii.getAge();
        if (age == UMii::Personal::Age_OldAdult) {
            out->format("%s%s_X_%03d", sUnk_710260D1A0[0].cstr(),
                        sUnk_710260DB50[*body.type].cstr(), *body.number);
            return;
        }
        if (age != UMii::Personal::Age_Adult) {
            if (age != UMii::Personal::Age_Child)
                return;
            out->format("%s%s_B_%03d", sUnk_710260D1A0[0].cstr(),
                        sUnk_710260DB50[*body.type].cstr(), *body.number);
            return;
        }
    }
    out->format("%s%s_%s_%03d", sUnk_710260D1A0[0].cstr(), sUnk_710260DB50[*body.type].cstr(),
                sUnk_710260D7A0[umii.getSexAge()].cstr(), *body.number);
}

void sub_7100F5B774(sead::BufferedSafeString* out, const UMii& umii) {
    const auto& common = umii.getCommon();
    if (*common.hat == 4 || *common.hat < 0) {
        out->clear();
        return;
    }
    const s32 type = *umii.getBody().type;
    switch (type) {
    case UMii::Body::Type_C:
    case UMii::Body::Type_T:
    case UMii::Body::Type_S:
        out->format("%sC_C_%03d", sUnk_710260D1A0[8].cstr(), *common.hat);
        return;
    case UMii::Body::Type_N:
    case UMii::Body::Type_SK:
        out->format("%s%s_%s_%03d", sUnk_710260D1A0[8].cstr(), sUnk_710260DB50[type].cstr(),
                    sUnk_710260D7A0[umii.getSexAge()].cstr(), *common.hat);
        return;
    default:
        return;
    }
}

}  // namespace ksys::mii
