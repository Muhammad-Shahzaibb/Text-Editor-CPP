#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <stack>
#include <thread>
#include <chrono>
#include<windows.h>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class Node
{
public:

    string data;
    Node* next;
};

class Undo
{
public: 

    int line_num;
    string text;
    int cmd_num;
    int mline, nline;
};

class linked_list
{
private:

    Node* head;
    Node* tail;
    int lines_count = 0;
    int next = 1;
    stack<Undo> undoStack;

public:

    std::ofstream outfile;
    linked_list() {
        int Set[] = { 7,7,7,7,7,7,7,7 }; // DEFAULT COLORS
    int counter = 1;
    char key;

    char title[7][132] =
    {
      {"TTTTTTTTT EEEEEEEE   X       X    TTTTTTTTT     EEEEEEEE  DD        IIIII  TTTTTTTTT  OOOO0OOO   RRRRRRR     :::: "},
        {"    T     EE          X     X         T         EE        D D         I        T      O      O   RR    RR    :::: "},
        {"    T	  EE            X  X          T         EE        D   D       I        T      O      O   RR    RR    :::: "},
        {"    T     EEEEE          X            T         EEEEE     D    D      I        T      O      O   RRRRRRR     :::: "},
        {"    T     EE            X X           T         EE        D     D     I        T      O      O   RRRR        :::: "},
        {"    T     EE           X    X         T         EE        D      D    I        T      O      O   RR  RR      :::: "},
        {"    T     EEEEEEEE   X        X       T         EEEEEEEE  DDDDDDDD  IIIII      T      OOO0OOOO   RR    RR    :::: "}
    };

    int x;
    for (x = 0;x < 7;x++)
    {
        puts(title[x]);
    }

    gotoxy(45, 10);
    cout << "Select the options: "<<endl;
    for (int i = 0;;)
    {


        gotoxy(35, 12);


        color(Set[0]);
        cout << "1. INSERT";

        gotoxy(35, 13);
        color(Set[1]);
        cout << "2. DELETE";

        gotoxy(35, 14);
        color(Set[2]);
        cout << "3. REPLACE";

        gotoxy(35, 15);
        color(Set[3]);
        cout << "4. PRINT";

        gotoxy(35, 16);
        color(Set[4]);
        cout << "5. SAVE";

        gotoxy(35, 17);
        color(Set[5]);
        cout << "6. UNDO";

        gotoxy(35, 18);
        color(Set[6]);
        cout << "7. EXIT";



        
        key = _getch();

        if (key == 72 && (counter >= 1 && counter <= 8))
        {
            counter--;
        }
        if (key == 80 && (counter >= 1 && counter <= 8))
        {
            counter++;
        }
        if (key == '\r')//carriage return
            {
            gotoxy(35, 20);
                if (counter == 1)
                {
                    system("cls");
                    int lineGiven;
                    string dataGiven;
                    cout << endl<<"Enter line you want the text to be placed into : ";
                    cin >> lineGiven;
                    cout << "Enter text : ";
                    cin.ignore(1);
                    getline(cin, dataGiven);
                    dataGiven += "\n";
                    if (lineGiven == 1)
                    {
                        addtohead(dataGiven);
                    }
                    else if (lineGiven > lines_count)
                    {
                        insertfurther(dataGiven, lineGiven);
                    }
                    else if (lineGiven < lines_count)
                    {
                        insertTextInBetween(dataGiven, lineGiven);
                    }
                    else if (lineGiven == lines_count)
                    {
                        int selection;
                        cout << endl<<"Enter 1 to replace the last line, enter 2 to insert a new line";
                        cin >> selection;
                        if (selection == 1)
                        {
                            Textreplace(dataGiven, lineGiven);
                        }
                        else if (selection == 2)
                        {
                            addToTail(dataGiven);
                        }
                    }
                }
                if (counter == 2)
                {
                    system("cls");
                    int lineGiven;
                    cout << endl << "Enter the line you want to delete : ";
                    cin >> lineGiven;
                    deleteLine(lineGiven);
                }
                if (counter == 3)
                {
                    system("cls");
                    int lineGiven;
                    string dataGiven;
                    cout << endl<< "Enter line you want to change the content of : ";
                    cin >> lineGiven;
                    if (lineGiven > lines_count)
                    {
                        cout << "The line you entered exceeds the existing number of lines..." << endl;
                    }
                    else {
                        cout << "Enter the new text : ";
                        cin >> dataGiven;
                        dataGiven += "\n";
                        Textreplace(dataGiven, lineGiven);
                    }
                }
                if (counter == 4)
                {
                    system("cls");
                    Print();
                    sleep_for(nanoseconds(1000));
                }
                if (counter == 5)
                {
                    system("cls");
                    Save_Data();
                }
                if (counter == 6)
                {
                    system("cls");
                    if (undoStack.empty())
                    {
                        cout << endl<< "No command." << endl;
                        sleep_for(nanoseconds(1000));
                    }
                    else {
                        //cout<<"under construction..."<<endl;
                        undo();
                        sleep_for(nanoseconds(1000));
                    }


                }
                if (counter == 7)
                {
                    system("cls");
                  exit(1);
                }


        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;
        Set[5] = 7;
        Set[6] = 7;

        if (counter == 1)
        {
            Set[0] = 12;
        }
        if (counter == 2)
        {
            Set[1] = 12;
        }
        if (counter == 3)
        {
            Set[2] = 12;
        }
        if (counter == 4)
        {
            Set[3] = 12;
        }
        if (counter == 5)
        {
            Set[4] = 12;
        }
        if (counter == 6)
        {
            Set[5] = 12;
        }
        if (counter == 7)
        {
            Set[6] = 12;
        }
    }

            
                Set[0] = 7;
                Set[1] = 7;
                Set[2] = 7;
                Set[3] = 7;
                Set[4] = 7;
                Set[5] = 7;
                Set[6] = 7;

                if (counter == 1)
                {
                    Set[0] = 12;
                }
                if (counter == 2)
                {
                    Set[1] = 12;
                }
                if (counter == 3)
                {
                    Set[2] = 12;
                }
                if (counter == 4)
                {
                    Set[3] = 12;
                }
                if (counter == 5)
                {
                    Set[4] = 12;
                }
                if (counter == 6)
                {
                    Set[5] = 12;
                }
                if (counter == 7)
                {
                    Set[6] = 12;
                }
            }
        }
    void addtohead(string data)
    {
        if (head == NULL)
        {
            Node* temp = new Node;
            temp->data = data;
            temp->next = NULL;
            head = temp;
            tail = head;
            lines_count++;
        }
        else
        {
            Node* temp = new Node;
            temp->data = data;
            temp->next = NULL;
            temp->next = head;
            head = temp;
            lines_count++;
        }
        Undo headadder;
        headadder.line_num = 1;
        headadder.cmd_num = 1;
        undoStack.push(headadder);
    }

