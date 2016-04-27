#include "NetworkAndMessage.h"
#include <stdlib.h>

NetworkAndMessage::NetworkAndMessage()
{
    //ctor
    buildQueue(20);

    city *LA = new city();
    city *Phoenix = new city();
    city *Denver = new city();
    city *Dallas = new city();
    city *StLousi = new city();
    city *Chicago = new city();
    city *Atlanta = new city();
    city *DC = new city();
    city *NY = new city();
    city *Boston = new city();

    LA->Name = "Los Angeles";
    Phoenix->Name = "Phoenix";
    Denver->Name = "Denver";
    Dallas->Name = "Dallas";
    StLousi->Name = "St. Louis";
    Chicago->Name = "Chicago";
    Atlanta->Name = "Atlanta";
    DC->Name = "Washington, D.C.";
    NY->Name = "New York";
    Boston->Name = "Boston";

    LA->next = Phoenix;
    Phoenix->next = Denver;
    Denver->next = Dallas;
    Dallas->next = StLousi;
    StLousi->next = Chicago;
    Chicago->next = Atlanta;
    Atlanta->next = DC;
    DC->next = NY;
    NY->next = Boston;
    Boston->next = NULL;

    LA->previous = NULL;
    Phoenix->previous = LA;
    Denver->previous = Phoenix;
    Dallas->previous = Denver;
    StLousi->previous = Dallas;
    Chicago->previous = StLousi;
    Atlanta->previous = Chicago;
    DC->previous = Atlanta;
    NY->previous = DC;
    Boston->previous = NY;

    LA->ndist = 2;
    Phoenix->ndist = 3;
    Denver->ndist = 4;
    Dallas->ndist = 4;
    StLousi->ndist = 1;
    Chicago->ndist = 4;
    Atlanta->ndist = 4;
    DC->ndist = 1;
    NY->ndist = 1;
    Boston->ndist = 0;

    LA->pdist = 0;
    Phoenix->pdist = 2;
    Denver->pdist = 3;
    Dallas->pdist = 4;
    StLousi->pdist = 4;
    Chicago->pdist = 1;
    Atlanta->pdist = 4;
    DC->pdist = 4;
    NY->pdist = 1;
    Boston->pdist = 1;

    head = LA;
    tail = Boston;
    current = LA;
    currPoints = 24;
}

NetworkAndMessage::~NetworkAndMessage()
{
    //dtor
}

void NetworkAndMessage::printNetwork(){
    city *temp;
    temp = head;
    cout<<"===CURRENT PATH==="<<endl;
    cout<<"NULL <- ";
    while(temp->next!=NULL){
        cout<<temp->Name<<" <-> ";
        temp = temp->next;
    }
    cout<<temp->Name<<" -> "<<"NULL"<<endl;
    cout<<"=================="<<endl;
}

int NetworkAndMessage::distance(string destination){
    city *temp;
    temp = current;
    int sum = 0;
    if(destination == temp->Name){
        return 0;
    }
    while(temp->Name != destination){
        sum = sum + temp->ndist;
        temp = temp->next;
        if(temp==NULL){
            temp = current;
            sum = 0;
            break;
        }
    }
    cout<<sum<<endl;
    if(sum!=0){
        return sum;
    }
    sum = 0;
    while(temp->Name != destination){
        sum = sum + temp->pdist;
        temp = temp->previous;
        if(temp->previous == NULL){
            temp = current;
            break;
        }
    }
    if(sum!=0){
        return sum;
    }
    return 0;

}

void NetworkAndMessage::printCurrent(){
    cout<<current->Name<<endl;
}

bool NetworkAndMessage::searchNetwork(string cityN){
    city *temp;
    temp = head;
    while(temp->Name!=cityN){
        temp = temp->next;
        if(temp == NULL){
            return false;
        }
    }
    return true;
}


///below are functions for the queue


void NetworkAndMessage::buildQueue(int qs){
    queueSize = qs;
    arrayQueue = new string[queueSize];
    queueHead = 0;
    queueTail = 0;
    queueCount = 0;
}

