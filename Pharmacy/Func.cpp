#include "Func.h"
Node* root = NewNode;

void build_menu()
{
	Preparat p;
menustart:
	system("cls");
	printf("Alegeti optiunea:\n\n");
	printf("1. Adauga element la inceputul listei.\n");
	printf("2. Adauga element la sfarsitul listei.\n");
	printf("3. Afiseaza lista din memorie.\n");
	printf("4. Afiseaza lista din fisier.\n");
	printf("5. Sterge un element din lista.\n");
	printf("6. Incarca lista din fisier in memorie.\n");
	printf("7. Sterge toate elementele.\n");
	printf("8. Sorteaza elementele in fisier dupa metoda Shell.\n");
	printf("9. Salveaza lista in fisier.\n");
	printf("10. Iesire din program.\n");
	int option;
	scanf("%d", &option);
	switch (option)
	{
	case 1:
		printf("Nume preparat:");
		scanf("%s", &p.nume);
		printf("Pret:");
		scanf("%d", &p.pret);
		printf("Este nevoie de prescriptie medicala? (Da/Nu):");
		scanf("%s", &p.pr_med);
		printf("Tip Preperat:");
		scanf("%s", &p.tip);
		add_first(p);
		goto menustart;
		break;
	case 2:
		printf("Nume preparat:");
		scanf("%s", &p.nume);
		printf("Pret:");
		scanf("%d", &p.pret);
		printf("Este nevoie de prescriptie medicala? (Da/Nu):");
		scanf("%s", &p.pr_med);
		printf("Tip Preperat:");
		scanf("%s", &p.tip);
		add_last(p);
		break;
	case 3:
		display(0);
		getch();
		goto menustart;
		break;
	case 4:
		display(1);
		getch();
		goto menustart;
		break;
	case 5:
		printf("Indicati indexul elementului pentru a fi sters:");
		int index;
		scanf("%d", &index);
		delete_at(index);
		getch();
		goto menustart;
		break;
	case 6:
		read_from_file();
		break;
	case 7:
		clear_list();
		printf("Sters cu success!!");
		getch();
		goto menustart;
		break;
	case 8:
		file_shell_sort();
		getch();
		goto menustart;
		break;
	case 9:
		save_to_file();
		goto menustart;
		break;
	case 10:
		exit(0);
		break;
	default:
		printf("Optiune indicata gresit.");
		break;
	}
}

void add_last(Preparat item)
{
	Node* tmp = root;
	while (root->next != NULL)
	{
		root = root->next;
	}
	root->next = NewNode;
	root->next->data = item;
	root->next->next = NULL;
	root = tmp;
}

void add_first(Preparat item)
{
	Node* newitem = NewNode;
	newitem->next = root->next;
	root->next = newitem;
	newitem->data = item;
}

void display(int needfile)
{
	if (needfile == 1)
	{
		read_from_file();
	}
	Node* tmp = root;
	for (int i = 0; i < 21; i++)
		printf("=");
	printf("\n");
	while (root->next != NULL)
	{
		root = root->next;
		printf("%d |%s |%-2s |%s \n", root->data.pret, root->data.nume, root->data.pr_med, root->data.tip);
	}
	for (int i = 0; i < 21; i++)
		printf("=");
	printf("\n");
	root = tmp;
}

void delete_at(int id)
{
	if (((id + 1) > get_length()) || id < 0)
	{
		printf("Eroare: index indicat in afara diapazonului.\n\n");
		return;
	}
	int i = -1;
	Node* tmp = root;
	Node* prev;
	while (root->next != NULL)
	{
		prev = root;
		root = root->next;
		i++;
		if (i == id)
		{
			if (root->next != NULL)
			{
				prev->next = root->next;
				free(root);
				root = prev->next;
			}
			else
			{
				prev->next = NULL;
				free(root);
				break;
			}
		}
	}
	root = tmp;
	printf("Sters cu success!!");
}

int get_length()
{
	Node* temp = root;
	int count = 0;
	while (root->next != NULL)
	{
		root = root->next;
		count++;
	}
	root = temp;
	return count;
}

void save_to_file()
{
	FILE* file = fopen(FileName, "w");
	Node* temp = root;
	while (root->next!=NULL)
	{
		root = root->next;
		fwrite(&root->data, sizeof(Preparat), 1, file);
	}
	root = temp;
	fclose(file);
}

void read_from_file()
{
	clear_list();
	FILE* file = fopen(FileName, "r");
	if (file==NULL)
	{
		printf("Eroare, fisierul nu exista");
		return;
	}
	Preparat buff;
	Node* temp = root;
	fread(&buff, sizeof(Preparat), 1, file);
	while (!feof(file))
	{
		root->next = NewNode;
		root = root->next;
		root->data = buff;
		fread(&buff, sizeof(Preparat), 1, file);
	}
	root->next = NULL;
	root = temp;
	fclose(file);
}

void clear_list()
{
	Node* temp = root;
	Node* prev;
	if (root->next!=NULL)
		root = root->next;
	else
		return;
	while (root->next!=NULL)
	{
		prev = root;
		root = root->next;
		free(prev);
	}
	root = temp;
	root->next = NULL;
}

