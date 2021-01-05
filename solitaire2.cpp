// klondike solitaire ds project take2
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // for sleep()
#include <cwchar>
#include <windows.h>
using namespace std;

struct topnode{													// doubly list
	char color[6];
	char suit[6];
	char symbol[6];
	char turned[6];
	topnode *next;
	topnode *prev;
	topnode *tail;
};topnode *headtop = NULL;										//head node for top

struct boardnode{												//multilist
	char color[6];
	char suit[6];
	char symbol[6];
	char turned[6];
	char list[6];
	int listnumber;
	boardnode *next;
	boardnode *tail;
};	boardnode *headboard = NULL;								//head node for board

struct foundationnode{											//multilist
	char color[6];
	char suit[6];
	char symbol[6];
	char turned[6];
	char suits[10];
	foundationnode *next;
	foundationnode *tail;
};	foundationnode *headfoundation = NULL;						//global headfoundation

int totalcards = 0;												//global counter(number of cards at foundationlist)
void addtopnode(char *col, char *suite, char *symbo,char *down);
void addboardnode(char *col, char *suite, char *symbo, char *down,int order);
void addheaderboardnode(int i);
void addheaderfoundationnode(char *suite);
void displaytopnode();
void displayboard();
void displayfoundationnode();
void solitaire_initializing();
bool topToFoundation(char *, char *, char *);
bool addfoundationnode(topnode *node);
bool addboardnode2(topnode *addingcard, int d);
bool topToBoard(char *a, char *b, char *c, int d);
bool boardToBoard(char *a, char *b, char *c, int d, int e);
bool addboardtoboard(boardnode *addingcard, int e);
bool boardToFoundation(int d);
void SetColor(int ForgC);

