#include <stdio.h>
#include <stdlib.h>

#include "../headers/task.h"
#include "../headers/common.h"
#include "../headers/db.h"

unsigned int mem_amount;
unsigned long current_index = 1;
static Task *tasks_buffer = NULL;

void init_tasks(void)
{
  if (tasks_buffer)
    return;

  FILE *file = fopen(DB_NAME, "rb");

  if (file == NULL) {
    printf("Could not open file %s\n", DB_NAME);
    exit(EXIT_FAILURE);
  }

  fread(&mem_amount, sizeof(int), 1, file);

  tasks_buffer = (Task *) malloc(
    mem_amount == 0 ? sizeof(Task) : mem_amount * sizeof(Task) + 1
  );

  if (tasks_buffer == NULL) {
    printf("Could not initialize tasks\n");
    exit(EXIT_FAILURE);
  }

  printf("mem amount is %d\n", mem_amount);
}

void create_task(void)
{
  Task *task = (Task *) malloc(sizeof(Task));

  task->id = current_index++;
  task->title = malloc(50);

  char *title_ptr = task->title;

  printf("Enter title: ");
  read_line(title_ptr);

  printf("Enter status (1 ~ Done or 0 ~ Undone): ");
  scanf(" %d", &task->status);

  tasks_buffer[++mem_amount] = *task;

  store_into_file(tasks_buffer, &mem_amount);
  save_index(&current_index);

  free(task->title);
  free(task);
}

void handle_op(char *op)
{
  switch (*op)
  {
    case 'i': {
      create_task();
      break;
    }
    case 'd': {
      break;
    };
    case 'u': {
      break;
    };
    case 'r': {
      break;
    };
  }
}
