#include "Func.h"

int main()
{
	root->next = NULL;
	/*Preparat p;
	p.pret = 20;
	strcpy(p.nume, "Analghin");
	strcpy(p.pr_med, "Da");
	strcpy(p.tip, "Cap");
	add_last(p);
	p.pret = 30;
	add_last(p);
	p.pret = 40;
	add_last(p);*/
	file_shell_sort();
	display();
	getch();
    return 0;
}