int main()
{
    cout<<"\t\t\t\t\t\tLOADING.."<<endl;
    cout<<"\t\t\t\t\t";
    for(int i=1;i<10;i++)
    {
        sleep(1);
        printf("%c",219);
    }
    system("cls");
    SetColor(15);
    cout<<"\n\n";
    cout<<"\t\t==========================================================================================================================================================================\n";
	solitaire_initializing();
	char a[3], b[3], c[3];
	int column, column2;
	char choice;
	do{
		cout << endl <<"  \t\t\t\t\t\t\t\t\tChoose an operation:" << endl;
		cout << "  \t\t\t\t\t\t\t\t1. Top to Foundation" << endl;
		cout << "  \t\t\t\t\t\t\t\t2. Top to Board" << endl;
		cout << "  \t\t\t\t\t\t\t\t3. Board to Board" << endl;
		cout << "  \t\t\t\t\t\t\t\t4. Board to Foundation" << endl;
		cout << "  \t\t\t\t\t\t\t\t5. Exit Game" << endl;
		cout << endl <<"\t\t\t\t\t\t\t\tInput choice(1, 2, 3, 4 or 5):"; cin >> choice;
		switch (choice)
		{
		case '1':
			cout << "	Select a card from top list :"; scanf("%s %s %s", &a, &b, &c);
			if (topToFoundation(a, b, c) == false)
			{
				cout << "	wrong movement" << endl;
				cout << "   ************" << endl;
				sleep(2);
				system("cls");
				displaytopnode();
				displayboard();
				displayfoundationnode();

				break;
			}
			sleep(2);
			system("cls");
			displaytopnode();
			displayboard();
			displayfoundationnode();

			break;
		case '2':
			cout << "	Select a card from top list :"; scanf("%s %s %s", &a, &b, &c);
			cout << "	Select the number of Destination Board List :"; cin >> column;
			if (topToBoard(a, b, c, column) == false)
			{
				cout << "	wrong movement" << endl;
				cout << "************" << endl;
				sleep(1);
			    system("cls");
				displaytopnode();
				displayboard();
				displayfoundationnode();

				break;
			}
			sleep(2);
			system("cls");
			displaytopnode();
			displayboard();
			displayfoundationnode();

			break;
		case '3':
			cout << "	Select the number of source Board List :";
			cin >> column;
			cout << "	Select the number of destination Board List :";
			cin >> column2;
			cout << "	Select a card from source Board List :";
			scanf("%s %s %s", &a, &b, &c);
			//system ("CLS");

			if (boardToBoard(a, b, c, column, column2) == false)
			{
				cout << "	wrong movement" << endl;
				cout << "************" << endl;
				sleep(1);
				system("cls");
				displaytopnode();
				displayboard();
				displayfoundationnode();

				break;
			}
			sleep(2);
			system("cls");
			displaytopnode();
			displayboard();
			displayfoundationnode();

			break;
		case '4':
			cout << "	Select the number of source Board List :"; cin >> column;
			if (boardToFoundation(column) == false)
			{
			    cout << "	wrong movement" << endl;
				cout << "************" << endl;
			}
			system("cls");
			displaytopnode();
            displayboard();
            displayfoundationnode();
            break;
        case '5':
            return 0;
            break;

		default:
		    cout<<"\n";
			cout << "\t\t\t\t\t\t\t\t\tChoose beetween 1-4!" << endl;
			sleep(1);

			system("cls");
			displaytopnode();
			displayboard();
			displayfoundationnode();

			break;


		}
	} while (totalcards != 52);
    //system("cls");
    SetColor(5);		//congrats when foundation node has 52 cards
    cout<<"\t\t\t\t\t\t\t\t\tHURRAH HURRAH HURRAH HURRAH HURRAH HURRAH!!";
	cout << "\t\t\t\t\t\t\t\t\t    .-~~-.                       " << endl;
	cout << "\t\t\t\t\t\t\t\t\t   {      }        CONGRATS!!           " << endl;
	cout << "\t\t\t\t\t\t\t\t\t .--.    .--.                    " << endl;
	cout << "\t\t\t\t\t\t\t\t\t{            }      YOU WON!!            " << endl;
	cout << "\t\t\t\t\t\t\t\t\t `._.'||`._.'                " << endl;
	cout << " \t\t\t\t\t\t\t\t\t     ||                        " << endl;
	cout << "\t\t\t\t\t\t\t\t\t     '--'                          " << endl;
	cout << "\t\t\t\t\t\t\t\t\t                    " << endl;
	cin >> column;
	SetColor(15);
    return 0;
}
void addtopnode(char *col, char *suite, char *symbo,char *down)			//add function to doubly list
{
	topnode *temp = new topnode;
	strcpy(temp->color, col);
	strcpy(temp->suit, suite);
	strcpy(temp->symbol,symbo);
	strcpy(temp->turned,down);
	temp->next = NULL;
	temp->prev = NULL;
	temp->tail = NULL;
	if (headtop == NULL)
	{
		headtop = temp;
		return;
	}
	topnode *traverse = headtop;
	while (traverse->next != NULL)
		traverse = traverse->next;
	traverse->next = temp;
	temp->prev = traverse;
}
bool addfoundationnode(topnode *node)				// top to foundation add
{
	char value[6];
	int count = 1;
	if (strcmp(node->symbol, "A") == 0)				// converts symbols to number in order to easy check
		strcpy(value, "1");
	else if (strcmp(node->symbol, "J") == 0)
		strcpy(value, "11");
	else if (strcmp(node->symbol, "Q") == 0)
		strcpy(value, "12");
	else if (strcmp(node->symbol, "K") == 0)
		strcpy(value, "13");
	else
		strcpy(value, node->symbol);
	int down = atoi(value);                 // converts string to integer

	int x;

	if (strcmp(node->suit, "S") == 0)       //converts char to corresponding int for easier comparison
		x = 1;
	else if (strcmp(node->suit, "H") == 0)
		x = 2;
	else if (strcmp(node->suit, "D") == 0)
		x = 3;
	else if (strcmp(node->suit, "C") == 0)
		x = 4;

	foundationnode *traverse = headfoundation;							//finds list

	for (int i = 1; i < x; i++)
		traverse = traverse->next;

	foundationnode *traversedown = traverse;

	while (traversedown->tail != NULL)
	{
		traversedown = traversedown->tail;
		count++;
	}
	if (count != down)
        return false;						//if card number isn't equal with row order return false

	foundationnode *temp = new foundationnode;				//add last node
	strcpy(temp->suit, node->suit);
	strcpy(temp->color, node->color);
	strcpy(temp->symbol, node->symbol);
	temp->next = NULL;
	temp->tail = NULL;
	traversedown->tail = temp;

	return true;
}

