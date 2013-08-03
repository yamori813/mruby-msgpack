/*
 * The original is https://github.com/msgpack/msgpack-ruby
 * MessagePack for Ruby
 *
 * Copyright (C) 2008-2012 FURUHASHI Sadayuki
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#ifndef MSGPACK_MRUBY_BUFFER_CLASS_H__
#define MSGPACK_MRUBY_BUFFER_CLASS_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "buffer.h"

extern struct RClass *cMessagePack_Buffer;

void MessagePack_Buffer_module_init(mrb_state *mrb, struct RClass *mMessagePack);

mrb_value MessagePack_Buffer_wrap(mrb_state *mrb, msgpack_buffer_t* b, mrb_value owner);

void MessagePack_Buffer_initialize(mrb_state *mrb, msgpack_buffer_t* b, mrb_value io, mrb_value options);

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif /* MSGPACK_MRUBY_BUFFER_CLASS_H__ */
