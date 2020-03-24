#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEW 0
#define MAXCAPACITY 30
#define START 10
#define QUANTUM 4
#define MAXMEM 300
#define FILENAME "input.txt"
#define OUTPUT "simplified_output.txt"
#define OUTPUT_COMPLETE "complete_output.txt"
#define MEMGEST "best_fit"

_Bool mem_access_denied = 0;
int to_print = -1, check_ram = 0, check_mem = 10;

struct program_control_block
{
    int pid, program_counter, state, time, time_to_ready, io_op_read, io_op_write, to_exit, start_mem, end_mem, parent; //state 0 -> new, 1 -> ready  2 -> run, 3 -> block, 4 -> exit
};

struct program_control_block *pcb_new(int pid, int program_counter, int state, int time_to_ready, int parent){
    struct program_control_block *new= malloc(sizeof(struct program_control_block));

    new -> pid = pid; new -> program_counter = program_counter; new -> state = state; new -> time_to_ready = time_to_ready;
    new -> time = 0; new -> io_op_read = 0; new -> io_op_write = 0; new -> to_exit = 0; new -> start_mem = 0; new -> end_mem = 0;
    new -> parent = parent;

    return new;
}
//-----------------------------------------------------------------------------------------

struct process{
    struct program_control_block *pcb;
    _Bool transited_state;
};

struct process *process_new(int pid, int program_counter, int state, int time_to_ready, int parent){
    struct process *new = malloc(sizeof(struct process));

    new -> pcb = pcb_new(pid, program_counter, state, time_to_ready, parent);

    new -> transited_state = 0;

    return new;
}

void process_destroy(struct process *to_destroy)
{
    free(to_destroy -> pcb);
    free(to_destroy);
}
//-----------------------------------------------------------------------------------------
struct process_queue_node{
    struct process *process;
    struct process_queue_node *next, *prev;
};

struct process_queue_node *new_node(struct process *curr){
    struct process_queue_node *new = malloc(sizeof(struct process_queue_node));

    new -> process = curr;
    new -> prev = NULL;
    new -> next = NULL;

    return new;
}

struct process_queue{
    struct process_queue_node *head, *tail;
    int occupied;
};

struct process_queue *process_queue_new(){
    struct process_queue *this = malloc(sizeof(struct process_queue));

    this -> head = NULL;
    this -> tail = NULL;

    this -> occupied = 0;

    return this;
}

_Bool process_queue_enqueue(struct process_queue *this_queue, struct process_queue_node *to_queue){

    if (this_queue -> occupied == MAXCAPACITY)
    {
        return 0;
    }

    else if (this_queue -> head == NULL)
    {
        this_queue -> head = to_queue;
        this_queue -> head -> next = NULL;
        this_queue -> head -> prev = NULL;
        this_queue -> tail = to_queue;
        this_queue -> tail -> next = NULL;
        this_queue -> tail -> prev = NULL;
    }

    else if (this_queue -> head != NULL && this_queue -> tail == NULL)
    {
        this_queue -> head -> prev = to_queue;
        this_queue -> tail = this_queue -> head;
        this_queue -> tail -> next = NULL;
        this_queue -> head = to_queue;
        this_queue -> head -> next = this_queue -> tail;
    }

    else{
        this_queue -> head -> prev = to_queue;
        to_queue -> next = this_queue -> head;
        this_queue -> head = to_queue;
    }

    this_queue -> occupied++;

    return 1;
}

struct process_queue_node *process_queue_dequeue(struct process_queue *this_queue){
    struct process_queue_node *temp, *aux;

    if (this_queue -> occupied == 0)
    {
        return 0;
    }

    else if (this_queue -> head == this_queue -> tail)
    {
        temp = this_queue -> head;

        this_queue -> head = NULL;
        this_queue -> tail = NULL;

    }

    else{
        temp = this_queue -> tail;

        if (this_queue -> tail -> prev == this_queue -> head)
        {
            this_queue -> tail = this_queue -> head;
            this_queue -> tail -> prev = NULL;
            this_queue -> tail -> next = NULL;
        }

        else{
            aux = this_queue -> tail -> prev;
            aux -> next = NULL;
            this_queue -> tail = NULL;
            this_queue -> tail = aux;
        }
    }

    this_queue -> occupied--;

    return temp;
}

void process_queue_remove(struct process_queue *this_queue, int pid){
    struct process_queue_node *temp = this_queue -> head;

    while (temp != NULL)
    {
        if (temp -> process -> pcb -> pid == pid)
        {
            temp -> prev -> next = temp -> next;
            temp -> next -> prev = temp -> prev;
            break;
        }

        temp = temp -> next;
    }
}

