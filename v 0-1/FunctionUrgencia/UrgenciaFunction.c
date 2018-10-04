#include <stdio.h>
#include <time.h>


long Urgencia(int dia, int mes, int ano)
{
    long importancia;
    time_t atual;
    struct tm str_time;
    time_t time_of_day;

    str_time.tm_year = ano-1900;
    str_time.tm_mon = mes-1;
    str_time.tm_mday = dia;
    str_time.tm_hour = 0;
    str_time.tm_min = 0;
    str_time.tm_sec = 0;
    str_time.tm_isdst = 0;

    time_of_day = mktime (&str_time);
    atual = time (NULL);
    importancia = (time_of_day)-(atual);
    return (importancia);
}

int main()
{
    int dia,mes,ano;
    printf("defina a data no estilo dd/mm/yyyy\n");
    scanf("%d/%d/%d",&dia,&mes,&ano);
    printf("urgencia = %ld",Urgencia(dia,mes,ano));

}
