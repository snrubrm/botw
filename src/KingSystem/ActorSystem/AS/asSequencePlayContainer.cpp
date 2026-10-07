#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

SequencePlayContainer::SequencePlayContainer(const CreateArg&, s32, const res::ASResource*) {}

// NON_MATCHING: cached child-buffer field addresses change register allocation and store scheduling.
void SequencePlayContainer::sub_710125F94C(Context* ctx, const res::ASResource* resource,
                                        f32 value, f32 duration) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    PlayState state;
    state._0 = -1.0f;
    state._4 = false;
    state._8 = ctx->sub_7101258D1C(sub_71011653E8(resource)) + 1;
    if (record->_0 >= 0) {
        Element* child = mChildren[record->_0];
        const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
        child->sub_7101165E60(ctx, child_resource);
    }
    const s8 next = record->_1;
    record->_1 = 0xff;
    record->_0 = next;
    record->_3 &= ~2;
    const res::ASResource* child_resource = sub_71013031FC(resource, next);
    mChildren[next]->sub_710116541C(ctx, &state, child_resource);
    mChildren[next]->sub_7101165CA8(ctx, true, child_resource, -1.0f, value, duration);
}

// NON_MATCHING: the initial signed-byte index checks are combined by the compiler.
bool SequencePlayContainer::m9(Context* ctx, PlayState* state, const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    if (record->_0 >= 0 && record->_0 != 0) {
        Element* child = mChildren[record->_0];
        const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
        child->sub_7101165E60(ctx, child_resource);
    }
    record->_0 = 0;
    record->_1 = 0xff;
    const s32 counter = state->_8;
    int loops = 0;
    while (true) {
        Element* child = mChildren[record->_0];
        const res::ASResource* child_resource = sub_71013031FC(resource, record->_0);
        if (child->sub_710116541C(ctx, state, child_resource))
            return true;
        const s32 index = record->_0;
        int next = index + 1;
        if (next == mChildren.size()) {
            auto* sequence = sead::DynamicCast<const res::ASSequencePlayContainerResource>(resource);
            if (!sequence || !sequence->getSequenceLoop())
                break;
            if (loops >= 3) {
                ctx->sub_7101258ABC();
                break;
            }
            next = 0;
            ++loops;
            ctx->_e8 = -1.0f;
        } else {
            ctx->_e8 = -1.0f;
            if (index < -1)
                return true;
        }
        Element* old_child = mChildren[record->_0];
        const res::ASResource* old_resource = sub_71013031FC(resource, record->_0);
        old_child->sub_7101165E60(ctx, old_resource);
        record->_0 = next;
        state->_8 = counter;
    }
    ctx->_e8 = -1.0f;
    return true;
}

bool SequencePlayContainer::m10(Context* ctx, State* state, const res::ASResource* resource) {
    const f32 value = state->_0;
    const u32 result = sub_710125EBB0(ctx, state, resource);
    state->_0 = value;
    return result & 1;
}

// NON_MATCHING: two argument-preserving moves are scheduled in the opposite order.
f32 SequencePlayContainer::m18(Context* ctx, bool a2, f32 value, f32 a4,
                             const res::ASResource* resource) {
    Context::Record* record = ctx->sub_7101258CD4(sub_71011653E8(resource));
    if (value < 0.0f)
        return value;
    {
        PlayState state;
        state._4 = false;
        state._0 = -1.0f;
        state._8 = ctx->sub_7101258D1C(sub_71011653E8(resource)) + 1;
        auto* sequence = sead::DynamicCast<const res::ASSequencePlayContainerResource>(resource);
        for (int i = 0; value >= 0.0f;) {
            const int previous = record->_0;
            if (i != previous) {
                if (previous >= 0) {
                    Element* child = mChildren[previous];
                    const res::ASResource* child_resource = sub_71013031FC(resource, previous);
                    child->sub_7101165E60(ctx, child_resource);
                }
                Element* child = mChildren[i];
                const res::ASResource* child_resource = sub_71013031FC(resource, i);
                child->sub_710116541C(ctx, &state, child_resource);
                a2 = true;
                record->_0 = i;
            }
            Element* child = mChildren[i];
            const res::ASResource* child_resource = sub_71013031FC(resource, i);
            value = child->m18(ctx, a2, value, a4, child_resource);
            if (value < 0.0f || (!sequence->getSequenceLoop() && i == mChildren.size() - 1)) {
                if (i != previous) {
                    record->_0 = i;
                    ctx->mFlags |= 0x20;
                }
                return value;
            }
            const bool last = i + 1 == mChildren.size();
            i = last ? 0 : i + 1;
            a2 |= last;
        }
    }
    return value;
}

bool SequencePlayContainer::m27(Context* ctx, const res::ASResource* resource) {
    if (auto* sequence = sead::DynamicCast<const res::ASSequencePlayContainerResource>(resource)) {
        if (sequence->getSequenceLoop())
            return true;
    }
    return SelectorBase::m27(ctx, resource);
}

bool SequencePlayContainer::m24(Context* ctx, const res::ASResource* resource) {
    int index;
    if (!sub_71013031B4(&index, ctx, resource))
        return true;
    if (auto* sequence = sead::DynamicCast<const res::ASSequencePlayContainerResource>(resource)) {
        if (sequence->getSequenceLoop())
            return false;
    }
    if (index != mChildren.size() - 1)
        return false;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    return child->m24(ctx, child_resource);
}

// NON_MATCHING: register allocation (the original keeps the resource cast in x28 and the result in w21) and the
// exit blocks are not shared the way the original shares them
bool SequencePlayContainer::m32(Context* ctx, void* a2, void* a3, void* a4, void* a5,
                                const res::ASResource* resource, f32 value) {
    auto* sequence = sead::DynamicCast<const res::ASSequencePlayContainerResource>(resource);
    bool result = false;
    if (value > 0.0f) {
        int index = 0;
        do {
            Element* child = mChildren[index];
            const res::ASResource* child_resource = sub_71013031FC(resource, index);
            if (!child->m32(ctx, a2, a3, a4, a5, child_resource, value))
                return result;
            value = *static_cast<f32*>(a5);
            if (value < 0.0f)
                return true;
            if (!sequence->getSequenceLoop() && index == mChildren.size() - 1)
                return true;
            index = index + 1 == mChildren.size() ? 0 : index + 1;
            result = true;
        } while (value > 0.0f);
    }
    return result;
}

}  // namespace ksys::as
