#include <regex.h>
#include "Input_Handling.h"

#define NUMBER_OF_OPERATIONS 9

regex_t regex;

char* operations[NUMBER_OF_OPERATIONS] = {
	"ins WARTOSC",
	"del WARTOSC",
	"srch WARTOSC",
	"prev WARTOSC",
	"next WARTOSC",
	"min",
	"max",
	"print",
	"quit"
};

char* operation_description[NUMBER_OF_OPERATIONS] = {
	"wstawia WARTOSC do BBST (jesli WARTOSCI nie ma w BBST)\n",
	"usuwa WARTOSC z BBST (jesli WARTOSC znajduje sie w BBST)\n",
	"zwraca wskaznik na wierzcholek BBST, gdzie jest WARTOSC (zwraca NULLa, jesli WARTOSCI nie ma w BBST)\n",
	"zwraca wskaznik na wierzcholek BBST, gdzie jest najwieksza wartosc z mniejszych od WARTOSCI (zwraca NULLa, jesli nie ma takiej wartosci w BBST)\n",
	"zwraca wskaznik na wierzcholek BBST, gdzie jest najmniejsza wartosc z wiekszych od WARTOSCI (zwraca NULLa, jesli nie ma takiej wartosci w BBST)\n",
	"zwraca minimalna wartosc w BBST\n",
	"zwraca maksymalna wartosc w BBST\n",
	"wyswietla cale BBST w postaci semigraficznej (korzen po lewej stronie, najmniejsza wartosc na gorze, a najwieksza na dole)\n",
	"konczy wczytywanie danych\n"
};

void print_operations(FILE* stream)
{
	print_text(stream, "", "Mozliwe polecenia:\n");

	FOR(i, NUMBER_OF_OPERATIONS)
	{
		print_text(stream, operations[i], operation_description[i]);
	}

	print_text(stream, "", "\n");
	print_text(stream, "UWAGA!", "WARTOSC jest typu int, WARTOSC moze zawierac wiodace 0\n\n");
}

bool read_int(int* value)
{
	char str[100];
	scanf(" %s", str);

	// Kompilacja REGEXa

	bool czy_wstapil_blad_podczas_kompilacji_regexa = regcomp(&regex, "^-?[0-9]*$", REG_EXTENDED);

	if(czy_wstapil_blad_podczas_kompilacji_regexa)
	{
		// system("clear");

		print_error(stderr, "", "\n-----------------------------------\n");
		print_error(stderr, "ERROR", "Blad podczas kompilacji regexa!\n");
		print_error(stderr, "", "-----------------------------------\n\n");

		regfree(&regex);

		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "D:PRZED!\n");

	int x = regexec(&regex, str, 0, NULL, 0);

	fprintf(stderr, "D:PO! %d\n", x);

	if(!x)
	{
		int rozmiar_napisu = (int) strlen(str);

		int dlugosc_liczby_bez_zer_wiodacych = 0;
		bool czy_sa_zera_wiodace = true;

		FOR(i, rozmiar_napisu)
		{
			if(str[i] == '-')
			{
				continue;
			}

			if(str[i] != '0')
			{
				czy_sa_zera_wiodace = false;
			}

			if(!czy_sa_zera_wiodace)
			{
				dlugosc_liczby_bez_zer_wiodacych++;
			}
		}

		if((dlugosc_liczby_bez_zer_wiodacych < 10) || (dlugosc_liczby_bez_zer_wiodacych == 10 && ((str[0] == '-' && str[1] == '1') || str[0] == '1')))
		{
			(*value) = atoi(str);

			return EXIT_SUCCESS;
		}

		else
		{
			system("clear");

			print_error(stderr, "", "\n-----------------------------------\n");
			print_error(stderr, "ERROR", "Bledna wartosc liczby!\n");
			print_error(stderr, "", "Wpisz poprawna liczbe!\n");
			print_error(stderr, "", "-----------------------------------\n\n");

			return EXIT_FAILURE;
		}
	}

	else if(x == REG_NOMATCH)
	{
		system("clear");

		print_error(stderr, "", "\n-----------------------------------\n");
		print_error(stderr, "ERROR", "Bledna wartosc liczby!\n");
		print_error(stderr, "", "Wpisz poprawna liczbe!\n");
		print_error(stderr, "", "-----------------------------------\n\n");

		return EXIT_FAILURE;
	}

	else
	{
		char msg_bufor[100];

		regerror(x, &regex, msg_bufor, sizeof(msg_bufor));

		// system("clear");

		print_error(stderr, "", "\n-----------------------------------\n");
		print_error(stderr, "Regex match failed:", msg_bufor);
		print_error(stderr, "", "\n");
		print_error(stderr, "", "-----------------------------------\n\n");

		regfree(&regex);

	    exit(EXIT_FAILURE);
	}
}

