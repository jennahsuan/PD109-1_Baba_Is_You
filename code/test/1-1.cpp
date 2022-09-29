#include <iostream>
using namespace std;

int main()
{
int tickAdu = 0, priAdu = 0, tickStu = 0, priStu = 0,
    money = 0, limit = 0;
cin >> tickAdu >> priAdu >> tickStu >> priStu >> money >> limit;

if((tickAdu + tickStu) > limit)
	cout << -1;  // ���ƶW�L�W�� 
else
	if(tickAdu * priAdu + tickStu * priStu > money)
		cout << -2;  // ������ 
	else
		cout << money - tickAdu * priAdu - tickStu * priStu;  //  �l�B 

return 0;
}
