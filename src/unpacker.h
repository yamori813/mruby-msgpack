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
#ifndef MSGPACK_MRUBY_UNPACKER_H__
#define MSGPACK_MRUBY_UNPACKER_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "buffer.h"

#ifndef MSGPACK_UNPACKER_STACK_CAPACITY
#define MSGPACK_UNPACKER_STACK_CAPACITY 128
#endif

struct msgpack_unpacker_t;
typedef struct msgpack_unpacker_t msgpack_unpacker_t;

enum stack_type_t {
  STACK_TYPE_ARRAY,
  STACK_TYPE_MAP_KEY,
  STACK_TYPE_MAP_VALUE,
};

typedef struct {
  size_t count;
  enum stack_type_t type;
  mrb_value object;
  mrb_value key;
} msgpack_unpacker_stack_t;

#define MSGPACK_UNPACKER_STACK_SIZE (8+4+8+8)  /* assumes size_t <= 64bit, enum <= 32bit, VALUE <= 64bit */

struct msgpack_unpacker_t {
  msgpack_buffer_t buffer;

  unsigned int head_byte;

  msgpack_unpacker_stack_t* stack;
  size_t stack_depth;
  size_t stack_capacity;

  mrb_value last_object;

  mrb_value reading_raw;
  size_t reading_raw_remaining;

  mrb_value buffer_ref;
};

#define UNPACKER_BUFFER_(uk) (&(uk)->buffer)

enum msgpack_unpacker_object_type {
  TYPE_NIL = 0,
  TYPE_BOOLEAN,
  TYPE_INTEGER,
  TYPE_FLOAT,
  TYPE_RAW,
  TYPE_ARRAY,
  TYPE_MAP,
};

void msgpack_unpacker_static_init(mrb_state *mrb);

void msgpack_unpacker_static_destroy(mrb_state *mrb);

void msgpack_unpacker_init(mrb_state *mrb, msgpack_unpacker_t* uk);

void msgpack_unpacker_destroy(mrb_state *mrb, msgpack_unpacker_t* uk);

void msgpack_unpacker_mark(mrb_state *mrb, msgpack_unpacker_t* uk);

void msgpack_unpacker_reset(mrb_state *mrb, msgpack_unpacker_t* uk);


/* error codes */
#define PRIMITIVE_CONTAINER_START 1
#define PRIMITIVE_OBJECT_COMPLETE 0
#define PRIMITIVE_EOF -1
#define PRIMITIVE_INVALID_BYTE -2
#define PRIMITIVE_STACK_TOO_DEEP -3
#define PRIMITIVE_UNEXPECTED_TYPE -4

int msgpack_unpacker_read(mrb_state *mrb, msgpack_unpacker_t* uk, size_t target_stack_depth);

int msgpack_unpacker_skip(mrb_state *mrb, msgpack_unpacker_t* uk, size_t target_stack_depth);

static inline mrb_value msgpack_unpacker_get_last_object(msgpack_unpacker_t* uk)
{
  return uk->last_object;
}


int msgpack_unpacker_peek_next_object_type(mrb_state *mrb, msgpack_unpacker_t* uk);

mrb_bool msgpack_unpacker_skip_nil(mrb_state *mrb, msgpack_unpacker_t* uk);

int msgpack_unpacker_read_array_header(mrb_state *mrb, msgpack_unpacker_t* uk, uint32_t* result_size);

int msgpack_unpacker_read_map_header(mrb_state *mrb, msgpack_unpacker_t* uk, uint32_t* result_size);

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif /* MSGPACK_MRUBY_UNPACKER_H__ */