    void addTotailwhatever(string data)
    {
        if (head == NULL)
        {
            Node* temp = new Node;
            temp->data = data;
            temp->next = NULL;
            head = temp;
            tail = head;
            lines_count++;
        }
        else
        {
            Node* temp = new Node;
            temp->data = data;
            temp->next = NULL;
            tail->next = temp;
            tail = temp;
            lines_count++;
        }
    }

    void deletetailwhatever()
    {
        Node* temp = head;

        if (head == NULL)
        {
            cout << "Nothing deleted." << endl;
        }
        else if (head == tail)
        {
            temp = head;
            string backup = temp->data;
            delete(temp);
            head = tail = NULL;
            lines_count--;
        }
        else
        {
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            tail = temp;
            delete temp->next;
            temp->next = NULL;
            lines_count--;
        }
    }

    void addToTail(string data)
    {
        if (head == NULL)
        {
            Node* temp = new Node;
            temp->data = data;
            temp->next = NULL;
            head = temp;
            tail = head;
            lines_count++;
        }
        else
        {
            Node* temp = new Node;
            temp->data = data;
            temp->next = NULL;
            tail->next = temp;
            tail = temp;
            lines_count++;
        }
        Undo tailadder;
        tailadder.line_num = 1;
        tailadder.cmd_num = 8;
        undoStack.push(tailadder);
    }

    void headdelete()
    {
        string store = head->data;
        Node* temp = head;
        Node* nextNode = head->next;
        head = nextNode;
        delete(temp);
        lines_count--;
        Undo deletedhead;
        deletedhead.text = store;
        deletedhead.line_num = 1;
        deletedhead.cmd_num = 3;
        undoStack.push(deletedhead);
    }

    void Taildelete()
    {
        Node* temp = head;

        if (head == NULL)
        {
            cout << "Delete nothing." << endl;
        }
        else if (head == tail)
        {               
            temp = head;
            string store = temp->data;
            delete(temp);
            head = tail = NULL;
            lines_count--;
            Undo deletedTail;
            deletedTail.text = store;
            deletedTail.line_num = 1;
            deletedTail.cmd_num = 7;
            undoStack.push(deletedTail);
        }
        else
        {
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            tail = temp;
            string backup = temp->next->data;
            delete temp->next;
            temp->next = NULL;
            lines_count--;
            Undo deletedTail;
            deletedTail.text = backup;
            deletedTail.line_num = 1;
            deletedTail.cmd_num = 7;
            undoStack.push(deletedTail);
        }
    }

