#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

SyncPlayContainer::SyncPlayContainer() {}

bool SyncPlayContainer::m10(Context* ctx, State* state, const res::ASResource* resource) {
    bool result = true;
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        result &= child->m10(ctx, state, child_resource);
        ++index;
    }
    return result;
}

void SyncPlayContainer::m11(Context* ctx, State* state, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->sub_710116554C(ctx, state, child_resource);
        ++index;
    }
}

void SyncPlayContainer::m12(Context* ctx, State* state, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m12(ctx, state, child_resource);
        ++index;
    }
}

void SyncPlayContainer::m13(Context* ctx, State* state, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m13(ctx, state, child_resource);
        ++index;
    }
}

void SyncPlayContainer::m14(Context* ctx, void* a2, State* a3, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->sub_71011654E0(ctx, a2, a3, child_resource);
        ++index;
    }
}

void SyncPlayContainer::m15(Context* ctx, State* state, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m15(ctx, state, child_resource);
        ++index;
    }
}

void SyncPlayContainer::m16(Context* ctx, const res::ASResource* resource, f32 value) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m16(ctx, child_resource, value);
        ++index;
    }
}

// NON_MATCHING: callee-saved register numbers (see SelectorBase::m17)
void SyncPlayContainer::m17(Context* ctx, u32 a2, u32 a3, const res::ASResource* resource, f32 a5,
                            f32 a6) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m17(ctx, a2, a3, child_resource, a5, a6);
        ++index;
    }
}

// NON_MATCHING: only the second literal-pool load of FLT_MAX (the checker cannot pair it with the original pool offset)
f32 SyncPlayContainer::m18(Context* ctx, bool a2, f32 a3, f32 a4,
                           const res::ASResource* resource) {
    f32 result = sead::MathCalcCommon<f32>::maxNumber();
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        const f32 value = child->m18(ctx, a2, a3, a4, child_resource);
        if (result > value)
            result = value;
        ++index;
    }
    return result;
}

void SyncPlayContainer::m19(Context* ctx, const res::ASResource* resource, f32 value) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m19(ctx, child_resource, value);
        ++index;
    }
}

void SyncPlayContainer::m20(Context* ctx, const res::ASResource* resource, f32 value) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m20(ctx, child_resource, value);
        ++index;
    }
}

void SyncPlayContainer::m21(Context* ctx, const res::ASResource* resource, f32 value) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m21(ctx, child_resource, value);
        ++index;
    }
}

void SyncPlayContainer::m22(Context* ctx, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m22(ctx, child_resource);
        ++index;
    }
}

bool SyncPlayContainer::m24(Context* ctx, const res::ASResource* resource) {
    bool result = true;
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        result &= child->m24(ctx, child_resource);
        ++index;
    }
    return result;
}

f32 SyncPlayContainer::m26(Context* ctx, const res::ASResource* resource) {
    f32 result = 0;
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        const f32 value = child->m26(ctx, child_resource);
        if (value > 0) {
            result = value;
            break;
        }
        ++index;
    }
    return result;
}

bool SyncPlayContainer::m27(Context* ctx, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        if (!child->m27(ctx, child_resource))
            return false;
        ++index;
    }
    return true;
}

void SyncPlayContainer::m28(f32* a1, Context* ctx, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m28(a1, ctx, child_resource);
        ++index;
    }
}

void SyncPlayContainer::m29(f32* a1, Context* ctx, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m29(a1, ctx, child_resource);
        ++index;
    }
}

int SyncPlayContainer::m30(f32* a1, Context* ctx, const res::ASResource* resource) {
    int result = -1;
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        const int value = child->m30(a1, ctx, child_resource);
        if (value >= 0)
            result = value;
        ++index;
    }
    return result;
}

// NON_MATCHING: the original keeps a 64-bit index and base pointer in the loop (ours strength-reduces them)
int SyncPlayContainer::m31(Context* ctx, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        const int value = child->m31(ctx, child_resource);
        if (value >= 0)
            return value;
        ++index;
    }
    return -1;
}

// NON_MATCHING: callee-saved register numbers (this / a4)
bool SyncPlayContainer::m32(Context* ctx, void* a2, void* a3, void* a4, void* a5,
                            const res::ASResource* resource, f32 value) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        if (child->m32(ctx, a2, a3, a4, a5, child_resource, value))
            return true;
        ++index;
    }
    return false;
}

bool SyncPlayContainer::m33(Context* ctx, void* a2, void* a3, const res::ASResource* resource,
                            f32 a5) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        if (child->m33(ctx, a2, a3, child_resource, a5))
            return true;
        ++index;
    }
    return false;
}

void SyncPlayContainer::m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->m34(a1, ctx, a3, child_resource);
        ++index;
    }
}

void SyncPlayContainer::m35(Context* ctx, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->sub_7101165E60(ctx, child_resource);
        ++index;
    }
}

void SyncPlayContainer::m36(Context* ctx, sead::BufferedSafeString* out,
                            const sead::SafeString& name, const res::ASResource* resource) {
    int index = 0;
    for (Element* child : mChildren) {
        const res::ASResource* child_resource = sub_71013031FC(resource, index);
        child->sub_7101165EBC(ctx, out, name, index, child_resource);
        ++index;
    }
}

}  // namespace ksys::as
