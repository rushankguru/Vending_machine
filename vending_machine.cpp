#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include "vending_machine.h"
using namespace std;


string get_item()
{
    string item;
    cout<<"Press 1 for COLA"<<endl;
    cout<<"Press 2 for CHIPS"<<endl;
    cout<<"Press 3 for CANDY"<<endl;
    cin>>item;

    return item;
}

void select_item()
{
    string input_item;
    int item_num;
    stringstream ss;

    input_item = get_item();
    ss<<input_item;
    ss>>item_num;

    switch(item_num)
    {
        case 1:
            cola();
        
        case 2:
            chips();
        
        case 3:
            candy();

        default:
            cout<<"Invalid entry"<<endl;
            display_items();
    }
}

void cola()
{
    string h;
    cout<<"you have choosen cola, it costs 100 cents"<<endl;
    cout<<"Press any key and then press ENTER to continue"<<endl;
    cin>>h;
    input_coins(100,"cola");
}

void chips()
{
    string h;
    cout<<"you have choosen chips, it costs 50 cents"<<endl;
    cout<<"Press any key and then press ENTER to continue"<<endl;
    cin>>h;
    input_coins(50,"chips");
}

void candy()
{
    string h;
    cout<<"you have choosen candy, it costs 65 cents"<<endl;
    cout<<"Press any key and then press ENTER to continue"<<endl;
    cin>>h;
    input_coins(65,"candy");
}

void display_items()
{
    string start;
    cout<<"WELCOME"<<endl;
    cout<<"cola $1.00 (100 cents)"<<endl;
    cout<<"chips for $0.50 (50 cents)"<<endl;
    cout<<"candy for $0.65 (65 cents)"<<endl;
    cout<<"press any key and then ENTER to start"<<endl;
    cin>>start;
    return select_item();
}

void input_coins(int cost, string product)
{
    string coin;
    int total_cents=0;

    cout<<
    "You can only enter a dime or a nickle or a quarter"<<"\n"<<
    "Enter n for nickle, d for dime and q for quarter"<<"\n"<<
    "Press e for exit"<<"\n"<<endl;
    int added_nickles = 0, added_dimes = 0, added_quarters = 0;
    while(true)
    {
        cout<<"INSERT COIN"<<endl;
        
        cin >> coin;
  
        if (coin=="e")
        {
            cout<<"You pressed exit, collect the coins from coin return tray"<<endl;
            adjust_saved_coins(added_nickles, added_dimes, added_quarters);
            return display_items();
        }

        else if (coin=="n")
        {
            cout<<"You entered a nickle"<<endl;
            total_cents += 5;
            coins.nickles +=1;
            added_nickles += 1;

        }

        else if (coin=="d")
        {
            cout<<"You entered a dime"<<endl;
            total_cents += 10;
            coins.dimes +=1;
            added_dimes +=1;
        }

        else if (coin=="q")
        {
            cout<<"You entered a quarter"<<endl;
            total_cents += 25;
            coins.quarters +=1;
            added_quarters +=1;
        }

        else
        {
            cout<<"your entry is rejected, collect the coins from coin return tray"<<endl;
            adjust_saved_coins(added_nickles, added_dimes, added_quarters);
            input_coins(cost, product);
        }

        cout << "\033[2J\033[1;1H";
        cout<<"you have entered a total "<< total_cents<<" cents"<<endl;

        if (total_cents>=cost)
        {
            break;
        }

    }

    collect_change(cost, product, total_cents, added_nickles, added_dimes, added_quarters);
}

void collect_change(int cost, string product, int total_cents, int added_nickles, int added_dimes, int added_quarters)
{
    int change;
    change  = total_cents - cost;

    struct result s;
    s = return_change(change);

    cout<<"collect your "<<product<<" from dispenser"<<endl;
    cout<<"THANK YOU"<<"\n"<<endl;
    if (change!=0)
    {
        if (s.nickles_change==-1 && s.dimes_change==-1 && s.quarters_change==-1)
        {
            cout<<"Machine cant give change, enter exact value as price"<<endl;
            cout<<"Also do not forget to collect your coins from return tray" <<endl;
            adjust_saved_coins(added_nickles, added_dimes, added_quarters);
            input_coins(cost, product);
        }
        else
        {
            cout<<"Also do not forget to collect "<< s.nickles_change << " nickles, "<< s.dimes_change << " dimes, "<< s.quarters_change <<" quarters from return tray" <<endl;
            adjust_saved_coins(s.nickles_change, s.dimes_change, s.quarters_change);
        }
    }

    display_items();
}

void adjust_saved_coins(int nickles, int dimes, int quarters)
{
    coins.nickles -= nickles;
    coins.dimes -= dimes;
    coins.quarters -= quarters;
}

struct result return_change(int change)
{
    int x,y,z;
    bool there;
    //check available coins
    int nickles = coins.nickles;//5

    int dimes = coins.dimes;//10
    int quarters = coins.quarters;//25

    struct result s;

    for (x=0;x<=nickles;x++)
    {
        for (y=0;y<=dimes;y++)
        {
            for (z=0;z<=quarters;z++)
            {
                if (change  == x*5 + y*10 + z*25)
                {
                    s.nickles_change = x;
                    s.dimes_change = y;
                    s.quarters_change = z;
                    return s;
                }
            }
        }
    }

    s.nickles_change = -1;
    s.dimes_change = -1;
    s.quarters_change = -1;

    return s;
    // change  = x*5 + y*10 + z*25;
}

int main()    
{
    display_items();
}


