#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10000

struct Program {
    char name[17];
    char code[30];
    char responsible[30];
    char email[30];
};

struct Student {
    char personal_number[11];
    char first_name[10];
    char last_name[10];
    char gender[7];
    char age[4];
    char email[30];
    struct Program *program;
};

void realloc_students(struct Student **students, int *student_count);
void add_student(struct Student **students, int *student_count);
void modify_student(struct Student **students, int *student_count, struct Program **programs, int *program_count);
struct Student delete_student(struct Student **students, int *student_count);
void display_students(struct Student *students, int *student_count);
int str_compare(const char *s1, const char *s2);
void search_by_personal_number(struct Student *students, int *student_count);
void search_by_first_name(struct Student *students, int *student_count);
void search_by_program(struct Student *students, int *student_count);
void count_gender(struct Student *students, int *student_count);
int save_to_file(struct Student *students, int *student_count);
void load_from_file(struct Student **students, int *student_count, struct Program **programs, int *program_count);
void add_new_program(struct Program **programs, int *program_count);
void update_program(struct Program **programs, int *program_count);
struct Program realloc_programs(struct Program **programs, int *program_count);
void display_programs(struct Program *programs, int *program_count);
void copy_programs(struct Program **programs, int *program_count, struct Student **students, int *student_count);

int main()
{
    int student_count = 1;
    int program_count = 1;
    struct Student *students = (struct Student*)malloc(student_count * sizeof(struct Student));
    students->program = (struct Program*)malloc(student_count * sizeof(struct Program));
    struct Program *programs = (struct Program*)malloc(program_count * sizeof(struct Program));
    student_count = 0;
    program_count = 0;

    while (1)
    {
        int option;
        int option1;
        char yes;
        printf("Välj mellan följande, skriv tal:\n1. Add\n2. Modify\n3. Delete\n4. Search\n5. Save\n6. Load\n7. Add program\n8. Modify program\n9. Exit\n");
        scanf("%d", &option);
        printf("Option = %d\n", option);

        switch(option)
        {
            case 1:
                realloc_students(&students, &student_count);
                add_student(&students, &student_count);
                display_students(students, &student_count);
                copy_programs(&programs, &program_count, &students, &student_count);
                break;
            case 2:
                modify_student(&students, &student_count, &programs, &program_count);
                display_students(students, &student_count);
                break;
            case 3:
                delete_student(&students, &student_count);
                display_students(students, &student_count);
                break;
            case 4:
                printf("1. Personal number\n2. Name\n3. Study Program\n4. Statistics\n");
                scanf("%d", &option1);
                if (option1 == 1) search_by_personal_number(students, &student_count);
                if (option1 == 2) search_by_first_name(students, &student_count);
                if (option1 == 3) search_by_program(students, &student_count);
                if (option1 == 4) count_gender(students, &student_count);
                break;
            case 5:
                save_to_file(students, &student_count);
                break;
            case 6:
                printf("Are you sure? Press y/n\n");
                scanf(" %c", &yes); // Add a space before %c to ignore leading whitespace
                if (yes == 'y') {
                    load_from_file(&students, &student_count, &programs, &program_count);
                    display_students(students, &student_count);
                }
                break;
            case 7:
                realloc_programs(&programs, &program_count);
                add_new_program(&programs, &program_count);
                display_programs(programs, &program_count);
                break;
            case 8:
                update_program(&programs, &program_count);
                display_programs(programs, &program_count);
                break;
            case 9:
                free(students);
                free(programs);  
                exit(0);
        }
    }

    return 0;
}

void realloc_students(struct Student **students, int *student_count)
{
    *student_count = (*student_count) + 1;
    *students = realloc(*students, (*student_count) * sizeof(struct Student));
    (*students)->program = realloc((*students)->program, (*student_count) * sizeof(struct Program));
}