bool addfoundationnode2(boardnode *replacingcard)				// BOARD to foundation add
{
	char symb[6];
	int say = 1;
	if (strcmp(replacingcard->symbol, "A") == 0)					// converts sysbols to number in order to easy check
		strcpy(symb, "1");
	else if (strcmp(replacingcard->symbol, "J") == 0)
		strcpy(symb, "11");
	else if (strcmp(replacingcard->symbol, "Q") == 0)
		strcpy(symb, "12");
	else if (strcmp(replacingcard->symbol, "K") == 0)
		strcpy(symb, "13");
	else
		strcpy(symb, replacingcard->symbol);
	int symbinnumber = atoi(symb);
	int suitnumber;

	if (strcmp(replacingcard->suit, "S") == 0)							//in order to track list
		suitnumber = 1;
	else if (strcmp(replacingcard->suit, "H") == 0)
		suitnumber = 2;
	else if (strcmp(replacingcard->suit, "D") == 0)
		suitnumber = 3;
	else if (strcmp(replacingcard->suit, "C") == 0)
		suitnumber = 4;

	foundationnode *traverse = headfoundation;

	for (int i = 1; i < suitnumber; i++)						//find list
		traverse = traverse->next;

	foundationnode *traversedown = traverse;

	while (traversedown->tail != NULL)
	{
		traversedown = traversedown->tail;
		say++;
	}
	if (say != symbinnumber) return false;						//if card number isnt equal with row order return false

	foundationnode *temp = new foundationnode;					//add last node
	strcpy(temp->suit, replacingcard->suit);
	strcpy(temp->color, replacingcard->color);
	strcpy(temp->symbol, replacingcard->symbol);
	temp->next = NULL;
	temp->tail = NULL;
	traversedown->tail = temp;
	return true;
}
bool addboardnode2(topnode *addcard, int d)            // top to board add
{
	char symbo[2];
	char symbo2[2];
	int say = 1;
	if (strcmp(addcard->symbol, "A") == 0)
		strcpy(symbo, "1");
	else if (strcmp(addcard->symbol, "J") == 0)
		strcpy(symbo, "11");
	else if (strcmp(addcard->symbol, "Q") == 0)
		strcpy(symbo, "12");
	else if (strcmp(addcard->symbol, "K") == 0)
		strcpy(symbo, "13");
	else
		strcpy(symbo, addcard->symbol);
	int symbtonum = atoi(symbo);

	boardnode *traverse = headboard;
	for (int i = 1; i < d; i++)										//find list (horizontally)
		traverse = traverse->next;

	boardnode *traversedown = traverse;
	while (traversedown->tail != NULL)							//find last node(vertically traversing)
		traversedown = traversedown->tail;
	if (strcmp(traversedown->symbol, "A") == 0)
		strcpy(symbo2, "1");
	else if (strcmp(traversedown->symbol, "J") == 0)
		strcpy(symbo2, "11");
	else if (strcmp(traversedown->symbol, "Q") == 0)
		strcpy(symbo2, "12");
	else if (strcmp(traversedown->symbol, "K") == 0)
		strcpy(symbo2, "13");
	else
		strcpy(symbo2, traversedown->symbol);
	int symb2int = atoi(symbo2);

	if (traverse->tail == NULL && symbtonum == 13)                 //on empty list king can be inserted
	{
		boardnode *temp = new boardnode;
		strcpy(temp->suit, addcard->suit);
		strcpy(temp->color, addcard->color);
		strcpy(temp->symbol, addcard->symbol);
		strcpy(temp->turned, "Up");
		temp->next = NULL;
		temp->tail = NULL;
		traverse->tail = temp;
		return true;
	}
	else if (traverse->tail == NULL && symbtonum != 13)
    {
        //printf("testestets");
        return false;
    }
   if (!(symb2int == symbtonum + 1))								//card must 1 less from upper card and different color
		return false;

	if (!(strcmp(addcard->color,traversedown->color)!=0))         //red colour should be followed by black only and vice versa
	{
		return false;
	}
	boardnode *temp = new boardnode;
	strcpy(temp->suit, addcard->suit);
	strcpy(temp->color, addcard->color);
	strcpy(temp->symbol, addcard->symbol);
	strcpy(temp->turned, "Up");
	temp->next = NULL;
	temp->tail = NULL;
	traversedown->tail = temp;
	return true;
}
bool addboardtoboard(boardnode *addingcard, int e)
{
	char symb[6];
	char symb2[6];
	int say = 1;
	if (strcmp(addingcard->symbol, "A") == 0)							// converts sysbols to number in order to easy check
		strcpy(symb, "1");
	else if (strcmp(addingcard->symbol, "J") == 0)
		strcpy(symb, "11");
	else if (strcmp(addingcard->symbol, "Q") == 0)
		strcpy(symb, "12");
	else if (strcmp(addingcard->symbol, "K") == 0)
		strcpy(symb, "13");
	else
		strcpy(symb, addingcard->symbol);
	int addingcarddegeri = atoi(symb);

	boardnode *traverse = headboard;

	for (int i = 1; i < e; i++)										//finds the list
		traverse = traverse->next;

	boardnode *traversedown = traverse;
	while (traversedown->tail != NULL)							//finds the card
		traversedown = traversedown->tail;

	if (traverse->tail == NULL && addingcarddegeri == 13)			//if list is empty you can add King
	{
		boardnode *temp = new boardnode;
		strcpy(temp->suit, addingcard->suit);
		strcpy(temp->color, addingcard->color);
		strcpy(temp->symbol, addingcard->symbol);
		strcpy(temp->turned, "Up");
		temp->next = NULL;
		temp->tail = addingcard->tail;
		traversedown->tail = temp;
		return true;
	}
	else if (traverse->tail == NULL && addingcarddegeri != 13)			//yeni addingcardndi.  if list is empty you cannot add other than king
		return false;

	if (strcmp(traversedown->symbol, "A") == 0)							// converts sysbols to number in order to easy check
		strcpy(symb2, "1");
	else if (strcmp(traversedown->symbol, "J") == 0)
		strcpy(symb2, "11");
	else if (strcmp(traversedown->symbol, "Q") == 0)
		strcpy(symb2, "12");
	else if (strcmp(traversedown->symbol, "K") == 0)
		strcpy(symb2, "13");
	else
		strcpy(symb2, traversedown->symbol);
	int symb2int = atoi(symb2);

	if (!(symb2int == addingcarddegeri + 1))								//card must 1 less from upper card and different color
		return false;

	if (!(strcmp(addingcard->color, traversedown->color) != 0))
	{
		return false;
	}

	boardnode *temp = new boardnode;						//add last node
	strcpy(temp->suit, addingcard->suit);
	strcpy(temp->color, addingcard->color);
	strcpy(temp->symbol, addingcard->symbol);
	strcpy(temp->turned, "Up");
	temp->next = NULL;
	temp->tail = addingcard->tail;
	traversedown->tail = temp;
	return true;
}
void addboardnode(char *col, char *suite, char *symbo, char *down, int order)	 //file to board multilist
{
	boardnode *temp = new boardnode;
	strcpy(temp->color, col);
	strcpy(temp->suit, suite);
	strcpy(temp->symbol, symbo);
	strcpy(temp->turned, down);
	temp->next = NULL;
	temp->tail = NULL;
	int i;
	boardnode *traverseforward = headboard;
	for (i = 1; i < order; i++)                       //go horizontally ahead
		traverseforward = traverseforward->next;
	boardnode *traversedown = traverseforward;
	while (traversedown->tail != NULL)
		traversedown = traversedown->tail;
	traversedown->tail = temp;
}
void addheaderboardnode(int i)
{
	boardnode *temp = new boardnode;
	temp->listnumber = i;
	strcpy(temp->list, ". list");
	temp->next = NULL;
	temp->tail = NULL;
	if (headboard == NULL)
	{
		headboard = temp;
		return;
	}
	boardnode *traverse = headboard;
	while (traverse->next != NULL)
		traverse = traverse->next;
	traverse->next = temp;
}
void addheaderfoundationnode(char *suite)
{
	foundationnode *temp = new foundationnode;
	strcpy(temp->suits, suite);
	temp->next = NULL;
	temp->tail = NULL;
	if (headfoundation == NULL)
	{
		headfoundation = temp;
		return;
	}
	foundationnode *traverse = headfoundation;
	while (traverse->next != NULL)
		traverse = traverse->next;
	traverse->next = temp;
}
void displaytopnode()									// list top node
{
	topnode *traverse = headtop->next;
	cout << endl << "                                                                  *****        \t\tTOP LIST                 *****" << endl;
	int s=0;
	cout<<"\n";
	cout<<"                ";
	while (traverse->next != NULL)
	{
	    s++;
        if(strcmp(traverse->color, "R") == 0)
        {
            SetColor(12);
            cout <<"R"<< ","<< traverse->suit << "," << traverse->symbol ;
        }

		else
        {
             SetColor(15);
            cout <<"B"<< ","<< traverse->suit << "," << traverse->symbol;

        }
        SetColor(15);
        cout <<"||";
		traverse = traverse->next;
	}
	cout << endl;
	cout<<endl;
    cout<<"\t\t==========================================================================================================================================================================\n";
    cout<<endl;
}
void displayboard()
{
	boardnode *traverse[7];						//7 traverse pointers for 7 lists
	boardnode *assign = headboard;
	int i = 0;
	while (assign != NULL)
	{
		traverse[i] = assign->tail;
		assign = assign->next;
		i++;
	}
	cout << endl <<"                                                                *****                   BOARD LIST                 *****\n" << endl;
	cout << "                                                                1.list   2.list   3.list   4.list   5.list   6.list   7.list" << endl;
	cout<<"                                                                ";
	for (int i = 1; i < 14; i++)
	{
		if (traverse[0] == NULL &&traverse[1] == NULL &&traverse[2] == NULL &&traverse[3] == NULL &&traverse[4] == NULL &&traverse[5] == NULL &&traverse[6] == NULL)
			break;
		if (traverse[0] != NULL)
		{
			if (strcmp(traverse[0]->turned, "Up") == 0)
            {
                if(strcmp(traverse[0]->color, "R") == 0)
                  {
                      SetColor(12);
                      cout <<"R"<< ","<< traverse[0]->suit << "," << traverse[0]->symbol << "    ";

                  }

		       else
                 {
                    SetColor(15);
                    cout <<"B"<< ","<< traverse[0]->suit << "," << traverse[0]->symbol << "    ";

                 }
                 SetColor(15);

            }
			else cout << "X         ";
			traverse[0] = traverse[0]->tail;

		}
		else{ cout << "         "; }
		if (traverse[1] != NULL)
		{
			if (strcmp(traverse[1]->turned, "Up") == 0)
            {
                if(strcmp(traverse[1]->color, "R") == 0)
                  {
                      SetColor(12);
                      cout <<"R"<< "," << traverse[1]->suit << "," << traverse[1]->symbol << "    ";

                  }
                else
                 {
                    SetColor(15);
                    cout <<"B"<< ","<< traverse[1]->suit << "," << traverse[1]->symbol << "    ";

                 }
                 SetColor(15);

            }

			else cout << "X        ";
			traverse[1] = traverse[1]->tail;
		}
		else{ cout << "         "; }
		if (traverse[2] != NULL)
		{
			if (strcmp(traverse[2]->turned, "Up") == 0)
            {
                if(strcmp(traverse[2]->color, "R") == 0)
                  {
                      SetColor(12);
                      cout <<"R"<< ","<< traverse[2]->suit << "," << traverse[2]->symbol << "    ";

                  }

		       else
                 {
                    SetColor(15);
                    cout <<"B"<< ","<< traverse[2]->suit << "," << traverse[2]->symbol << "    ";

                 }
                 SetColor(15);
				//cout << traverse[2]->suit << "," << traverse[2]->symbol << "    ";
            }
			else cout << "X        ";
			traverse[2] = traverse[2]->tail;
		}
		else{ cout << "         "; }
		if (traverse[3] != NULL)
		{
			if (strcmp(traverse[3]->turned, "Up") == 0)
            {
                if(strcmp(traverse[3]->color, "R") == 0)
                  {
                      SetColor(12);
                      cout <<"R"<< ","<< traverse[3]->suit << "," << traverse[3]->symbol << "    ";

                  }

		       else
                 {
                    SetColor(15);
                    cout <<"B"<< ","<< traverse[3]->suit << "," << traverse[3]->symbol << "    ";

                 }
                 SetColor(15);
				//cout << traverse[3]->suit << "," << traverse[3]->symbol << "    ";
            }
			else cout << "X        ";
			traverse[3] = traverse[3]->tail;
		}
		else{ cout << "         "; }
		if (traverse[4] != NULL)
		{
			if (strcmp(traverse[4]->turned, "Up") == 0)
            {
                if(strcmp(traverse[4]->color, "R") == 0)
                  {
                      SetColor(12);
                      cout <<"R"<< ","<< traverse[4]->suit << "," << traverse[4]->symbol << "    ";

                  }

		       else
                 {
                    SetColor(15);
                    cout <<"B"<< ","<< traverse[4]->suit << "," << traverse[4]->symbol << "    ";

                 }
                 SetColor(15);
				//cout << traverse[4]->suit << "," << traverse[4]->symbol << "    ";
            }
			else cout << "X        ";
			traverse[4] = traverse[4]->tail;
		}
		else{ cout << "         "; }
		if (traverse[5] != NULL)
		{
			if (strcmp(traverse[5]->turned, "Up") == 0)
            {
                if(strcmp(traverse[5]->color, "R") == 0)
                  {
                      SetColor(12);
                      cout <<"R"<< ","<< traverse[5]->suit << "," << traverse[5]->symbol << "    ";

                  }

		       else
                 {
                    SetColor(15);
                    cout <<"B"<< ","<< traverse[5]->suit << "," << traverse[5]->symbol << "    ";

                 }
                 SetColor(15);
				//cout << traverse[5]->suit << "," << traverse[5]->symbol << "    ";
            }
			else cout << "X        ";
			traverse[5] = traverse[5]->tail;
		}
		else{ cout << "         "; }
		if (traverse[6] != NULL)
		{
			if (strcmp(traverse[6]->turned, "Up") == 0)
            {
                if(strcmp(traverse[6]->color, "R") == 0)
                  {
                      SetColor(12);
                      cout <<"R"<< ","<< traverse[6]->suit << "," << traverse[6]->symbol << "    ";

                  }

		       else
                 {
                    SetColor(15);
                    cout <<"B"<< ","<< traverse[6]->suit << "," << traverse[6]->symbol << "    ";

                 }
                 SetColor(15);
				//cout << traverse[6]->suit << "," << traverse[6]->symbol << "    ";
            }
			else cout << "X        ";
			traverse[6] = traverse[6]->tail;
		}
		else{ cout << "         "; }
		cout <<endl;
		cout<<"                                                                ";
		//cout<<"|"<<endl;
		//cout<<"                                                                ";

	}


}

