#include <stdio.h>
#include <time.h>


int main()
{
    int dia,mes,ano;
    long importancia;
    time_t atual;
    struct tm str_time;
    time_t time_of_day;
    printf("defina data da deadline, no formato dd/mm/yyyy\n");
    scanf("%d/%d/%d",&dia,&mes,&ano);
    str_time.tm_year = ano-1900;
    str_time.tm_mon = mes-1;
    str_time.tm_mday = dia;
    str_time.tm_hour = 0;
    str_time.tm_min = 0;
    str_time.tm_sec = 0;
    str_time.tm_isdst = 0;

    time_of_day = mktime (&str_time);
//	printf(ctime(&time_of_day));
//  printf("seconds fake data is %ld \n",time_of_day);
    atual = time (NULL);
//    printf(ctime(&atual));
//    printf ("Number of seconds since January 1, 1970 is %ld \n", atual);

    importancia = (time_of_day)-(atual);
    printf ("importancia relativa = %ld",importancia);
    return (importancia);
}