void add_student(struct Student **students, int *student_count)
{
    int i = (*student_count) - 1;
    struct Program *programs = (*students)->program;
    printf("Skriv ny personnummer\n");
    scanf("%11s", (*students)[i].personal_number);
    printf("Skriv förnamn\n");
    scanf("%20s", (*students)[i].first_name);
    printf("Skriv ny efternamn\n");
    scanf("%20s", (*students)[i].last_name);
    printf("Skriv gender\n");
    scanf("%6s", (*students)[i].gender);
    printf("Skriv ny program\n");
    scanf("%20s", programs[i].name);
    printf("Skriv ny age\n");
    scanf("%3s", (*students)[i].age);
    printf("Skriv ny email\n");
    scanf("%30s", (*students)[i].email);
}

char search_personal_number[11];

void modify_student(struct Student **students, int *student_count, struct Program **programs, int *program_count)
{
    struct Program **current_program = &(*programs);
    struct Student **current_students = &(*students);
    int found = 0;
    int index = -1;
    printf("Skriv personnummer\n");
    scanf("%s", search_personal_number);
    for (int i = 0; i < *student_count; i++)
    {
        if (strcmp((*students)[i].personal_number, search_personal_number) == 0)
        {
            index = i;
            found = 1;
            break;
        }
    }
    if (found)
    {
        add_student(&(*students), &index);
        copy_programs(&(*current_program), &(*program_count), &(*current_students), &index);
    }
    else
        printf("Studenten finns inte");
}

struct Student delete_student(struct Student **students, int *student_count)
{
    int found = 0;
    int index = 0;
    int count = 0;
    struct Program *programs = (*students)->program;
    printf("Skriv personnummer\n");
    scanf("%11s", search_personal_number);
    while (count < (*student_count))
    {
        if (strcmp((*students)[count].personal_number, search_personal_number) == 0)
        {
            found++;
            for (int i = count; i < (*student_count) - 1; i++)
            {
                (*students)[i] = (*students)[i + 1];
                programs[i] = programs[i + 1];
            }
            break;
        }
        count++;
    }
    if (found == 0)
        printf("Studenten finns inte i databasen\n");
    else
    {
        printf("Studenten är borttagen nu\n");
        (*student_count)--;
        *students = realloc(*students, (*student_count) * sizeof(struct Student));
        (*students)->program = realloc((*students)->program, (*student_count) * sizeof(struct Program));
    }
}

void display_students(struct Student *students, int *student_count)
{
    struct Program *programs = students->program;
    for (int i = 0; i < (*student_count); i++)
    {
        printf("%s %s %s %s %s %s %s\n", students[i].personal_number, students[i].first_name, students[i].last_name, students[i].gender, programs[i].name, students[i].age, students[i].email);
    }
}

