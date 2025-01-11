#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Fonction.h"

/* Les membres de group :
    BAAZIZ Abderraouf 181833021936
    Khoukhi Aymen 191933020665
    Berdja Maria 191931086899
    Sabrina Khemamil 171731077726
    */

int main()
{
	chaine ch;
	TabCh Tab;
	int b;
    pile p;

	do
	{
		printf("Donner une formule arethmetique : \n");
		gets(ch);

		Tab = remplicage(ch);
	    b = Tab.b;
    }while(b == 0);
    
        p = postfixe(Tab);
        Evaluation(p);

        return 0;
}