void process_queue_destroy(struct process_queue *this_queue){
    if (this_queue -> occupied != 0)
    {
        while (this_queue -> head != NULL)
        {
            if (this_queue -> tail == NULL)
            {
                free(this_queue -> head);
            }

            else{
                if (this_queue -> tail -> prev == this_queue -> head)
                {
                    free(this_queue -> tail);
                }

                else{
                    struct process_queue_node *aux = this_queue -> tail -> prev;

                    free(this_queue -> tail);

                    this_queue -> tail = aux;
                    this_queue -> tail -> next = NULL;
                }
            }
        }
    }

    free(this_queue);
}

//-----------------------------------------------------------------------------------------
int next_fit(int mem[], int ram[], struct process_queue_node *to_mem){
    int space_available = NEW, space_needed = NEW, i = check_mem;

    for (int j = to_mem -> process -> pcb -> start_mem; j < to_mem -> process -> pcb -> end_mem; ++j) {
        space_needed++;
    }

    while(space_available < space_needed) {
        if (mem[i] == -1)
        {
            space_available++;
        }
        if (i == MAXMEM)
        {
            return -1;
        }
        if (mem[i] != -1){
            if (space_available == 0)
            {
                check_mem++;
            }
            else {
                check_mem += space_available;
                space_available = 0;
            }
        }

        i++;
    }

    return check_mem;
}

//-----------------------------------------------------------------------------------------
int best_fit(int mem[], int ram[], struct process_queue_node *to_mem)
{
    int space_available = NEW, space_needed = NEW, save_here, block_space = MAXMEM, counter = 1;

    for (int j = to_mem -> process -> pcb -> start_mem; j < to_mem -> process -> pcb -> end_mem; ++j) {
        space_needed++;
    }

    save_here = START;
    for (int i = START; i < MAXMEM; ++i) {
        while (mem[i] == -1)
        {
            space_available++;
            i++;
            counter++;

            if (i == MAXMEM)
            {
                break;
            }
        }

        if (space_available >= space_needed && space_available < block_space)
        {
            block_space = space_available;
            check_mem = save_here;
            save_here += counter;
            counter = 1;
        }
        save_here += counter;
        counter = 1;

    }

    return check_mem;
}

//-----------------------------------------------------------------------------------------
void save_to_mem(int mem[], int ram[], struct process_queue_node *to_mem){
    int here, counter = 0, start_ram = to_mem -> process -> pcb -> start_mem, end_ram = to_mem -> process -> pcb -> end_mem;
    char mem_gest[] = MEMGEST;

    if (strcmp(mem_gest, "next_fit") == 0)
    {
        here = next_fit(mem, ram, to_mem);
    }
    else{
        here = best_fit(mem, ram, to_mem);
    }

    if (here != -1)
    {
        to_mem -> process -> pcb -> program_counter = here;
        to_mem -> process -> pcb -> start_mem = here;
        to_mem -> process -> pcb -> end_mem = here;

        for (int i = start_ram; i < end_ram; ++i) {
            if (ram[i] == -1)
            {
                break;
            }

            mem[here + counter] = ram[i];
            to_mem -> process -> pcb -> end_mem++;
            counter++;
        }
    }

    else{
        check_mem = START;
    }

    for (int j = start_ram; j < end_ram; ++j) {
        if (ram[j] == -1)
        {
            break;
        }

        ram[j] = -1;
    }
}

//-----------------------------------------------------------------------------------------

struct process *create_process(FILE *fp, int p_id, int ram[]){
    int i = NEW, ttr = NEW, tmp_inst = NEW, instructions[MAXMEM];
    char stop;
    struct process *temp;

    for (int j = 0; j < MAXMEM; ++j) {
        instructions[j] = -1;
    }

    fscanf(fp, "%d", &ttr);

    temp = process_new(p_id, START, -1, ttr, -1);

    fscanf(fp, "%c", &stop);
    while (stop != '\n')
    {
        fscanf(fp, "%d", &tmp_inst);
        if (fscanf(fp, "%c", &stop) == EOF)
        {
            instructions[i] = tmp_inst;
            break;
        }
        instructions[i] = tmp_inst;
        i++;
    }

    i = NEW;

    temp -> pcb -> start_mem = check_ram;
    temp -> pcb -> end_mem = check_ram;
    temp -> pcb -> program_counter = check_ram;

