#include <string>

using namespace std;

string get_item();
void select_item();
void cola();
void chips();
void candy();
void display_items();
void input_coins(int cost, string product);
void collect_change(int cost, string product, int total_cents, int added_nickles, int added_dimes, int added_quarters);
struct result 
{
    int nickles_change; 
    int dimes_change; 
    int quarters_change;
};
struct result return_change(int change);
class Denominations
{
    public:
        int nickles=0, dimes=0, quarters=0;
};
Denominations coins;
void adjust_saved_coins(int added_nickles, int added_dimes, int added_quarters);
