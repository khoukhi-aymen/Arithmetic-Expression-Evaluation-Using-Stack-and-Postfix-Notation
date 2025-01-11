#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Fonction.h"

pile Cree_noeud()
{
    pile aux;
    aux = NULL;
    aux =(pile)malloc(sizeof(noeud));
    if(aux == NULL)
    {
        printf("\nerreur,bloc non reservé\n");
        exit(-1);
    }
    return aux;

}


char* sommet_pile(pile p)
{
    char* x;
    x = p->val;
    return(x);

}


void Empile(pile* p,chaine x)
{
    pile tmp;

    tmp  =  Cree_noeud();
    strcpy(tmp->val, x);
    tmp->svt = *p;
    *p = tmp;
}


CHAIN Depiler(pile* p)
{
    CHAIN x;
    pile tmp;

    strcpy(x.ELm,(*p)-> val);
    tmp = *p;
    *p = (*p) -> svt;

    free(tmp);

    return x;
}


int pile_vide(pile p)
{
    if(p == NULL)
    {
        return 1;

    }
    else
    {
        return 0;
    }

}


int operande(chaine x)
{
    int i;

    for(i = 0 ; i < strlen(x) ; i++)
    {
        if(!isdigit(x[i]) && x[i] != '.')
        {
            return 0;

        }

    }
    return 1;

}


int operateur(chaine x)
{
    chaine a ="+";
    chaine b ="-";
    chaine c ="*";
    chaine d = "%";
    chaine e ="/";

    int i;
    for(i = 0 ; i < strlen(x) ; i++)
    {
    if ((strcmp(x,a) != 0) && (strcmp(x,b) != 0) && (strcmp(x,c) != 0) && (strcmp(x,d)  != 0) && (strcmp(x,e) != 0))
    {
        return 0;
    }
    }
    return 1;
}


int priorite(chaine x)
{
    chaine f ="+";
    chaine g ="-";
    chaine h ="*";
    chaine i = "%";
    chaine j ="/";
    int b; 
    if( strcmp(x,f) == 0 || strcmp(x,g) == 0 )
    {
        b= 0;
    }
    if(strcmp(x,h) == 0 || strcmp(x,i) == 0 || strcmp(x,j) == 0)
    {
        b= 1;
    }

    return b;
}


double operation(chaine x1,chaine x2,chaine x)
{
    double result;
    int con1,con2 ;
    double convert1,convert2;

    convert1 = atof(x1);
    convert2 = atof(x2);

    char c;
    c = x[0];
    if(c == '+')
    {
        result = convert2 + convert1;

    }
    if(c == '-')
    {
        result = convert2 - convert1;
    }
    if(c == '*')
    {
        result = convert2 * convert1;
    }
    if(c == '/')
    {
        result = convert2 / convert1;
    }
    if(c == '%')
    {
        con1 = atoi(x1);
        con2 = atoi(x2);
        con2 = con2 % con1;
        result = (double)con2;
    }
    return result;

}


pile postfixe(TabCh Tab)
{
    pile p,R;
    p = NULL;
    R = NULL;
    chaine z = "(";
    chaine y = ")";
    int i,n;
    CHAIN x1;
    chaine x;
    TabChaine T;

    n = Tab.taill;
    for (i = 0; i < n  ; ++i)
	{
		strcpy(T[i],Tab.val[i]);
	}

    for(i = 0 ; i < n ; i++)
    {
        if(operande(T[i]) == 1)
        {
            Empile(&R,T[i]);

        }
        if(strcmp(T[i],z) == 0)
        {
            Empile(&p,T[i]);


        }
        if(operateur(T[i]) == 1)
        {
            while( (!pile_vide(p)) && (operateur(sommet_pile(p)) == 1) && (priorite(T[i]) <= priorite(sommet_pile(p)) ))
            {
                x1 = Depiler(&p);
                strcpy(x,x1.ELm);
                Empile(&R,x);

            }
            Empile(&p,T[i]);
        }

        if(strcmp(T[i],y) == 0)
        {
            while ( (!pile_vide(p)) && (strcmp(sommet_pile(p),z) != 0) )
            {
                x1 = Depiler(&p);
                strcpy(x,x1.ELm);
                Empile(&R,x);
            }
            x1 = Depiler(&p);
            strcpy(x,x1.ELm);
        }

    }


    while(!pile_vide(R))
    {
        x1 =  Depiler(&R);
        strcpy(x,x1.ELm);
        Empile(&p,x);
    }

    printf("\nla methode fixee : \n|");
    Affiche_pile(p);
    printf("\n");

    return p;
}


