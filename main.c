typedef unsigned long size_t;

long write(int fd, const char* buffer, size_t buffer_size);
long read(int fd, void* buf, size_t count);

size_t string_length(const char* str) {
  size_t result = 0;
  while (*str++) ++result;
  return result;
}

void copy_size(const char* restrict src, char* restrict dst, size_t size) {
  for (size_t i = 0; i < size; ++i) dst[i] = src[i];
}

typedef struct {
  char* data;
  size_t used, capacity;
} memory_arena;

void arena_init(memory_arena* arena, char* mem, size_t size) {
  arena->data = mem;
  arena->used = 0;
  arena->capacity = size;
}

void* arena_push_size(memory_arena* arena, size_t size) {
  if (arena->used + size > arena->capacity) return 0;
  void* result = arena->data + arena->used;
  arena->used += size;
  return result;
}

void* arena_copy_size(memory_arena* arena, const void* buff, size_t size) {
  char *result = arena_push_size(arena, size);
  if (result) copy_size(buff, result, size);
  return result;
}

char* arena_copy_cstr(memory_arena* arena, const char* str) {
  return arena_copy_size(arena, str, string_length(str));
}

char global_memory[1024];

int main(void) {
  memory_arena global_arena;
  arena_init(&global_arena, global_memory, sizeof(global_memory));

  long ret;

  char hello[] = "hello, world\n";
  ret = write(1, hello, sizeof(hello)-1);

  char buff[1024];
  ret = read(0, buff, sizeof(buff));
  if (ret < 0) {
    char err[] = "failed to read input\n";
    write(2, err, sizeof(err)-1);
    return 1;
  }

  arena_copy_cstr(&global_arena, "input: ");
  arena_copy_size(&global_arena, buff, ret);
  arena_copy_cstr(&global_arena, "\n");
  write(1, global_arena.data, global_arena.used); 

  return ret;
}