    while(instructions[i] != -1)
    {
        ram[check_ram] = instructions[i];
        check_ram++; i++;
        temp -> pcb -> end_mem++;
    }

    return temp;
}

struct process *create_clone(int p_id, int mem[], int ram[], struct process_queue_node *to_clone){
    struct process *cloned = process_new(p_id, START, -1, 0, to_clone -> process -> pcb -> pid);

    cloned -> pcb -> start_mem = check_ram;
    cloned -> pcb -> end_mem = check_ram;

    for (int t = to_clone -> process -> pcb -> start_mem; t < to_clone -> process -> pcb -> end_mem; ++t) {
        ram[check_ram] = mem[t];
        cloned -> pcb -> end_mem++;
        check_ram++;
    }

    return cloned;
}

void give_output(struct process_queue_node *processes_running[], int curr_time, FILE *output){
    int state;

    fprintf(output, "%02d", curr_time);

    for (int i = 0; i < MAXCAPACITY; ++i) {
        if (processes_running[i] == NULL)
        {
            break;
        }

        state = processes_running[i] -> process -> pcb -> state;

        if (state != -1)
        {
            fprintf(output, "|");
            switch (state) {
                case 0:
                    fprintf(output, " new ");
                    break;

                case 1:
                    fprintf(output, "ready");
                    break;

                case 2:
                    fprintf(output, " run ");
                    break;

                case 3:
                    fprintf(output, "block");
                    break;

                case 4:
                    fprintf(output, "exit ");
                    break;

                default:
                    fprintf(output, "     ");
                    break;
            }
        }
    }

    if (to_print != -1)
    {
        fprintf(output, " %d", to_print);

        to_print = -1;
    }

    if (mem_access_denied == 1)
    {
        fprintf(output, " MEMORY ACCESS VIOLATION");

        mem_access_denied--;
    }
    fprintf(output, "\n");
}

