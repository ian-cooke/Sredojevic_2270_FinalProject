#include <iostream>
#include <string>
#include "NetworkAndMessage.h"
#include <sstream>

using namespace std;

int main()
{
    NetworkAndMessage running;

    int select = 0;
    bool start = true;
    while(start == true)
    {
        cout<<"~~~~~Main Menu~~~~~"<<endl;
        cout<<"1. Send message to city"<<endl;
        cout<<"2. Edit message"<<endl;
        cout<<"3. Print Message, Location and Sending Points"<<endl;
        cout<<"4. Play for Points"<<endl;
        cout<<"5. Quit"<<endl;
        cin>>select;


        if(select==1){
            int newSelect;
            string destCity;
            if(running.queueIsEmpty()==true){
                string words;
                cout<<"Message: ";
                cin.ignore();
                getline(cin,words);
                istringstream Sent(words);
                string words2;
                while(Sent >> words2){
                    running.enqueue(words2);
                }
            }else{
                running.printQueue();
                cout<<"1. Send current message"<<endl;
                cout<<"2. Send new message"<<endl;
                cin>>newSelect;

                if(newSelect==2){
                    running.deleteQueue();
                    string words;
                    cout<<"Message: ";
                    cin.ignore();
                    getline(cin,words);
                    istringstream Sent(words);
                    string words2;
                    while(Sent >> words2){
                        running.enqueue(words2);
                    }
                }
            }
            running.printNetwork();
            cout<<"Enter a destination city:"<<endl;
            if(newSelect==1){
                cin.ignore();
            }
            getline(cin, destCity);
            bool exist = running.searchNetwork(destCity);
            if(exist==true){
                int dist = running.distance(destCity);
                if(running.currPoints!=0){
                    if(dist > running.currPoints){
                        string check;
                        cout<<"You do not have enough points to guarantee 100% send rate. Are you sure you would like to send this message? If you do, you may lose parts of your message."<<endl;
                        cout<<"Y/N"<<endl;
                        cin>>check;
                        if(check=="y" or check=="Y"){
                            running.dataLoss(dist-running.currPoints);
                            running.sendMessage(destCity);
                            running.currPoints = 0;
                        }
                    }else if(dist == 0){
                        cout<<"You are already here. You dont need to send the message here"<<endl;
                        cout<<""<<endl;
                    }else{
                        running.sendMessage(destCity);
                        running.currPoints = running.currPoints - dist;
                    }
                }else{
                    cout<<"You do not have enough points to send a message"<<endl;
                    cout<<""<<endl;
                }
            }else{
                cout<<"That city does not exist"<<endl;
                cout<<""<<endl;
            }
        }

        if(select==2){
            int choice;
            cout<<"1. Create new message"<<endl;
            cout<<"2. Alter current message"<<endl;
            cin>>choice;
            cout<<""<<endl;

            if(choice==1){
                running.deleteQueue();
                string words;
                cout<<"Message: ";
                cin.ignore();
                getline(cin,words);
                istringstream Sent(words);
                string words2;
                while(Sent >> words2){
                    running.enqueue(words2);
                }
            }

            if(choice==2){
                int index;
                string word;
                running.printQueueWithIndex();
                cout<<"Which index would you like to edit?"<<endl;
                cin>>index;
                running.editqueue(index);
            }
        }

        if(select==3){
            cout<<"Current Message: ";
            running.printQueue();
            cout<<"Current Sending Points: "<< running.currPoints<<endl;
            cout<<"Current Location: ";
            running.printCurrent();
        }

        if(select==4){
            int choice;
            int y;
            cout<<"1. Easy Math(1 point for each correct answer)"<<endl;
            cout<<"2. Medium Math(2 points for each correct answer)"<<endl;
            cout<<"3. Hard Math(4 points for each correct answer)"<<endl;
            cin>>choice;

            cout<<"How many problems would you like to do?"<<endl;
            cin>>y;

            if(choice==1){
                running.easyMath(y);
            }

            if(choice==2){
                running.mediumMath(y);
            }

            if(choice==3){
                running.hardMath(y);
            }
        }

        if(select==5){
            start= false;
        }
    }
    cout<<"Bye bye, now!"<<endl;
    return 0;
}
