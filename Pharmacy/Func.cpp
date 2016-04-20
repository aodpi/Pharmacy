#include "Func.h"
Node* root = NewNode;

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

void display()
{
	read_from_file("out.txt");
	Node* tmp = root;
	for (int i = 0; i < 21; i++)
		printf("=");
	printf("\n");
	while (root->next!=NULL)
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
	FILE* file = fopen("out.txt", "w");
	Node* temp = root;
	while (root->next!=NULL)
	{
		root = root->next;
		fwrite(&root->data, sizeof(Preparat), 1, file);
	}
	root = temp;
	fclose(file);
}

void read_from_file(char *name)
{
	clear_list();
	FILE* file = fopen(name, "r");
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
	read_from_file("out.txt");
	int quantity = get_length();
	Preparat obj1, obj2;
	FILE* file = fopen("out.txt", "r++");
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
					default:
						break;
					}
					break;
					break;
				default:
					break;
				}
			}
		}
	}
	fclose(file);
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