    void insertTextInBetween(string dataGiven, int lineGiven)
    {
        if (lineGiven == 0)
        {
            cout << "There's no line 0, did you mean 1 (cough...Google suggestions...cough)" << endl;
        }
        else if (lineGiven == 1)
        {
            if (head == NULL)
            {
                Node* temp;
                temp = new Node;
                temp->data = dataGiven;
                temp->next = NULL;
                head = temp;
                tail = head;
                lines_count++;
            }
            else 								//one or more than one Node
            {
                Node* temp;
                temp = new Node;
                temp->data = dataGiven;
                temp->next = NULL;
                temp->next = head;
                head = temp;
                lines_count++;
            }
            //May be unnecessary, dunno
            Undo insertedToHead;
            insertedToHead.line_num = 1;
            insertedToHead.cmd_num = 5;
            undoStack.push(insertedToHead);
            // addToHead(dataGiven);
            // numOfLines++;
        }
        else {
            Node* prevNode = head;
            Node* nextNode = head;
            Node* temp = new Node();
            temp->data = dataGiven;
            temp->next = NULL;
            int iterator = 2;
            while (iterator < lineGiven)
            {
                prevNode = prevNode->next;
                nextNode = nextNode->next;
                iterator++;
            }
            nextNode = nextNode->next;
            prevNode->next = temp;
            temp->next = nextNode;
            lines_count++;
            Undo insertedInBetween;
            insertedInBetween.line_num = lineGiven;
            insertedInBetween.cmd_num = 6;
            undoStack.push(insertedInBetween);
        }
    }

    void Textreplace(string givendata, int givenline)
    {
        Undo linereplaced;
        if (lines_count < givenline)
        {
            cout << "Exceed number of lines" << endl;
        }
        else if (givenline == 0)
        {
            cout << "No line 0 exist" << endl;
        }
        else if (lines_count >= givenline)
        {
            Node* temp = head;
            int gotoline = 1;
            while (gotoline < givenline)
            {
                temp = temp->next;
                gotoline++;
            }
            string backup = temp->data;
            temp->data = givendata;
            linereplaced.line_num = givenline;
            linereplaced.text = backup;
            linereplaced.cmd_num = 4;
            undoStack.push(linereplaced);
        }
    }

    void insertfurther(string datagiven, int linegiven)
    {
        Undo insertedfurtheraway;
        insertedfurtheraway.line_num = 0;
        insertedfurtheraway.cmd_num = 9;
        if (head == NULL)
        {
            while (lines_count < linegiven - 1)
            {
                addTotailwhatever("\n");
                insertedfurtheraway.line_num++;
            }
            addTotailwhatever(datagiven);
        }
        else {
            while (lines_count < linegiven - 1)
            {
                addTotailwhatever("\n");
                insertedfurtheraway.line_num++;
            }
            addTotailwhatever(datagiven);
        }
        undoStack.push(insertedfurtheraway);
    }

    void moveNtoM(int nLineGiven, int mLineGiven) {      //function used to Move line N into line M
        if (nLineGiven == 1)
        {
            string headText = head->data;
            headdelete();
            insertTextInBetween(headText, mLineGiven);
        }
        else
        {
            Node* temp = head;
            int iterator = 1;
            while (iterator < nLineGiven)
            {
                temp = temp->next;
                iterator++;
            }
            string dataSaved = temp->data;
            deleteLine(nLineGiven);
            insertTextInBetween(dataSaved, mLineGiven);
        }
        Undo moveHeadToM;
        moveHeadToM.cmd_num = 2;
        moveHeadToM.nline = nLineGiven;
        moveHeadToM.mline = mLineGiven;
        undoStack.push(moveHeadToM);
    }

    void deleteLine(int linegiven) {
        if (head == NULL)
        {
            cout << "No line to be deleted" << endl;
        }
        else if (head == tail) {
            Node* t = head;
            delete(t);
            head = NULL;
            tail = NULL;
            lines_count--;
        }
        else if (linegiven == 0) {
            cout << "No line 0" << endl;
        }
        else if (linegiven == 1) {
            string backup = head->data;
            Node* temp = head;
            Node* nodenext = head->next;
            head = nodenext;
            delete(temp);
            lines_count--;
            Undo removehead;
            removehead.text = backup;
            removehead.line_num = 1;
            removehead.cmd_num = 12;
            undoStack.push(removehead);
        }
        else if (linegiven == lines_count) {
            Node* temp = head;
            Undo deletedLine;
            deletedLine.cmd_num = 11;
            while (temp->next != NULL && temp->next->next != NULL)
            {
                temp = temp->next;
            }
            tail = temp;
            string backup = temp->next->data;
            delete temp->next;
            temp->next = NULL;
            lines_count--;
            deletedLine.text = backup;
            deletedLine.line_num = linegiven;
            undoStack.push(deletedLine);

        }
        else if (linegiven > lines_count)
        {
            cout << "Line is larger." << endl;
        }
        else if (linegiven < lines_count)
        {
            Undo deletedLine;
            deletedLine.cmd_num = 10;
            Node* prevNode = head;
            Node* nextNode = head;
            Node* temp = head;
            int iterator = 2;
            while (iterator < linegiven)
            {
                prevNode = prevNode->next;
                nextNode = nextNode->next;
                iterator++;
            }
            nextNode = nextNode->next;
            temp = nextNode;
            nextNode = nextNode->next;
            prevNode->next = nextNode;
            string backup = temp->data;
            delete(temp);
            lines_count--;
            deletedLine.text = backup;
            deletedLine.line_num = linegiven;
            undoStack.push(deletedLine);
        }
    }