void NetworkAndMessage::enqueue(string word){
    if(queueIsFull() == false){
        arrayQueue[queueTail] = word;
        queueTail++;
        if(queueTail==queueSize){
            queueTail = 0;
        }
        bool check = queueIsFull();
        if(check == false){
            cout<<"E: "<<word<<endl;
            cout<<"H: "<<queueHead<<endl;
            cout<<"T: "<<queueTail<<endl;
        }else{
            cout<<"Message length reached"<<endl;
        }
        queueCount = queueCount + 1;
    }else{
        cout<<"Message length reached."<<endl;
    }
}

void NetworkAndMessage::deleteQueue(){
    string delWord = "check";
    while(queueIsEmpty() == false){
        delWord = arrayQueue[queueHead];
        queueCount--;
        queueHead++;
        if(queueHead == queueSize){
            queueHead = 0;
        }
    }
}

void NetworkAndMessage::editqueue(int index){
    string old = arrayQueue[index];
    string newWord;
    string choice;
    bool done = false;
    while(done==false){
        cout<<"Enter your new word"<<endl;
        cin>>newWord;
        arrayQueue[index]= newWord;
        printQueue();
        cout<<"Is this the message you wish to send?Y/N"<<endl;
        cin>>choice;
        if(choice=="Y" or choice=="y"){
            done = true;
        }
    }
}

void NetworkAndMessage::printQueue(){
    if(queueCount != 0){
        int itt = queueHead;
        int counter = 0;
        while(counter != queueCount){
            cout<<arrayQueue[itt]<<" ";
            itt++;
            counter++;
            if(itt == queueSize){
                itt = 0;
            }
        }
        cout<<""<<endl;
    }else{
        cout<<"Empty"<<endl;
    }
}

void NetworkAndMessage::printQueueWithIndex(){
    if(queueCount != 0){
        int itt = queueHead;
        int counter = 0;
        while(counter != queueCount){
            cout<<itt<<": "<<arrayQueue[itt]<<endl;
            itt++;
            counter++;
            if(itt == queueSize){
                itt = 0;
            }
        }
    }else{
        cout<<"Empty"<<endl;
    }
}

void NetworkAndMessage::dataLoss(int x){
    int y;
    if(x%2==0){
        y = x/2;
    }else{
        y = x/2 +1;
    }
    for(int i = 0;i<y;i++){
        int r = rand() % queueCount;
        int index = queueHead+r;
        if(index >=queueSize){
            index = index-queueSize;
        }
        arrayQueue[index] = "&$#*@%";

    }

}

bool NetworkAndMessage::queueIsFull(){
    if(queueCount == queueSize){

        return true;
    }
    return false;
}

bool NetworkAndMessage::queueIsEmpty(){
    if(queueCount == 0){
        return true;
    }
    return false;
}

void NetworkAndMessage::sendMessage(string destCity){
    string word;
    city *temp = new city;
    temp = current;
    int itt = 0;
    int x = queueHead;
    bool check= true;
    while(temp->Name!=destCity){
        temp = temp->next;
        if(temp==NULL){
            check=false;
            break;
        }
    }
    cout<<"test"<<endl;
    if(check==true){
        while(itt!=queueCount){
            temp = current;
            word = arrayQueue[x];
            x++;
            while(temp->Name!= destCity){
                temp->message = word;
                cout<<temp->Name<<" received "<<temp->message<<endl;
                temp->message = "";
                temp = temp->next;
            }
            temp->message = word;
            cout<<temp->Name<<" received "<<temp->message<<endl;
            temp->message = "";
            itt++;
        }
    }else{
        while(itt!=queueCount){
            temp = current;
            word = arrayQueue[x];
            x++;
            while(temp->Name!= destCity){
                temp->message = word;
                cout<<temp->Name<<" received "<<temp->message<<endl;
                temp->message = "";
                temp = temp->previous;
            }
            temp->message = word;
            cout<<temp->Name<<" received "<<temp->message<<endl;
            temp->message = "";
            itt++;
        }
    }
    current = temp;
    temp = NULL;
    delete temp;
}

///Points functions

bool NetworkAndMessage::addition(){
    int a = rand() %100 + 1;
    int b = rand() %100 + 1;
    int c = a+b;
    int answer;
    cout<<a<<"+"<<b<<"=";
    cin>>answer;
    if(answer==c){
        return true;
    }else{
        return false;
    }
}

