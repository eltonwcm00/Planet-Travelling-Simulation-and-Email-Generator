#include <iostream>
#include <ctime>
#include <unistd.h>
#include <fstream>

using namespace std;

string gen_random() {

    string tmp_s, tmp_b, tmp_c, email;

    static const char num[] = "1234567890";
    static const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const char alphaSmall[] = "abcdefghijklmnopqrstuvwxyz";
    static string domain;
    //static const string domain[] = {".net" ".org" ".my"};
    static const char at = '@';

    static const int numSwitch = 3;
    static const char total[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz" "1234567890";


    for (int i = 0; i < 4; ++i)
        tmp_b += alpha[rand() % (sizeof(alpha) - 1)];

    for (int i = 0; i < 4; ++i)
        tmp_s += total[rand() % (sizeof(total) - 1)];

    for (int i = 0; i < 5; ++i)
        tmp_c += num[rand() % (sizeof(num) - 1)];

    switch(rand() % numSwitch) {

        case 0 : domain = ".net";
                 break;

        case 1 : domain = ".org";
                 break;

        case 2 : domain = ".my";
                 break;
    }

    email = tmp_b + tmp_s + tmp_c + at + tmp_s + domain;

    return email;
}

int main(int argc, char *argv[]) {

    time(0);

    string data;
    int index = 0;

    ofstream myfile;
    myfile.open ("setA.txt");

    for (int i=0;i<100;i++)
    {
        //data = gen_random(5);
        data = gen_random();
       // cout << index++ <<"\t"<< data << endl;
        myfile << data << endl;
    }

    myfile.close();

    return 0;
}
