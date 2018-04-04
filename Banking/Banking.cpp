// Banking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Account.h"

using namespace std;

vector<Account> accounts;

int RunHelp() {
	cout << "usage: Banking <command>[<args>]";
	return 0;
}



int RunDeposit(string accID, string value) {
	if (value == "")
		value = "0";
	if (accID == "")
	{
		cout << "fatal: Account ID not specified";
		return 1;
	}

	return 0;
}



int RunNew(string accType, string accName) {
	if (accType == "")
		accType = "current";
	if (accName == "")
	{
		cout << "fatal: Account name not specified";
		return 1;
	}

	Account newAccount(accName, accType);
	accounts.push_back(newAccount);

	string fileName = to_string(newAccount.GetID()) + ".txt";
	ofstream myfile (fileName);
	myfile << newAccount.GetID() << endl;
	myfile << newAccount.GetName() << endl;
	myfile << newAccount.GetBalance() << endl;
	myfile << newAccount.GetType();
	myfile.close();

	cout << "account created with ID " << newAccount.GetID() << " under the name " << newAccount.GetName() << " With starting balance of £";
	printf("%.2f\n", newAccount.GetBalance());
	return 0;
}


int main(int argc, char* argv[])
{
	string command;
	
	if (argc < 2)
	{
		return RunHelp();
	}
	else
	{
		command = argv[1];
		if (command == "help") {
			return RunHelp();
		}
		else if (command == "new") {
			string AccName = "";
			string AccType = "";

			for (int i = 2; i < argc; i++) {
				string param = argv[i];
				if (param == "-h" or param == "--help")
				{
					cout << "usage: Banking new [<options>] \n\n\t-n, --name\t\tName of Account \n\t-t, --type\t\tType of Account \n" << endl;
					return 0;
				}
				else if (param == "-n" or param == "--name")
				{
					if (i < argc - 1)
						if (argv[i + 1][0] != '-')
							AccName = argv[i + 1];
				}
				else if (param == "-t" or param == "--type")
				{
					if (i < argc - 1)
						if (argv[i + 1][0] != '-')
							AccType = argv[i + 1];
				}
			}

			RunNew(AccType, AccName);
		}
		else if (command == "deposit") {
			string AccID = "";
			string Value = "";

			for (int i = 2; i < argc; i++) {
				string param = argv[i];
				if (param == "-h" or param == "--help")
				{
					cout << "usage: Banking deposit [<options>] \n\n\t-i, --id\t\tAccount ID \n\t-v, --value\t\tamount to be deposited in Account \n" << endl;
					return 0;
				}
				else if (param == "-i" or param == "--id")
				{
					if (i < argc - 1)
						if (argv[i + 1][0] != '-')
							AccID = argv[i + 1];
				}
				else if (param == "-v" or param == "--value")
				{
					if (i < argc - 1)
						if (argv[i + 1][0] != '-')
							Value = argv[i + 1];
				}
			}

			RunDeposit(AccID, Value);
		}

		return 0;
	}
}