void file_shell_sort()
{
	read_from_file();
	int quantity = get_length();
	Preparat obj1, obj2;
	FILE* file = fopen(FileName, "r+");
	if (file==NULL)
	{
		printf("Eroare fisierul nu exista.");
		return;
	}
	printf("Alegeti campul de sortare:\n\n");
	printf("1. Pret 2. Nume 3. Prescriptie Medicala 4. Tip\n");
	int op1;
	scanf("%d", &op1);
	printf("1. Ascendent 2. Descendent\n");
	int op2;
	scanf("%d", &op2);
	for (int pas = quantity/2; pas > 0; pas/=2)
	{
		for (int i = pas; i < quantity; i++)
		{
			for (int j = i-pas; j >= 0; j-=pas)
			{
				fseek(file, j * sizeof(obj1), SEEK_SET);
				fread(&obj1, sizeof(obj1), 1, file);
				fseek(file, (j + pas) * sizeof(obj2), SEEK_SET);
				fread(&obj2, sizeof(obj2), 1, file);
				switch (op1)
				{
				case 1:
					switch (op2)
					{
					case 1:
						if (obj1.pret > obj2.pret)
						{
							fseek(file, (j + pas) * sizeof(obj1), SEEK_SET);
							fwrite(&obj1, sizeof(obj1), 1, file);
							fseek(file, j * sizeof(obj2), SEEK_SET);
							fwrite(&obj2, sizeof(obj2), 1, file);
						}
							break;
					case 2:
						if (obj1.pret < obj2.pret)
						{
							fseek(file, (j + pas) * sizeof(obj1), SEEK_SET);
							fwrite(&obj1, sizeof(obj1), 1, file);
							fseek(file, j * sizeof(obj2), SEEK_SET);
							fwrite(&obj2, sizeof(obj2), 1, file);
						}
						break;
					default:
						break;
					}

				case 2:
					switch (op2)
					{
					case 1:
						if (strcmp(obj1.nume,obj2.nume)>0)
						{
							fseek(file, (j + pas) * sizeof(obj1), SEEK_SET);
							fwrite(&obj1, sizeof(obj1), 1, file);
							fseek(file, j * sizeof(obj2), SEEK_SET);
							fwrite(&obj2, sizeof(obj2), 1, file);
						}
						break;
					case 2:
						if (strcmp(obj1.nume, obj2.nume)<0)
						{
							fseek(file, (j + pas) * sizeof(obj1), SEEK_SET);
							fwrite(&obj1, sizeof(obj1), 1, file);
							fseek(file, j * sizeof(obj2), SEEK_SET);
							fwrite(&obj2, sizeof(obj2), 1, file);
						}
						break;
					}
					break;
				case 3:
					switch (op2)
					{
					case 1:
						if (strcmp(obj1.pr_med, obj2.pr_med)>0)
						{
							fseek(file, (j + pas) * sizeof(obj1), SEEK_SET);
							fwrite(&obj1, sizeof(obj1), 1, file);
							fseek(file, j * sizeof(obj2), SEEK_SET);
							fwrite(&obj2, sizeof(obj2), 1, file);
						}
						break;
					case 2:
						if (strcmp(obj1.pr_med, obj2.pr_med)<0)
						{
							fseek(file, (j + pas) * sizeof(obj1), SEEK_SET);
							fwrite(&obj1, sizeof(obj1), 1, file);
							fseek(file, j * sizeof(obj2), SEEK_SET);
							fwrite(&obj2, sizeof(obj2), 1, file);
						}
						break;
					default:
						break;
					}
					break;
				case 4:
					switch (op2)
					{
					case 1:
						if (strcmp(obj1.tip, obj2.tip)>0)
						{
							fseek(file, (j + pas) * sizeof(obj1), SEEK_SET);
							fwrite(&obj1, sizeof(obj1), 1, file);
							fseek(file, j * sizeof(obj2), SEEK_SET);
							fwrite(&obj2, sizeof(obj2), 1, file);
						}
						break;
					case 2:
						if (strcmp(obj1.tip, obj2.tip)<0)
						{
							fseek(file, (j + pas) * sizeof(obj1), SEEK_SET);
							fwrite(&obj1, sizeof(obj1), 1, file);
							fseek(file, j * sizeof(obj2), SEEK_SET);
							fwrite(&obj2, sizeof(obj2), 1, file);
						}
						break;
					}
					break;
				}
			}
		}
	}
	fclose(file);
	printf("Sortare reusita.");
}

void edit_at(int index)
{
	Node* tmp = root;
	int quant = get_length(), i = -1;
	while (root->next!=NULL)
	{
		root = root->next;
		i++;
		if (i==index)
		{
			printf("Editeaza>");
			printf("Nume:");
			scanf("%s",&root->data.nume);
			printf("Pret:");
			scanf("%d", &root->data.pret);
			printf("Prescriptie medicala:");
			scanf("%s", &root->data.pr_med);
			printf("Tip:");
			scanf("%s", &root->data.tip);
			break;
		}
	}
	root = tmp;
}
