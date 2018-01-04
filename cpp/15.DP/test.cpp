#include "Bank.h"

#include <iostream>
#include <string>


int main()
{   
    int cont = 1;                   // trigger to stop loop
    int option; 
    
    Bank& bank = Bank::CreateObj();

    while (cont)
    {
        cout << "                                     " << endl;
        cout << "Choose option:                       " << endl;
        cout << "1: create Personal Saving account    " << endl;
        cout << "2: create Family account             " << endl;
        cout << "3: create Stock Exchange account     " << endl;
        cout << "4: Invest In Stock Exchange Accounts " << endl;
        cout << "5: Bonus To Family Accounts          " << endl;
        cout << "6: Invite Saving Account Owners      " << endl;
        cout << "Any another number - stop            " << endl;

        cin >> option;
        switch (option)
        {
            case 1:
                bank.OpenAccount("PersonalSaving");
            break;
            case 2:
                bank.OpenAccount("Family");
            break;
            case 3:
                bank.OpenAccount("StockExchange");
            break;
            case 4:
                bank.InvestInStockExchangeAccounts();
            break;
            case 5:
                bank.BonusToFamilyAccounts();
            break;
            case 6:
                bank.InviteSavingAccountOwners();
            break;
			default:
                cont = 0;
            break;
		}
	}
}


