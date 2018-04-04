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

bool is_file_exist(string fileName)
{
	ifstream infile(fileName);
	return infile.good();
}



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
	int ID = atoi(accID.c_str());
	if (is_file_exist(to_string(ID) + ".txt"))
	{
		Account targetAccount(ID);
		targetAccount.Deposit(stod(value)*100);

		cout << "New balance of account " << targetAccount.GetID() << " under the name " << targetAccount.GetName() << " is £";
		printf("%.2f\n", targetAccount.GetBalance());
		return 0;
	}
	else 
	{
		cout << "fatal: Account does not exist";
		return 0;
	}

	return 0;
}



int RunWithdraw(string accID, string value) {
	if (value == "")
		value = "0";
	if (accID == "")
	{
		cout << "fatal: Account ID not specified";
		return 1;
	}
	int ID = atoi(accID.c_str());
	if (is_file_exist(to_string(ID) + ".txt"))
	{
		Account targetAccount(ID);
		targetAccount.Withdraw(stod(value) * 100);

		cout << "New balance of account " << targetAccount.GetID() << " under the name " << targetAccount.GetName() << " is £";
		printf("%.2f\n", targetAccount.GetBalance());
		return 0;
	}
	else
	{
		cout << "fatal: Account does not exist";
		return 0;
	}

	return 0;
}



int RunTransfer(string fromID, string toID, string value) {
	if (value == "")
		value = "0";
	if (fromID == "")
	{
		cout << "fatal: Sender Account ID not specified";
		return 1;
	}
	if (toID == "")
	{
		cout << "fatal: Receiver Account ID not specified";
		return 1;
	}

	int sendID = atoi(fromID.c_str());
	int receiveID = atoi(toID.c_str());
	if (!is_file_exist(to_string(sendID) + ".txt"))
	{
		cout << "fatal: Sender Account does not exist";
		return 0;
	}
	if (!is_file_exist(to_string(receiveID) + ".txt"))
	{
		cout << "fatal: Receiver Account does not exist";
		return 0;
	}

	Account senderAccount(sendID);
	Account receiverAccount(receiveID);

	if (senderAccount.Withdraw(stod(value) * 100) == 0)
		receiverAccount.Deposit(stod(value) * 100);
	else
		cout << "Sender account does not have the funds requires to complete this transaction" << endl;

	cout << "Balance of account " << senderAccount.GetID() << " under the name " << senderAccount.GetName() << " is £";
	printf("%.2f\n", senderAccount.GetBalance());

	cout << "Balance of account " << receiverAccount.GetID() << " under the name " << receiverAccount.GetName() << " is £";
	printf("%.2f\n", receiverAccount.GetBalance());
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



int RunClose(string accID, string accName) {
	if (accID == "")
	{
		cout << "fatal: Account ID not specified";
		return 1;
	}

	if (is_file_exist(accID + ".txt"))
	{
		Account targetAccount( atoi(accID.c_str()) );

		if (accName == targetAccount.GetName())
		{
			string temp = accID + ".txt";
			remove( temp.c_str() );
			cout << "Account " << targetAccount.GetID() << " under the name " << targetAccount.GetName() << " has been closed.\n";
			return 0;
		}
		else
		{
			cout << "Name entered must mach name of account in order to confirm account closure.\n";
			return 0;
		}
	}
	else
	{
		cout << "fatal: Account does not exist";
		return 0;
	}
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
		else if (command == "transfer") {
			string sendID = "";
			string receiveID = "";
			string Value = "";

			for (int i = 2; i < argc; i++) {
				string param = argv[i];
				if (param == "-h" or param == "--help")
				{
					cout << "usage: Banking deposit [<options>] \n\n\t-s, --sender\t\tSender Account ID \n\t-r, --receiver\t\tReceiver Account ID \n\t-v, --value\t\tamount to be deposited in Account \n" << endl;
					return 0;
				}
				else if (param == "-s" or param == "--sender")
				{
					if (i < argc - 1)
						if (argv[i + 1][0] != '-')
							sendID = argv[i + 1];
				}
				else if (param == "-r" or param == "--receiver")
				{
					if (i < argc - 1)
						if (argv[i + 1][0] != '-')
							receiveID = argv[i + 1];
				}
				else if (param == "-v" or param == "--value")
				{
					if (i < argc - 1)
						if (argv[i + 1][0] != '-')
							Value = argv[i + 1];
				}
			}

			RunTransfer(sendID, receiveID, Value);
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
		else if (command == "withdraw") {
			string AccID = "";
			string Value = "";

			for (int i = 2; i < argc; i++) {
				string param = argv[i];
				if (param == "-h" or param == "--help")
				{
					cout << "usage: Banking withdraw [<options>] \n\n\t-i, --id\t\tAccount ID \n\t-v, --value\t\tamount to be withdrawn from Account \n" << endl;
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

			RunWithdraw(AccID, Value);
		}
		else if (command == "close") {
			string AccName = "";
			string AccID = "";

			for (int i = 2; i < argc; i++) {
				string param = argv[i];
				if (param == "-h" or param == "--help")
				{
					cout << "usage: Banking close [<options>] \n\n\t-i, --id\t\tAccount ID \n\t-n, --name\t\tName of Account \n" << endl;
					return 0;
				}
				else if (param == "-n" or param == "--name")
				{
					if (i < argc - 1)
						if (argv[i + 1][0] != '-')
							AccName = argv[i + 1];
				}
				else if (param == "-i" or param == "--id")
				{
					if (i < argc - 1)
						if (argv[i + 1][0] != '-')
							AccID = argv[i + 1];
				}
			}

			RunClose(AccID, AccName);
		}
		else
		{
			cout << "\"" << command << "\" is not a recognised command." << endl;
			RunHelp();
		}

		return 0;
	}
}