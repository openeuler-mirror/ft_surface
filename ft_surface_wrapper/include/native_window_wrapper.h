/*
 * Copyright (c) 2021-2022 Huawei Technologies Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdint.h>
#include "external_window.h"
#ifndef NATIVE_WINDOW_WRAPPER_H_
#define NATIVE_WINDOW_WRAPPER_H_
#define SUCCESS 0
#define FAILED -1

#ifdef __cplusplus
extern "C" {
#endif

int LoadFtSurface();
int OpenLibraryTest();

int32_t NativeWindowRequestBufferWrapper(OHNativeWindow *window,
    OHNativeWindowBuffer **buffer, int *fenceFd);

int32_t NativeWindowHandleOptWrapper(OHNativeWindow *window, int code, ...);

int32_t NativeWindowCancelBufferWrapper(OHNativeWindow *window, OHNativeWindowBuffer *buffer);

BufferHandle *GetBufferHandleFromNativeWrapper(OHNativeWindowBuffer *buffer);

int32_t NativeObjectUnreferenceWrapper(void *obj);

int32_t NativeObjectReferenceWrapper(void *obj);

int32_t NativeWindowFlushBufferWrapper(OHNativeWindow *window, OHNativeWindowBuffer *buffer,
    int fenceFd, struct OHNativeWindowRegion region);
#ifdef __cplusplus
}
#endif
#endif //NATIVE_WINDOW_WRAPPER_H_