bool NetworkAndMessage::subtraction(){
    int a = rand() %100 + 1;
    int b = rand() %100 + 1;
    int c = a-b;
    int answer;
    cout<<a<<"-"<<b<<"=";
    cin>>answer;
    if(answer==c){
        return true;
    }else{
        return false;
    }
}

void NetworkAndMessage::easyMath(int x){
    bool problems = true;
    int number;
    number = x;
    int right = 0;
    bool correct;
    int wrong = 0;
    while(problems==true and number!=0){
        int r = rand()%10;
        if(r%2 == 0){
            correct=addition();
            number--;
            if(correct==true){
                cout<<"Correct!"<<endl;
                right++;
            }else{
                wrong++;
                cout<<"Incorrect"<<endl;
            }
        }else{
            correct=subtraction();
            number--;
            if(correct==true){
                cout<<"Correct!"<<endl;
                right++;
            }else{
                wrong++;
                cout<<"Incorrect"<<endl;
            }
        }
    }
    cout<<"Right: "<<right<<endl;
    cout<<"Total: "<<right+wrong<<endl;
    currPoints = currPoints+right;
    if(wrong==0){
        currPoints=currPoints+2;
        cout<<"2 extra points for no wrong answers!"<<endl;
    }
}

bool NetworkAndMessage::multiplication(){
    int a = rand()%20 + 1;
    int b = rand()%20 + 1;
    int c = a*b;
    int answer;
    cout<<a<<"*"<<b<<"=";
    cin>>answer;
    if(answer==c){
        return true;
    }else{
        return false;
    }
}

bool NetworkAndMessage::divisoin(){
    int a = (rand()%20+30);
    int b = (rand()%20+1)*3;
    int c = a*b;
    int answer;
    cout<<c<<"/"<<b<<"=";
    cin>>answer;
    if(answer==a){
        return true;
    }else{
        return false;
    }
}

void NetworkAndMessage::mediumMath(int x){
    bool problems = true;
    bool correct;
    int number;
    number = x;
    int right = 0;
    int wrong = 0;
    while(problems==true and number!=0){
        int r = rand()%10;
        if(r%2 == 0){
            correct=multiplication();
            number--;
            if(correct==true){
                cout<<"Correct!"<<endl;
                right++;
            }else{
                wrong++;
                cout<<"Incorrect"<<endl;
            }
        }else{
            correct=divisoin();
            number--;
            if(correct==true){
                cout<<"Correct!"<<endl;
                right++;
            }else{
                wrong++;
                cout<<"Incorrect"<<endl;
            }
        }
    }
    cout<<"Right: "<<right<<endl;
    cout<<"Total: "<<right+wrong<<endl;
    currPoints = currPoints+(2*right);
    if(wrong==0){
        currPoints=currPoints+4;
        cout<<"4 extra points for no wrong answers!"<<endl;
    }
}

bool NetworkAndMessage::solveForX(){
    int x = rand()%20;
    int a = rand()%15+1;
    int b = rand()%10+1;
    int c = a*x + b;
    int answer;
    cout<<a<<"x+"<<b<<"="<<c<<endl;
    cout<<"x=";
    cin>>answer;
    if(answer==x){
        return true;
    }else{
        return false;
    }
}

void NetworkAndMessage::hardMath(int x){
    bool problems = true;
    bool correct;
    int number;
    number = x;
    int right = 0;
    int wrong = 0;
    if(number==0){
        cout<<"Well that was uneventful"<<endl;
    }
    while(problems==true and number!=0){
        correct=solveForX();
        number--;
        if(correct==true){
            cout<<"Correct!"<<endl;
            right++;
        }else{
            wrong++;
            cout<<"Incorrect"<<endl;
        }
    }
    cout<<"Right: "<<right<<endl;
    cout<<"Total: "<<right+wrong<<endl;
    currPoints = currPoints+(4*right);
    if(wrong==0){
        currPoints=currPoints+6;
        cout<<"6 extra points for no wrong answers!"<<endl;
    }
}