    void undo()
    {                        //function used to undo the last action taken
        Undo temp = undoStack.top();
        if (temp.cmd_num == 1)
        {
            cout << "Added To head, removing from head..." << endl;
            headdelete();
            undoStack.pop();
        }
        else if (temp.cmd_num == 2)
        {
            cout << "Moved M to N, moving N to M" << endl;
            moveNtoM(temp.mline, temp.nline);
            undoStack.pop();
        }
        else if (temp.cmd_num == 3)
        {
            cout << "Deleted head, replacing head..." << endl;;
            addtohead(temp.text);
            undoStack.pop();
        }
        else if (temp.cmd_num == 4)
        {
            cout << "Replaced line, replacing again..." << endl;
            Textreplace(temp.text, temp.line_num);
            undoStack.pop();
        }
        else if (temp.cmd_num == 5)
        {
            cout << "Inserted to Head, removing from head..." << endl;
            headdelete();
            undoStack.pop();
        }
        else if (temp.cmd_num == 6)
        {
            cout << "Inserted in between, removing that line..." << endl;
            deleteLine(temp.line_num);
            undoStack.pop();
        }
        else if (temp.cmd_num == 7)
        {
            cout << "Deleted Tail, inserting again..." << endl;
            addToTail(temp.text);
            undoStack.pop();
        }
        else if (temp.cmd_num == 8)
        {
            cout << "Added to tail, removing from tail..." << endl;
            Taildelete();
            undoStack.pop();
        }
        else if (temp.cmd_num == 9)
        {
            int whatever = temp.line_num;
            while (whatever >= 0) {
                deletetailwhatever();
                whatever--;
            }
            undoStack.pop();
        }
        else if (temp.cmd_num == 10)
        {
            cout << "Line deleted, inserting again..." << endl;
            insertTextInBetween(temp.text, temp.line_num);
            undoStack.pop();
        }
        else if (temp.cmd_num == 11)
        {
            cout << "Last line deleted, inserting again..." << endl;
            addToTail(temp.text);
            undoStack.pop();
        }
        else if (temp.cmd_num == 12)
        {
            cout << "First line deleted, inserting again..." << endl;
            addtohead(temp.text);
            undoStack.pop();
        }
    }

    void Check_File()                      //function used to open a file from the same folder this cpp file is in
    {
        ifstream myfile;
        string fileName;
        cout << "Enter the file name : ";
        cin >> fileName;
        fileName += ".txt";

        myfile.open(fileName);
        string s;

        while (getline(myfile, s))
        {
            addToTail(s);
        }

        myfile.close();
    }

    void Print()                   //function used to print the whole linked list
    {
        Node* temp = head;
        int linePrinted = 1;
        int pagePrinted = 2;

        if (head == NULL)
        {
            cout << "-------------------Nothing is present---------------------------\n" << endl;
        }
        else
        {
            while (temp != NULL)
            {
                if (linePrinted == 1)
                {
                    cout << "-------------------Page " << "1" << "-------------------\n";
                }
                else if ((linePrinted - 1) % 10 == 0)
                {
                    cout << "-------------------Page " << pagePrinted << "-------------------\n";
                    pagePrinted++;
                }
                cout << linePrinted << ") " << temp->data << endl;
                temp = temp->next;
                linePrinted++;
            }
        }
    }


    void Save_Data()
    {
        ofstream outfile;
        Node* temp = head;
        int linePrinted = 1;
        string filename;

        cout << "Enter the file name : ";
        cin >> filename;
        filename += ".txt";

        outfile.open(filename, ios_base::app);

        while (temp != NULL)
        {
            outfile << temp->data;
            temp = temp->next;
            linePrinted++;
        }
        outfile.flush();
        outfile.close();
    }
};

int main(int argc, char const* argv[])
{
    linked_list ob1;
}