void read_data(AVL_OS_Tree* tree)
{
	print_operations(stdout);

	int values[MAX_N];

	int wskaznik_na_operacje = 0;

	while(true)
	{
		char operation[100];
		scanf(" %s", operation);

		if(strcmp(operation, "ins") == 0)
		{
			int value;
			scanf("%d", &value);

			// while(read_int(&value) == EXIT_FAILURE) {}

			AVL_OS_Tree_Node* node = avl_os_tree_lookup_node(tree, &value);

			if(node != NULL && tree->compare_function(avl_os_tree_node_value(node), &value) == 0)
			{
				print_error(stderr, "", "\n-----------------------------------\n");
				print_error(stderr, "ERROR", "W AVL_OS_Tree juz istnieje podana wartosc!\n");
				print_error(stderr, "", "-----------------------------------\n\n");
			}

			else
			{
				values[wskaznik_na_operacje] = value;

				avl_os_tree_insert(tree, &values[wskaznik_na_operacje], &values[wskaznik_na_operacje]);

				wskaznik_na_operacje++;
			}
		}

		else if(strcmp(operation, "del") == 0)
		{
			int value;
			scanf("%d", &value);
			// while(read_int(&value) == EXIT_FAILURE) {}

			if(tree->root == NULL)
			{
				print_error(stderr, "", "\n-----------------------------------\n");
				print_error(stderr, "ERROR", "AVL_OS_Tree jest puste!\n");
				print_error(stderr, "", "-----------------------------------\n\n");
			}

			else
			{
				bool czy_nie_udalo_sie_usunac = avl_os_tree_remove(tree, &value);

				if(czy_nie_udalo_sie_usunac)
				{
					print_error(stderr, "", "\n-----------------------------------\n");
					print_error(stderr, "ERROR", "W AVL_OS_Tree nie ma podanej wartosci!\n");
					print_error(stderr, "", "-----------------------------------\n\n");
				}

				// else
				// {
					// fprintf(stderr, "D: udalo sie usunac wartosc!\n");
				// }
			}
		}

		else if(strcmp(operation, "srch") == 0)
		{
			int value;
			scanf("%d", &value);
			// while(read_int(&value) == EXIT_FAILURE) {}

			AVL_OS_Tree_Node* node = avl_os_tree_lookup_node(tree, &value);

			if(node != NULL && tree->compare_function(avl_os_tree_node_value(node), &value) == 0)
			{
				int* wynik = avl_os_tree_node_value(node);

				printf("TAK\n");
			}

			else
			{
				printf("NIE\n");
			}
		}

		else if(strcmp(operation, "prev") == 0)
		{
			int value;
			scanf("%d", &value);
			// while(read_int(&value) == EXIT_FAILURE) {}

			if(tree->root == NULL)
			{
				print_error(stderr, "", "\n-----------------------------------\n");
				print_error(stderr, "ERROR", "AVL_OS_Tree jest puste!\n");
				print_error(stderr, "", "-----------------------------------\n\n");
			}

			else
			{
				AVL_OS_Tree_Node* node = prev(tree, &value);

				if(node == NULL)
				{
					print_error(stderr, "", "\n-----------------------------------\n");
					print_error(stderr, "ERROR", "W AVL_OS_Tree nie ma wartosci mniejszej od podanej!\n");
					print_error(stderr, "", "-----------------------------------\n\n");
				}

				else
				{
					int* wynik = avl_os_tree_node_value(node);

					printf("%d\n", *wynik);
				}
			}
		}

		else if(strcmp(operation, "next") == 0)
		{
			int value;
			scanf("%d", &value);
			// while(read_int(&value) == EXIT_FAILURE) {}

			if(tree->root == NULL)
			{
				print_error(stderr, "", "\n-----------------------------------\n");
				print_error(stderr, "ERROR", "AVL_OS_Tree jest puste!\n");
				print_error(stderr, "", "-----------------------------------\n\n");
			}

			else
			{
				AVL_OS_Tree_Node* node = next(tree, &value);

				if(node == NULL)
				{
					print_error(stderr, "", "\n-----------------------------------\n");
					print_error(stderr, "ERROR", "W AVL_OS_Tree nie ma wartosci wiekszej od podanej!\n");
					print_error(stderr, "", "-----------------------------------\n\n");
				}

				else
				{
					int* wynik = avl_os_tree_node_value(node);

					printf("%d\n", *wynik);
				}
			}
		}

		else if(strcmp(operation, "min") == 0)
		{
			AVL_OS_Tree_Node* min_node = min_element(tree);

			if(min_node == NULL)
			{
				print_error(stderr, "", "\n-----------------------------------\n");
				print_error(stderr, "ERROR", "AVL_OS_Tree jest puste!\n");
				print_error(stderr, "", "-----------------------------------\n\n");
			}

			else
			{
				int* wynik = avl_os_tree_node_value(min_node);

				printf("%d\n", *wynik);
			}
		}

		else if(strcmp(operation, "max") == 0)
		{
			AVL_OS_Tree_Node* max_node = max_element(tree);

			if(max_node == NULL)
			{
				print_error(stderr, "", "\n-----------------------------------\n");
				print_error(stderr, "ERROR", "AVL_OS_Tree jest puste!\n");
				print_error(stderr, "", "-----------------------------------\n\n");
			}

			else
			{
				int* wynik = avl_os_tree_node_value(max_node);

				printf("%d\n", *wynik);
			}
		}

		else if(strcmp(operation, "print") == 0)
		{
			// print_array(tree);

			print_tree(tree);
		}

		else if(strcmp(operation, "quit") == 0)
		{
			break;
		}

		else
		{
			system("clear");

			print_error(stderr, "", "\n-----------------------------------\n");
			print_error(stderr, "ERROR", "Bledne polecenie!\n");
			print_error(stderr, "", "Wpisz poprawne polecenie!\n");
			print_error(stderr, "", "-----------------------------------\n\n");

			print_operations(stderr);
		}
	}

	// regfree(&regex);
}