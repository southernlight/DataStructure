#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct song Song;
typedef struct snode SNode;
typedef struct artist Artist;

typedef struct song
{
	Artist* artist;
	char* title,*path;
	int index;
}Song;

typedef struct snode
{
	SNode* next,*prev;
	Song* song;
}Snode;

typedef struct artist
{
	char* name;
	Artist* next;
	SNode* head,* tail;
}Artist;

void initialize();
void add_song(char* artist, char* title, char* path);
void status();
void load(FILE* fp);
void searchsong_byArtistAndTitle(char* artist, char* title);
void searchsong_byArtist(char* artist);
void play(int index);
void save(FILE* fp);
void remove_song(int index);


#endif