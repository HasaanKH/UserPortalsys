#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class validation
{
public:
    bool password(string pStr)
    {
        if (pStr.length() < 8)
        {
            return false;
        }

        int specialcharcount = 0;
        for (char i : pStr)
        {
            cout << i;
            if (i == '!' || i == '%' || i == '*')
            {
                specialcharcount++;
            }
        }

        if (specialcharcount != 1)
        {
            return false;
        }

        for (char i : pStr)
        {
            if (isupper(i))
            {
                break;
            }
        }

        return true;
    }
};

class fileObject
{
public:
    void write(string u, string p)
    {
        fstream myfile("userData.txt");
        myfile << u << "," << p << "\n";
        myfile.close();
    }

    bool usernameSearch(string u)
    {
        string line;
        fstream myfile("userData.txt");
        while (getline(myfile, line))
        {
            string user;
            int pos = line.find(',');
            user = line.substr(0, pos);
            if (u == user)
            {
                return true;
            }
        }
        return false;
    }

    bool search(string u, string p)
    {
        string line;
        ifstream myfile("userData.txt");
        while (getline(myfile, line))
        {
            string user;
            string password;
            int pos = line.find(',');
            user = line.substr(0, pos);
            password = line.substr(pos + 1, line.length() - user.length() + 1);
            if (u == user)
            {
                if (p == password)
                {
                    return true;
                }
            }
        }

        return false;
    }
};

class userDetail
{
public:
    userDetail()
    {
        cout << "Do you have an account, Y/N: ";
        char accountConfirmation;
        cin >> accountConfirmation;

        fileObject fileObjectInstance;
        validation validationInstance;

        if (accountConfirmation == 'Y')
        {
            bool temp;
            do
            {
                string username;
                string password;
                cout << "\n Enter username: ";
                cin >> username;
                cout << "\n Enter password: ";
                cin >> password;
                temp = fileObjectInstance.search(username, password);
            } while (!(temp));
            cout << "Successfully logged in!";
        }

        else if (accountConfirmation == 'N')
        {
            string username;
            string password;
            bool usernameValid = 1;
            bool passwordValid = 1;

            cout << "\n create a username: ";
            while (usernameValid)
            {
                cout << "\n username already taken! create a username: ";
                cin >> username;
                usernameValid = (fileObjectInstance.usernameSearch(username));
            }

            while (passwordValid)
            {
                cout << "\n Create a password, must be atleast 8 characters, have atleast 1 capital and 1 special character (!, %, *): ";
                cin >> password;
                passwordValid = !(validationInstance.password(password));
                cout << passwordValid;
            }

            fileObjectInstance.write(username, password);
            cout << "New account created!";
        }

        else
        {
            cout << "idiot";
        }
    }
};

int main()
{
    userDetail user;
    return 0;
}