void give_complete_output(struct process_queue_node *processes_running[], int curr_time, FILE *output, int mem[])
{
    int state;

    fprintf(output, "%02d", curr_time);

    for (int i = 0; i < MAXCAPACITY; ++i) {
        if (processes_running[i] == NULL)
        {
            break;
        }

        state = processes_running[i] -> process -> pcb -> state;

        if (state != -1)
        {
            fprintf(output, "|");
            switch (state) {
                case 0:
                    fprintf(output, " new ");
                    break;

                case 1:
                    fprintf(output, "ready");
                    break;

                case 2:
                    fprintf(output, " run ");
                    break;

                case 3:
                    fprintf(output, "block");
                    break;

                case 4:
                    fprintf(output, "exit ");
                    break;

                default:
                    fprintf(output, "     ");
                    break;
            }
        }
    }

    if (to_print != -1)
    {
        fprintf(output, " %d", to_print);

        to_print = -1;
    }

    if (mem_access_denied == 1)
    {
        fprintf(output, " MEMORY ACCESS VIOLATION");

        mem_access_denied--;
    }

    fprintf(output, "\n");
    fprintf(output, "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    fprintf(output, "\n");

    int print_mem = 0;

    while (print_mem != MAXMEM)
    {
        for (int i = 0; i < 10; ++i) {
            fprintf(output, "%d ", mem[print_mem]);
            print_mem++;
        }

        fprintf(output, "\n");
    }

    fprintf(output, "\n");
    fprintf(output, "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    fprintf(output, "\n");
}

int main()
{
    int p_id = 1, disk = -1, p_r = NEW, p_e = NEW, pc_here = -1;
    FILE *fp = fopen(FILENAME, "r");
    int ram[MAXMEM];
    int mem[MAXMEM]; // index 0 - 9 -> reserved variables, 10 -.. -> instructions;
    for (int l = 0; l < MAXMEM; ++l) {
        ram[l] = -1;
        mem[l] = -1;
    }

    struct process_queue_node *to_processes = NULL, *aux = NULL;

    struct process_queue_node *processes_running[MAXCAPACITY];
    for (int k = 0; k < MAXCAPACITY; ++k) {
        processes_running[k] = NULL;
    }

    struct process_queue *new = process_queue_new();
    struct process_queue *ready = process_queue_new();
    struct process_queue *run = process_queue_new();
    struct process_queue *block = process_queue_new();
    struct process_queue *exit = process_queue_new();

    while(!feof(fp))
    {
        to_processes = new_node(create_process(fp, p_id, ram));

        processes_running[p_r] = to_processes;
        p_id++; p_r++;
    }

    fclose(fp);

    FILE *output = fopen(OUTPUT, "w+"), *output_complete = fopen(OUTPUT_COMPLETE, "w+");

    //round_robin quantum  4--------------------------
    int curr_time = NEW;
    while(p_r != p_e)
    {
        if (processes_running[NEW] != NULL)
        {
            for (int i = 0; i < MAXCAPACITY; ++i)
            {
                if (processes_running[i] == NULL)
                {
                    break;
                }
                if (processes_running[i] -> process -> pcb -> time_to_ready == curr_time)
                {
                    processes_running[i]->process->pcb->state++;
                    processes_running[i]->process->transited_state++;
                    process_queue_enqueue(new, processes_running[i]);
                }
            }
        }

        //----------------------------------------------------------------------------------------------
        if(run -> tail != NULL)
        {
            if (run -> tail -> process -> pcb -> io_op_read == 1 || run -> tail -> process -> pcb -> io_op_write == 1){
                run -> tail -> process -> pcb -> state++;
                run -> tail -> process -> transited_state++;
                run -> tail -> process -> pcb -> time = 0;
                process_queue_enqueue(block, process_queue_dequeue(run));
            }
        }

        if (block -> tail != NULL)//testar
        {
            if (block -> tail -> process -> transited_state == 0)
            {
                block -> tail -> process -> pcb -> time++;

                if (block -> tail -> process -> pcb -> time == 3)
                {

                    if (block -> tail -> process -> pcb -> io_op_read == 1)//teste case 9
                    {
                        mem[block -> tail -> process -> pcb -> program_counter] = disk;
                        block -> tail -> process -> pcb -> io_op_read--;
                        block -> tail -> process -> pcb -> program_counter += 2;
                    }

                    if (block -> tail -> process -> pcb -> io_op_write == 1)//teste case 8
                    {
                        disk = mem[block -> tail -> process -> pcb -> program_counter];
                        block -> tail -> process -> pcb -> io_op_write--;
                        block -> tail -> process -> pcb -> program_counter += 2;
                    }

                    block -> tail -> process -> pcb -> state = block -> tail -> process -> pcb -> state - 2;
                    block -> tail -> process -> transited_state++;
                    block -> tail -> process -> pcb -> time = 0;
                    process_queue_enqueue(ready, process_queue_dequeue(block));
                }
            }
        }

        if (exit -> tail != NULL)
        {
            to_processes = exit -> tail;

            if (to_processes -> process -> pcb -> state != 4)
            {
                to_processes -> process -> pcb -> state = 4;
                to_processes -> process -> transited_state++;
            }

            while (to_processes != NULL)
            {
                if (to_processes -> process -> transited_state == 0)
                {
                    to_processes -> process -> pcb -> state++;

                    for (int i = (to_processes -> process -> pcb -> start_mem); i < to_processes -> process -> pcb -> end_mem; ++i)
                    {
                        mem[i] = -1;
                    }

                    p_e++;
                    aux = to_processes -> prev;
                    process_queue_dequeue(exit);
                    to_processes = aux;
                }

                else{
                    aux = to_processes -> prev;
                    to_processes = aux;
                }

            }
        }

        if(run -> tail != NULL)
        {
            if (run -> tail -> process -> pcb -> to_exit == 1)
            {
                run -> tail -> process -> pcb -> state = run -> tail -> process -> pcb -> state + 2;
                process_queue_enqueue(exit, process_queue_dequeue(run));
            }
        }

        if(run -> tail != NULL)
        {
            if (run -> tail -> process -> pcb -> time == QUANTUM)
            {
                run -> tail -> process -> pcb -> state--;
                run -> tail -> process -> transited_state++;
                run -> tail -> process -> pcb -> time = 0;
                process_queue_enqueue(ready, process_queue_dequeue(run));
            }
        }

        to_processes = new -> tail;
        while (to_processes != NULL)
        {
            if (to_processes -> process -> transited_state == 0)
            {
                to_processes -> process -> pcb-> state++;
                to_processes -> process -> transited_state++;
                save_to_mem(mem, ram, to_processes);
                to_processes = to_processes -> prev;
                process_queue_enqueue(ready, process_queue_dequeue(new));
            }
            else{
                to_processes = to_processes -> prev;
            }
        }

        if (ready -> tail != NULL)
        {
            if (run -> occupied == 0)
            {
                ready -> tail -> process -> pcb -> state++;
                ready -> tail -> process -> transited_state++;
                process_queue_enqueue(run, process_queue_dequeue(ready));
            }

        }

        if (run -> tail != NULL) {
            switch (mem[run -> tail -> process -> pcb -> program_counter]) {
                case 0:
                    run -> tail -> process -> pcb -> program_counter++;
                    int var_1 = mem[run -> tail -> process -> pcb -> program_counter] - 1;

                    if (var_1 >= 10)
                    {
                        mem_access_denied++;
                        run -> tail -> process -> pcb -> to_exit++;
                        process_queue_enqueue(exit, process_queue_dequeue(run));
                        break;
                    }

                    run -> tail -> process -> pcb -> program_counter++;
                    int var_2_val = mem[mem[run -> tail -> process -> pcb -> program_counter] - 1];
                    mem[var_1] = var_2_val;
                    run -> tail -> process -> pcb -> program_counter++;
                    break;

                case 1:
                    run -> tail -> process -> pcb -> program_counter++;
                    int var_set = mem[run -> tail -> process -> pcb -> program_counter ] - 1;

                    if (var_set >= 10)
                    {
                        mem_access_denied++;
                        run -> tail -> process -> pcb -> to_exit++;
                        process_queue_enqueue(exit, process_queue_dequeue(run));
                        break;
                    }

                    run -> tail -> process -> pcb -> program_counter++;
                    int val = mem[run -> tail -> process -> pcb -> program_counter];
                    mem[var_set] = val;
                    run -> tail -> process -> pcb -> program_counter++;
                    break;

                case 2://precisa de teste i guess
                    run -> tail -> process -> pcb -> program_counter++;

                    if (mem[run -> tail -> process -> pcb -> program_counter] - 1 >= 10)
                    {
                        mem_access_denied++;
                        run -> tail -> process -> pcb -> to_exit++;
                        process_queue_enqueue(exit, process_queue_dequeue(run));
                        break;
                    }

                    mem[mem[run -> tail -> process -> pcb -> program_counter] - 1]++;
                    run -> tail -> process -> pcb -> program_counter += 2;
                    break;

                case 3://precisa de teste i guess
                    run -> tail -> process -> pcb -> program_counter++;

                    if (mem[run -> tail -> process -> pcb -> program_counter] - 1 >= 10)
                    {
                        mem_access_denied++;
                        run -> tail -> process -> pcb -> to_exit++;
                        process_queue_enqueue(exit, process_queue_dequeue(run));
                        break;
                    }

                    mem[mem[run -> tail -> process -> pcb -> program_counter] - 1]--;
                    run -> tail -> process -> pcb -> program_counter += 2;
                    break;

                case 4://instrução BACKWARD
                    run -> tail -> process -> pcb -> program_counter++;

                    if ((run -> tail -> process -> pcb -> program_counter - 1) - mem[run -> tail -> process -> pcb -> program_counter] * 3 >= run -> tail -> process -> pcb -> start_mem)
                    {
                        run -> tail -> process -> pcb -> program_counter -= mem[run -> tail -> process -> pcb -> program_counter] * 3;
                        run -> tail -> process -> pcb -> program_counter--;
                    }
                    else{
                        //falta output completo
                        mem_access_denied++;
                        run -> tail -> process -> pcb -> to_exit++;
                        process_queue_enqueue(exit, process_queue_dequeue(run));
                    }
                    break;

                case 5://instrução FORWARD
                    run -> tail -> process -> pcb -> program_counter++;

                    if ((run -> tail -> process -> pcb -> program_counter - 1) + mem[run -> tail -> process -> pcb -> program_counter] * 3 <= run -> tail -> process -> pcb -> end_mem)
                    {
                        run -> tail -> process -> pcb -> program_counter += mem[run -> tail -> process -> pcb -> program_counter] * 3;
                        run -> tail -> process -> pcb -> program_counter--;
                    }
                    else{
                        //falta output completo
                        mem_access_denied++;
                        run -> tail -> process -> pcb -> to_exit++;
                        process_queue_enqueue(exit, process_queue_dequeue(run));
                    }
                    break;

                case 6://precisa de teste
                    run -> tail -> process -> pcb -> program_counter++;
                    if (mem[mem[run -> tail -> process -> pcb -> program_counter] - 1] == 0)
                    {
                        run -> tail -> process -> pcb -> program_counter++;
                        int jump = mem[run -> tail -> process -> pcb -> program_counter] * 3 - 1;
                        run -> tail -> process -> pcb -> program_counter++;

                        if (run -> tail -> process -> pcb -> program_counter + jump <= run -> tail -> process -> pcb -> end_mem)
                        {
                            run -> tail -> process -> pcb -> program_counter += jump;
                            run -> tail -> process -> pcb -> program_counter -= 2;
                        }
                        else{
                            mem_access_denied++;
                            run -> tail -> process -> pcb -> to_exit++;
                            process_queue_enqueue(exit, process_queue_dequeue(run));
                        }

                    }
                    else{
                        run -> tail -> process -> pcb -> program_counter += 2;
                    }
                    break;

                case 7://instrução fork()
                    run -> tail -> process -> pcb -> program_counter++;

                    pc_here = run -> tail -> process -> pcb -> program_counter - run -> tail -> process -> pcb -> start_mem;
                    to_processes = new_node(create_clone(p_id, mem, ram, run -> tail));

                    save_to_mem(mem, ram, to_processes);

                    to_processes -> process -> pcb -> program_counter += pc_here + 2;
                    to_processes -> process -> pcb -> state = 1;

                    processes_running[p_r] = to_processes;
                    process_queue_enqueue(ready, to_processes);
                    p_id++; p_r++;

                    if (run -> tail -> process -> pcb -> parent == -1)
                    {
                        if (mem[run -> tail -> process -> pcb -> program_counter] - 1 >= 10)
                        {
                            mem_access_denied++;
                            run -> tail -> process -> pcb -> to_exit++;
                            process_queue_enqueue(exit, process_queue_dequeue(run));
                        }

                        mem[mem[run -> tail -> process -> pcb -> program_counter] - 1] = to_processes -> process -> pcb -> pid;
                    }
                    else{
                        if (mem[run -> tail -> process -> pcb -> program_counter] - 1 >= 10)
                        {
                            mem_access_denied++;
                            run -> tail -> process -> pcb -> to_exit++;
                            process_queue_enqueue(exit, process_queue_dequeue(run));
                        }

                        mem[mem[run -> tail -> process -> pcb -> program_counter] - 1] = 0;
                    }

                    run -> tail -> process -> pcb -> program_counter += 2;
                    break;


                case 8:
                    run -> tail -> process -> pcb -> io_op_write++;
                    run -> tail -> process -> pcb -> program_counter++;
                    break;

                case 9:
                    run -> tail -> process -> pcb -> io_op_read++;
                    run -> tail -> process -> pcb -> program_counter++;
                    break;

                case 10://precisa de teste
                    run -> tail -> process -> pcb -> program_counter++;

                    if (mem[run -> tail -> process -> pcb -> program_counter] -1 >= 10)
                    {
                        mem_access_denied++;
                        run -> tail -> process -> pcb -> to_exit++;
                        process_queue_enqueue(exit, process_queue_dequeue(run));
                        break;
                    }

                    to_print = mem[mem[run -> tail -> process -> pcb -> program_counter] - 1];
                    run -> tail -> process -> pcb -> program_counter += 2;
                    break;

                case 11:
                    run -> tail -> process -> pcb -> to_exit++;
                    run -> tail -> process -> pcb -> program_counter += 3;
                    break;
            }

            if (run -> tail != NULL)
            {
                if(run -> tail -> process -> pcb -> program_counter >= run -> tail -> process -> pcb -> end_mem && run -> tail -> process -> pcb -> to_exit == 0)
                {
                    mem_access_denied++;
                    run -> tail -> process -> pcb -> to_exit++;
                    process_queue_enqueue(exit, process_queue_dequeue(run));

                }

                else{
                    run -> tail -> process -> pcb -> time++;
                }
            }
        }


        //-----------------------------------------------------------------------------------------------

        for (int j = 0; j < MAXCAPACITY; ++j)
        {
            if (processes_running[j] == NULL)
            {
                break;
            }

            if (processes_running[j] -> process -> transited_state == 1)
            {
                processes_running[j] -> process -> transited_state--;
            }
        }

        give_output(processes_running, curr_time, output);
        give_complete_output(processes_running, curr_time, output_complete, mem);

        curr_time++;
    }
    //-------------------------------------------------

    for (int m = 0; m < MAXCAPACITY; ++m) {
        if (processes_running[m] != NULL)
        {
            free(processes_running[m] -> process -> pcb);
            free(processes_running[m]);
        }
    }

    fclose(output);
    fclose(output_complete);
    process_queue_destroy(new);
    process_queue_destroy(ready);
    process_queue_destroy(run);
    process_queue_destroy(block);
    process_queue_destroy(exit);

    return 0;
}