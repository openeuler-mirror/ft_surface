#include "native_window_wrapper.h"
#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>
#include "ftsurface_log.h"


typedef int32_t (*FunNativeWindowRequestBuffer)(OHNativeWindow *, OHNativeWindowBuffer **, int *);
typedef int32_t (*FunNativeWindowHandleOpt)(OHNativeWindow *, int, ...);
typedef int32_t (*FunNativeWindowCancelBuffer)(OHNativeWindow *, OHNativeWindowBuffer *);
typedef BufferHandle* (*FunGetBufferHandleFromNative)(OHNativeWindowBuffer *);
typedef int32_t (*FunNativeObjectReference)(void *obj);
typedef int32_t (*FunNativeObjectUnreference)(void *obj);
typedef int32_t (*FunNativeWindowFlushBuffer)(OHNativeWindow *window, OHNativeWindowBuffer *buffer,
    int fenceFd, struct OHNativeWindowRegion region);

static void *libHandle = NULL;
static FunNativeWindowRequestBuffer requestBuffer = NULL;
static FunNativeWindowHandleOpt handleOpt = NULL;
static FunNativeWindowCancelBuffer cancelBuffer = NULL;
static FunGetBufferHandleFromNative getBufferHandleFromNative = NULL;
static FunNativeObjectReference objReference = NULL;
static FunNativeObjectUnreference objUnreference = NULL;
static FunNativeWindowFlushBuffer flushBuffer = NULL;

int LoadFtSurface()
{
    if (libHandle != NULL) {
        return SUCCESS;
    }
    libHandle = dlopen("/usr/lib64/libsurface.so", RTLD_NOW | RTLD_GLOBAL);
    if (libHandle == NULL) {
        LOG("can not open libsurface.so\n");
        return FAILED;
    }
    requestBuffer = (FunNativeWindowRequestBuffer)dlsym(libHandle, "NativeWindowRequestBuffer");
    if (requestBuffer == NULL) {
        return FAILED;
    }
    handleOpt = (FunNativeWindowHandleOpt)dlsym(libHandle, "NativeWindowHandleOpt");
    if (handleOpt == NULL) {
        return FAILED;
    }
    cancelBuffer = (FunNativeWindowCancelBuffer)dlsym(libHandle, "NativeWindowCancelBuffer");
    if (cancelBuffer == NULL) {
        return FAILED;
    }
    getBufferHandleFromNative = (FunGetBufferHandleFromNative)dlsym(libHandle, "GetBufferHandleFromNative");
    if (getBufferHandleFromNative == NULL) {
        return FAILED;
    }
    objReference = (FunNativeObjectReference)dlsym(libHandle, "NativeObjectReference");
    if (objReference == NULL) {
        return FAILED;
    }
    objUnreference = (FunNativeObjectUnreference)dlsym(libHandle, "NativeObjectUnreference");
    if (objUnreference == NULL) {
        return FAILED;
    }
    flushBuffer = (FunNativeWindowFlushBuffer)dlsym(libHandle, "NativeWindowFlushBuffer");
    if (flushBuffer == NULL) {
        return FAILED;
    }
    LOG("open libsurface success\n");
    return SUCCESS;
}

int OpenLibraryTest()
{
    if (requestBuffer == NULL) {
        return FAILED;
    }
    return SUCCESS;
}

int32_t NativeWindowRequestBufferWrapper(OHNativeWindow *window,
    OHNativeWindowBuffer **buffer, int *fenceFd)
{
    LOG("%s\n", __func__);
    return requestBuffer(window, buffer, fenceFd);
}
static int32_t handleOptWrapperInner(OHNativeWindow *window, int code, va_list args) {
    int32_t ret = SUCCESS;
    switch (code)
    {
        case GET_FORMAT: {
            int32_t *format = va_arg(args, int32_t*);
            ret = handleOpt(window, code, format);
            break;
        }
        case SET_USAGE: {
            uint64_t usage = va_arg(args, uint64_t);
            ret = handleOpt(window, code, usage);
            break;
        }
        case GET_BUFFER_GEOMETRY: {
            int32_t *height = va_arg(args, int32_t*);
            int32_t *width = va_arg(args, int32_t*);
            ret = handleOpt(window, code, height, width);
            break;
        }
        default: {
            LOGE("ftsurface not support %d\n", code);
            break;
        }
    }
    return ret;
}
int32_t NativeWindowHandleOptWrapper(OHNativeWindow *window, int code, ...)
{
    LOG("%s\n", __func__);
    if (window == NULL) {
        return FAILED;
    }
    va_list args;
    va_start(args, code);
    handleOptWrapperInner(window, code, args);
    va_end(args);
    return SUCCESS;
}

int32_t NativeWindowCancelBufferWrapper(OHNativeWindow *window, OHNativeWindowBuffer *buffer)
{
    LOG("%s\n", __func__);
    return cancelBuffer(window, buffer);
}

BufferHandle *GetBufferHandleFromNativeWrapper(OHNativeWindowBuffer *buffer)
{
    LOG("%s\n", __func__);
    return getBufferHandleFromNative(buffer);
}

int32_t NativeObjectUnreferenceWrapper(void *obj)
{
    LOG("%s\n", __func__);
    return objUnreference(obj);
}

int32_t NativeObjectReferenceWrapper(void *obj)
{
    LOG("%s\n", __func__);
    return objReference(obj);
}

int32_t NativeWindowFlushBufferWrapper(OHNativeWindow *window, OHNativeWindowBuffer *buffer,
    int fenceFd, struct OHNativeWindowRegion region)
{
    LOG("%s\n", __func__);
    return flushBuffer(window, buffer, fenceFd, region);
}