void displayfoundationnode()
{
	foundationnode *traverse[4];					//4 traverse pointers for 4 list
	foundationnode *assign = headfoundation;
	int i = 0;
	while (assign != NULL)
	{
		traverse[i] = assign->tail;
		assign = assign->next;
		i++;
	}
	cout << endl << "Foundation Lists" << endl;
  cout << "Spades   Hearts   Diamonds  Clubs" << endl;
  for (int i = 1; i < 14; i++)
	{
		if (traverse[0] == NULL &&traverse[1] == NULL &&traverse[2] == NULL &&traverse[3] == NULL)
			break;

		if (traverse[0] != NULL)
		{
		    if(strcmp(traverse[0]->color, "R") == 0)
                  {
                      SetColor(12);
                      cout <<"R"<< ","<< traverse[0]->suit << "," << traverse[0]->symbol << "    ";

                  }

		       else
                 {
                    SetColor(15);
                    cout <<"B"<< ","<< traverse[0]->suit << "," << traverse[0]->symbol << "    ";

                 }
                 SetColor(15);
				//cout << traverse[0]->suit << "," << traverse[0]->symbol << "    ";
			//cout << traverse[0]->color << "," << traverse[0]->suit << "," << traverse[0]->symbol << "    ";
			traverse[0] = traverse[0]->tail;
		}
		else{ cout << "         "; }
		if (traverse[1] != NULL)
		{
		    if(strcmp(traverse[1]->color, "R") == 0)
                  {
                      SetColor(12);
                      cout <<"R"<< ","<< traverse[1]->suit << "," << traverse[1]->symbol << "    ";

                  }

		       else
                 {
                    SetColor(15);
                    cout <<"B"<< ","<< traverse[1]->suit << "," << traverse[1]->symbol << "    ";

                 }
                 SetColor(15);
				//cout << traverse[1]->suit << "," << traverse[1]->symbol << "    ";
			//cout << traverse[1]->color << "," << traverse[1]->suit << "," << traverse[1]->symbol << "    ";
			traverse[1] = traverse[1]->tail;
		}
		else{ cout << "         "; }
		if (traverse[2] != NULL)
		{
		    if(strcmp(traverse[2]->color, "R") == 0)
                  {
                      SetColor(12);
                      cout <<"R"<< ","<< traverse[2]->suit << "," << traverse[2]->symbol << "    ";

                  }

		       else
                 {
                    SetColor(15);
                    cout <<"B"<< ","<< traverse[2]->suit << "," << traverse[2]->symbol << "    ";

                 }
                 SetColor(15);
				//cout << traverse[2]->suit << "," << traverse[2]->symbol << "    ";
			//cout << traverse[2]->color << "," << traverse[2]->suit << "," << traverse[2]->symbol << "    ";
			traverse[2] = traverse[2]->tail;
		}
		else{ cout << "         "; }
		if (traverse[3] != NULL)
		{
		    if(strcmp(traverse[3]->color, "R") == 0)
                  {
                      SetColor(12);
                      cout <<"R"<< ","<< traverse[3]->suit << "," << traverse[3]->symbol << "    ";

                  }

		       else
                 {
                    SetColor(15);
                    cout <<"B"<< "," << traverse[3]->suit << "," << traverse[3]->symbol << "    ";

                 }
                 SetColor(15);
				//cout << traverse[3]->suit << "," << traverse[3]->symbol << "    ";
			//cout << traverse[3]->color << "," << traverse[3]->suit << "," << traverse[3]->symbol;
			traverse[3] = traverse[3]->tail;
		}
		else{ cout << "         "; }
		cout << endl;
	}

}
void solitaire_initializing()
{
	char a[6], b[6], c[6], d[6], star[10];								// ex: D S A Down **

	FILE *fptr;
	fptr = fopen("solitaire.txt", "r");
	addtopnode("A", "A", "A", "A");										//topnode head starts with A A A A but never shown in console
	for (int i = 0; i < 24; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);
		addtopnode(a, b, c, d);											//add from file to top list
	}
	addtopnode("Z", "Z", "Z", "Z");
	fscanf(fptr, "%s", star);											//skip stars

	addheaderboardnode(1);											//boardlist starts with numbers but never shown in console
	for (int i = 0; i < 1; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//1. list from file to top list
		addboardnode(a, b, c, d, 1);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(2);
	for (int i = 0; i < 2; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//2. list from file to top list
		addboardnode(a, b, c, d, 2);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(3);
	for (int i = 0; i < 3; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//3. list from file to top list
		addboardnode(a, b, c, d, 3);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(4);
	for (int i = 0; i < 4; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//4. list from file to top list
		addboardnode(a, b, c, d, 4);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(5);
	for (int i = 0; i < 5; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//5. list from file to top list
		addboardnode(a, b, c, d, 5);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(6);
	for (int i = 0; i < 6; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//6. list from file to top list
		addboardnode(a, b, c, d, 6);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(7);
	for (int i = 0; i < 7; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//7. list from file to top list
		addboardnode(a, b, c, d, 7);
	}
	addheaderfoundationnode("Spades");									//foundations node starts with Symbols never shown in console
	addheaderfoundationnode("Hearts");
	addheaderfoundationnode("Diamonds");
	addheaderfoundationnode("Clubs");

	fclose(fptr);
	displaytopnode();
	displayboard();
	displayfoundationnode();
}
bool topToFoundation(char *a, char *b, char *c)
{
	bool finalss = false;
	topnode *traverse = headtop;
	while (traverse != NULL)								//checks the card
	{
		if (strcmp(traverse->color, a) == 0 && strcmp(traverse->suit, b) == 0 && strcmp(traverse->symbol, c) == 0)
		{
			finalss = true;
			break;
		}
		traverse = traverse->next;
	}
	if (finalss == true)										// if card on the top list send
	{
		if (addfoundationnode(traverse) == false)			//if not appropriate card return false
			return false;
		traverse->prev->next = traverse->next;				//break nodes
		traverse->next->prev = traverse->prev;
		cout << "Movement Succesful !" << endl;
		cout << "*********" << endl;
		totalcards++;

	}
	else                                                    //if card not on the top list return false
		return false;
	return true;
}
bool topToBoard(char *a, char *b, char *c, int d)
{
	bool finalss = false;
	topnode *traverse = headtop;
      int q=0;
	while(traverse != NULL)
	{
	    q++;
	    if(q==14)
        {
            printf("%s %s %s",a,b,c);
        }
		if (strcmp(traverse->color, a) == 0 && strcmp(traverse->suit, b) == 0 && strcmp(traverse->symbol, c) == 0)
		{
			finalss = true;
			break;
		}
		traverse = traverse->next;
	}
	if (finalss == true)
	{
		if (addboardnode2(traverse, d) == false)
			return false;
		traverse->prev->next = traverse->next;
		traverse->next->prev = traverse->prev;
		cout << "Movement Succesful !" << endl;
		cout << "*********" << endl;

	}
	else
		return false;
	return true;
}
bool boardToBoard(char *a, char *b, char *c, int d, int e)
{
	bool finalss = false;
	boardnode *traverse = headboard;
	boardnode *traverse2 = headboard;					//never used
	boardnode *traversetail;
	boardnode *traversetail2;							//never used
	boardnode *tut = headboard;
	for (int i = 1; i < d; i++)							//finds the list by the number entered
		traverse = traverse->next;
	for (int i = 1; i < e; i++)
		traverse2 = traverse2->next;

	traversetail = traverse->tail;
	tut = traverse;							// traversi
	while (traversetail != NULL)			//finds the card and checks
	{
		if (strcmp(traversetail->color, a) == 0 && strcmp(traversetail->suit, b) == 0 && strcmp(traversetail->symbol, c) == 0)
		{
			finalss = true;
			break;
		}
		traversetail = traversetail->tail;
		tut = tut->tail;
	}
	if (finalss == true)
	{
		if (addboardtoboard(traversetail, e) == false)	//checks if appropriate card if true breaks node
			return false;
		tut->tail = NULL;									// prev node =NULL
		strcpy(tut->turned, "Up");							// prev node =Up
		cout << "Movement Succesful !" << endl;
		cout << "*********" << endl;
	}
	else
		return false;
	return true;
}
bool boardToFoundation(int d)
{
	bool finals = false;
	boardnode *traverse = headboard;
	for (int i = 1; i < d; i++)						//finds column
		traverse = traverse->next;
	boardnode *temp;
	temp = traverse->tail;
	boardnode *temp2 = traverse;
	if (temp == NULL)						//if list is empty return false
		return false;
	while (temp->tail != NULL)			//finds the last card
	{
		temp = temp->tail;
		temp2 = temp2->tail;
	}

	finals = true;
	if (finals == true)
	{
		if (addfoundationnode2(temp) == false)	// check if appropriate card and breaks node
			return false;
		temp2->tail = NULL;									//prev node->tail NULL
		strcpy(temp2->turned, "Up");							//prev node = Up
		cout<< "Movement Succesful !" << endl;
		totalcards++;
		cout << "*********" << endl;
	}
	else
		return false;
	return true;
}
void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
