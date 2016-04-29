#pragma once
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define NewNode (Node*)malloc(sizeof(Node))
#define FileName "out.txt"

typedef struct Preparat
{
	int pret;
	char nume[25], pr_med[3], tip[20];
}Preparat;

typedef struct Node
{
	Preparat data;
	Node* next;
}Node;

extern Node* root;

void build_menu();
void add_last(Preparat item);
void add_first(Preparat item);
void display(int needfile);
void delete_at(int id);
int get_length();
void save_to_file();
void read_from_file();
void clear_list();
void file_shell_sort();
void edit_at(int index);