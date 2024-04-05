#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "library.h"
#include "string_tools.h"

#define BUFFER_LENGTH 200

void handle_load();
void process_command();
void handle_add();
void handle_search();
void handle_play();
void handle_save();
void handle_remove();
//push test
int main()
{
    initialize();
    handle_load();
    process_command();
}

void handle_load()
{
    char buffer[BUFFER_LENGTH];
    printf("Data file name ? ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) <= 0)
        return;
    FILE *fp = fopen(buffer, "r");
    if (fp == NULL)
    {
        printf("No such file exists.\n");
        return;
    }

    load(fp);
    fclose(fp);
}

void process_command()
{
    char command_line[BUFFER_LENGTH];
    char *command;
    char *tmp;
    while (1)
    {
        printf("$ ");

        if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
            continue;

        command = strtok(command_line, " ");
        if (strcmp(command, "add") == 0)
            handle_add();
        else if (strcmp(command, "status") == 0)
            status();
        else if (strcmp(command, "search") == 0)
            handle_search();
        // else if (strcmp(command, "play") == 0)
        //     handle_play();
        else if (strcmp(command, "remove") == 0)
            handle_remove();
        else if (strcmp(command, "save") == 0)
        {
            tmp = strtok(NULL, " ");
            if (strcmp(tmp, "as") != 0)
                continue;
            handle_save();
        }
        else if (strcmp(command, "exit") == 0)
            break;
    }
}
void handle_search()
{
    char name[BUFFER_LENGTH], title[BUFFER_LENGTH];

    printf("   Artist: ");
    if (read_line(stdin, name, BUFFER_LENGTH) <= 0)
    {
        printf("   Artist name required.\n");
        return;
    }
    printf("   Title: ");
    int title_len = read_line(stdin, title, BUFFER_LENGTH);
    if (title_len <= 0)
        searchsong_byArtist(name); //�Ű� ������ �ٸ��� �ΰ� ������ �Լ�
    else
        searchsong_byArtistAndTitle(name, title);
}

void handle_add()
{
    char buffer[BUFFER_LENGTH];
    char *artist = NULL, *title = NULL, *path = NULL;
    printf("   Artist: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
        artist = strdup(buffer);
    printf("   Title: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
        title = strdup(buffer);
    printf("   Path: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0)
        path = strdup(buffer);

    add_song(artist, title, path);
}

void handle_remove()
{
    char *id_str = strtok(NULL, " ");
    int index = atoi(id_str);
    remove_song(index);
}

void handle_save()
{
    char *file_name = strtok(NULL, " ");
    FILE *fp = fopen(file_name, "w");
    save(fp);
    fclose(fp);
}

// void handle_play()
// {
//     char *id_str = strtok(NULL, " ");
//     int index = atoi(id_str);
//     play(index);
// }