int str_compare(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void search_by_personal_number(struct Student *students, int *student_count)
{
    struct Program *programs = students->program;
    char search_personal_number[11];
    printf("Skriv personnummer\n");
    scanf("%s", search_personal_number);
    for (int i = 0; i < (*student_count); i++)
    {
        if (strcmp(search_personal_number, students[i].personal_number) == 0)
        {
            printf("%s %s %s %s %s %s %s\n", students[i].personal_number, students[i].first_name, students[i].last_name, students[i].gender, programs[i].name, students[i].age, students[i].email);
        }
    }
}

void search_by_first_name(struct Student *students, int *student_count)
{
    struct Program *programs = students->program;
    char search_first_name[11];
    printf("Skriv förnamn\n");
    scanf("%s", search_first_name);
    for (int i = 0; i < (*student_count); i++)
    {
        if (strcmp(search_first_name, students[i].first_name) == 0)
        {
            printf("%s %s %s %s %s %s %s\n", students[i].personal_number, students[i].first_name, students[i].last_name, students[i].gender, programs[i].name, students[i].age, students[i].email);
        }
    }
}

void search_by_program(struct Student *students, int *student_count)
{
    struct Program *programs = students->program;
    char search_program_name[30];
    printf("Skriv programnamn\n");
    scanf("%s", search_program_name);
    for (int i = 0; i < (*student_count); i++)
    {
        if (strcmp(search_program_name, programs[i].name) == 0)
        {
            printf("%s %s %s %s %s %s %s\n", students[i].personal_number, students[i].first_name, students[i].last_name, students[i].gender, programs[i].name, students[i].age, students[i].email);
        }
    }
}

void count_gender(struct Student *students, int *student_count)
{
    int female = 0;
    int male = 0;
    for (int i = 0; i < (*student_count); i++)
    {
        if (strcmp(students[i].gender, "female") == 0)
        {
            female++;
        }
        if (strcmp(students[i].gender, "male") == 0)
        {
            male++;
        }
    }
    printf("Number of female students = %d\nNumber of male students = %d\n", female, male);
}

int save_to_file(struct Student *students, int *student_count)
{
    struct Program *programs = students->program;
    FILE *file;
    file = fopen("students.txt", "w");
    for (int i = 0; i < (*student_count); i++)
    {
        fprintf(file, "%s %s %s %s %s %s %s\n", students[i].personal_number, students[i].first_name, students[i].last_name, students[i].gender, programs[i].name, students[i].age, students[i].email);
    }
    fclose(file);
}

void load_from_file(struct Student **students, int *student_count, struct Program **programs, int *program_count)
{
    struct Program **current_program = &(*programs);
    struct Student **current_students = &(*students);
    FILE *file;
    file = fopen("students.txt", "r");
    if (file == NULL)
    {
        printf("No file found, cannot load\n");
        return;
    }
    int i = 0;
    while (!feof(file))
    {
        realloc_students(&(*current_students), &(*student_count));
        fscanf(file, "%s %s %s %s %s %s %s\n", (*current_students)[i].personal_number, (*current_students)[i].first_name, (*current_students)[i].last_name, (*current_students)[i].gender, (*current_students)[i].program->name, (*current_students)[i].age, (*current_students)[i].email);
        copy_programs(&(*current_program), &(*program_count), &(*current_students), &(*student_count));
        i++;
    }
    fclose(file);
}

void add_new_program(struct Program **programs, int *program_count)
{
    int i = (*program_count);
    printf("Skriv program namn\n");
    scanf("%16s", (*programs)[i].name);
    printf("Skriv program kod\n");
    scanf("%29s", (*programs)[i].code);
    printf("Skriv ansvarig\n");
    scanf("%29s", (*programs)[i].responsible);
    printf("Skriv epost\n");
    scanf("%29s", (*programs)[i].email);
    (*program_count)++;
}

void update_program(struct Program **programs, int *program_count)
{
    char program_name[17];
    int found = 0;
    printf("Skriv namn på programmet som ska uppdateras\n");
    scanf("%16s", program_name);
    for (int i = 0; i < (*program_count); i++)
    {
        if (strcmp((*programs)[i].name, program_name) == 0)
        {
            printf("Skriv ny program kod\n");
            scanf("%29s", (*programs)[i].code);
            printf("Skriv ny ansvarig\n");
            scanf("%29s", (*programs)[i].responsible);
            printf("Skriv ny epost\n");
            scanf("%29s", (*programs)[i].email);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Programmet finns inte\n");
    }
}

struct Program realloc_programs(struct Program **programs, int *program_count)
{
    *programs = realloc(*programs, (*program_count + 1) * sizeof(struct Program));
}

void display_programs(struct Program *programs, int *program_count)
{
    for (int i = 0; i < (*program_count); i++)
    {
        printf("%s %s %s %s\n", programs[i].name, programs[i].code, programs[i].responsible, programs[i].email);
    }
}

void copy_programs(struct Program **programs, int *program_count, struct Student **students, int *student_count)
{
    int i = (*student_count) - 1;
    int j;
    struct Program *current_program = (*students)->program;
    for (j = 0; j < (*program_count); j++)
    {
        if (strcmp(current_program[i].name, (*programs)[j].name) == 0)
        {
            strcpy(current_program[i].code, (*programs)[j].code);
            strcpy(current_program[i].responsible, (*programs)[j].responsible);
            strcpy(current_program[i].email, (*programs)[j].email);
            break;
        }
    }
}