double Evaluation(pile p)
{
    double res ;
    chaine resultat;
    double convertit;

    chaine x,x1,x2;
    CHAIN X;

    pile R = NULL;

    while (!pile_vide(p))
    {
        X = Depiler(&p);
        strcpy(x,X.ELm);
        if(operande(x))
        {
            Empile(&R,x);
        }
        else
        {
            X = Depiler(&R);
            strcpy(x1,X.ELm);

            X = Depiler(&R);
            strcpy(x2,X.ELm);

            res = operation(x1,x2,x);
          	sprintf(resultat,"%f",res);
            Empile(&R,resultat);
        }

    }
    X = Depiler(&R);
    convertit = atof(X.ELm);
    printf("\n Tres bien! voila le resultat : \n -> %2.2f <- \n",convertit);

    return convertit;
}


void Affiche_pile(pile p)
{

    while(p != NULL)
    {
        printf(" %s |",p->val);
        p = p->svt;
    }

}


pile Tab_To_pile(TabChaine T, int j)
{
	pile p;
	int i ;
	p= NULL;

	for (i = j; i >=0 ; i--)
	{

	 	Empile(&p,T[i]);

	}

	return p;
}


int si_oper(char c)
	{
		if ((c >= '0') && (c <= '9'))
		{
			return 1;
		}
		else{
			if (c == '.')
			{
				return 1;
			}
			else{
				return 0;
			}
		}
	}


int si_opera(char c)
	{
		if (c =='+' || c =='-' || c=='*' || c =='/' || c =='%')
		{
			return 1;
		}
		else{
			return 0;
		}

	}

int si_paro(char c)
	{
		if(c=='(' || c == ')')
		{
			return 1;
		}
		else{
			return 0;
		}
	}

TabCh remplicage(chaine ch)
	{
		TabChaine T;
		TabCh T1;
		CHAIN STR;

		int i,b,j;
		b=1;
		j=0;

		STR = if_blanks(ch);
		ch = STR.ELm;

		if (si_opera(ch[0])==1 || si_paro(ch[0])==1)
		{
			char str[3];
			str[0] = ch[0];
			str[1] = '\0';

		 	strcpy(T[0],str);
		 	j++;
		 	T[j][0]= '\0' ;
		}
		else
		{
			if (si_oper(ch[0])==1)
			{
				char str[3];
				str[0] = ch[0];
				str[1] = '\0';

			 	strcpy(T[0],str);
			 	if (si_opera(ch[1])==1 || si_paro(ch[1])==1)
			 	{
			 		j++;
			 	}
		 	}
		 	else
		 	{
		 		b=0;

		 	}

		}

		for (i = 1; i < strlen(ch); ++i)
		{
			if (si_opera(ch[i])==1 || si_paro(ch[i])==1)
				{
					char str[3];
					str[0] = ch[i];
					str[1] = '\0';

				 	strcpy(T[j],str);
				 	j++;
				 	T[j][0]= '\0';
				 	if ( (si_opera(ch[i+1])==1)&&(si_paro(ch[i])==0)&&( (ch[i+1])!='-')&&((ch[i+1])!='+'))
				 	{
				 		b=0;
				 	}

				}
				else {
					if (si_oper(ch[i])==1)
						{

						char str[3];
						str[0] = ch[i];
						str[1] = '\0';

						strcat(T[j],str);

					 	if (si_opera(ch[i+1])==1 || si_paro(ch[i+1])==1)
					 	{
					 		j++;
					 	}
					 	}
					 else
					 {
					 	b=0;
					 }
				}
		}
		if (si_opera(ch[i-1])) 
		{
				b=0;
		}

		if (b==1)
		{	
			if (si_paro(ch[i-1])) 
			{
				T1.taill = j;
			}
			else
			{
				T1.taill = j+1;
			}

			for (i = 0; i <= T1.taill; ++i)
			{
				strcpy(T1.val[i],T[i]);
			}
			b = verif_parenthese(ch);
			if (b==1)
			{
				printf("\n");
				printf("Le Tableux des chaines characters : \n|");
				for (i = 0; i < T1.taill  ; ++i)
					{
						printf(" %s |",T1.val[i] );
					}
				printf("\n");
			}
			else
			{
				printf("error de paronthes ...try again\n");
			}

		}
		else
		{
			printf("%s verfier votre formule slv...et repeter .\n",ch );
		}

	T1.b = b;
	return T1;
	}

CHAIN if_blanks(chaine ch)
	{
		int i,j,nb;
		CHAIN str;
	do
	{
		nb= 0;
		for (i = 0; i < strlen(ch); ++i)
		{
			if(ch[i]== ' ')
			{
				nb=nb+1;
				for (j = i; j <strlen(ch) ; ++j)
					{
						ch[j]= ch[j+1];
					}
			}
		}
		strcpy(str.ELm,ch);
	}while(nb != 0);
		return str;
	}


int verif_parenthese(chaine T)
{
	int E=0,I=0;
	while (T[I] !='\0')
	{
		if (T[I] == '(') {
		 E++;
		}else{
			if(T[I] == ')'){
				E--;
				  if (E<0){
				  	return 0;

		              	}
			}
	}
	I++;
   }
if(E == 0){
	return 1;
	}else{
		return 0;
    }
}
