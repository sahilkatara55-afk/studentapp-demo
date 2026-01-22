#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Account {
    int acno;
    char name[50];
    double deposit;

public:
    void create_account() {
        cout << "\nEnter The account No. : ";
        cin >> acno;
        cout << "Enter The Name of The account Holder : ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Initial amount (>=500 for Saving and >=1000 for current) : ";
        cin >> deposit;
        cout << "\nAccount Created Successfully...";
    }

    void show_account() const {
        cout << "\nAccount No. : " << acno;
        cout << "\nAccount Holder Name : " << name;
        cout << "\nBalance amount : " << deposit;
    }

    void draw(int x) { deposit -= x; }
    void add(int x) { deposit += x; }
    int get_acno() const { return acno; }
    double get_deposit() const { return deposit; }
};

// --- Function Prototypes ---
void write_account();
void display_sp(int);
void display_all();
void delete_account(int);
void deposit_withdraw(int, int);
void transfer_money(int, int, int);

// --- File Operations ---

void write_account() {
    Account ac;
    ofstream outFile("bank.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(Account));
    outFile.close();
}

void display_sp(int n) {
    Account ac;
    bool flag = false;
    ifstream inFile("bank.dat", ios::binary);
    if (!inFile) { cout << "File could not be opened!!"; return; }
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.get_acno() == n) {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (!flag) cout << "\nAccount number does not exist";
}

void display_all() {
    Account ac;
    ifstream inFile("bank.dat", ios::binary);
    if (!inFile) { cout << "File could not be opened!!"; return; }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME                Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        cout << setw(10) << ac.get_acno() << setw(20) << " " << setw(10) << ac.get_deposit() << endl;
    }
    inFile.close();
}

void deposit_withdraw(int n, int option) {
    int amt;
    bool found = false;
    Account ac;
    fstream File("bank.dat", ios::binary | ios::in | ios::out);
    if (!File) { cout << "File could not be opened!!"; return; }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*>(&ac), sizeof(Account));
        if (ac.get_acno() == n) {
            ac.show_account();
            if (option == 1) {
                cout << "\n\nEnter The amount to be deposited: ";
                cin >> amt;
                ac.add(amt);
            }
            if (option == 2) {
                cout << "\n\nEnter The amount to be withdraw: ";
                cin >> amt;
                if (amt > ac.get_deposit()) cout << "Insufficient balance";
                else ac.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(Account));
            cout << "\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (!found) cout << "\n\n Record Not Found ";
}

void transfer_money(int source, int dest, int amt) {
    Account ac;
    bool s_found = false, d_found = false;
    fstream File("bank.dat", ios::binary | ios::in | ios::out);

    // This is a simplified logic: 1. Subtract from source 2. Add to dest
    // In a real system, these would happen inside a transaction.
    deposit_withdraw(source, 2); // Withdraw logic
    deposit_withdraw(dest, 1);   // Deposit logic
}

void delete_account(int n) {
    Account ac;
    ifstream inFile("bank.dat", ios::binary);
    ofstream outFile("Temp.dat", ios::binary);
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Account))) {
        if (ac.get_acno() != n) {
            outFile.write(reinterpret_cast<char*>(&ac), sizeof(Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("bank.dat");
    rename("Temp.dat", "bank.dat");
    cout << "\n\tRecord Deleted ..";
}

int main() {
    int ch, num;
    do {
        cout << "\n\n\tMAIN MENU";
        cout << "\n\t01. NEW ACCOUNT (Admin)";
        cout << "\n\t02. DEPOSIT AMOUNT";
        cout << "\n\t03. WITHDRAW AMOUNT";
        cout << "\n\t04. BALANCE ENQUIRY";
        cout << "\n\t05. ALL ACCOUNT HOLDER LIST (Admin)";
        cout << "\n\t06. CLOSE AN ACCOUNT (Admin)";
        cout << "\n\t07. TRANSFER MONEY";
        cout << "\n\t08. EXIT";
        cout << "\n\tSelect Your Option (1-8): ";
        cin >> ch;
        switch (ch) {
            case 1: write_account(); break;
            case 2: cout << "\nEnter Account No: "; cin >> num; deposit_withdraw(num, 1); break;
            case 3: cout << "\nEnter Account No: "; cin >> num; deposit_withdraw(num, 2); break;
            case 4: cout << "\nEnter Account No: "; cin >> num; display_sp(num); break;
            case 5: display_all(); break;
            case 6: cout << "\nEnter Account No: "; cin >> num; delete_account(num); break;
            case 7: 
                int s, d, a;
                cout << "\nSource A/c: "; cin >> s;
                cout << "Dest A/c: "; cin >> d;
                transfer_money(s, d, a); 
                break;
        }
    } while (ch != 8);
    return 0;
}