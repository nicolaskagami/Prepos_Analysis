//Nicolas Silveira Kagami

#include "sdc.h"

void sdcRead(char * sdcFileName)
{
    sdcFile = fopen(sdcFileName,"r");
    if(sdcFile)
    {
        numberClocks = 0;
        sdcCreateClk();
        sdcSetInputDelay();
        sdcSetMaxDelay();
        sdcClksPrint();
    }
}

void sdcCreateClk()
{ 
    char line[MAX_LINE];
    char * aux;
    char * aux2;
    fpos_t position;

    do
    {
        fgetpos (sdcFile, &position);
        if(fgets(line,MAX_LINE,sdcFile))
        {
            aux = strtok(line," \n");
            if(aux && strcmp(aux,"create_clock")==0)
            {
                aux2 = strtok(NULL," \n");
                aux2 = strtok(NULL," \n");
                clocks[numberClocks].period = strtof(aux2,NULL);
                aux2 = strtok(NULL," \n");
                aux2 = strtok(NULL," \n");
                strcpy(clocks[numberClocks].name, aux2);
                numberClocks++;
            }
            else
            { 
                fsetpos (sdcFile, &position);
                aux = NULL;
            }
        }
        else
        {
            fsetpos (sdcFile, &position);
            aux = NULL;
        }
    }
    while(!feof(sdcFile) && aux);

}

void sdcSetInputDelay()
{
    char line[MAX_LINE];
    char * aux;
    char * aux2;
    float delay;
    int clock;
    int input;
    fpos_t position;
    
    do
    {
        fgetpos (sdcFile, &position);
        if(fgets(line,MAX_LINE,sdcFile))
        {
            aux = strtok(line," \n");
            if(aux && strcmp(aux,"set_input_delay")==0)
            {
                aux2 = strtok(NULL," \n");
                delay = strtof(aux2,NULL);
                aux2 = strtok(NULL," \n");
                aux2 = strtok(NULL," \n");
                clock = sdcClkSearch(aux2);
                if(clock != -1)
                {
                    aux2 = strtok(NULL," \n");
                    input = aagFindSignal(aux2);
                    if(input)
                    {
                        signals[input].delay = delay;
                    }
                }
            }
            else
            {
                fsetpos (sdcFile, &position);
                aux = NULL;
            }
        }
        else
        {
            fsetpos (sdcFile, &position);
            aux = NULL;
        }
    }
    while(!feof(sdcFile) && aux);

}

void sdcSetMaxDelay()
{
    char line[MAX_LINE];
    char * aux;
    char * aux2;
    float delay;
    int output;
    fpos_t position;

    
    do
    {
        fgetpos (sdcFile, &position);
        if(fgets(line,MAX_LINE,sdcFile))
        {
            aux = strtok(line," \n");
            puts(aux);
            if(aux && strcmp(aux,"set_max_delay")==0)
            {
                aux2 = strtok(NULL," \n");
                puts(aux2);
                delay = strtof(aux2,NULL);
                aux2 = strtok(NULL," \n");
                aux2 = strtok(NULL," \n");
                output = aagFindOutput(aux2);
                if(output != -1)
                {
                    outputs[output].maxdelay = delay;
                }
            }
            else
            {
                fsetpos (sdcFile, &position);
                aux = NULL;
            }
        }
        else
        {
            fsetpos (sdcFile, &position);
            aux = NULL;
        }
    }
    while(!feof(sdcFile) && aux);
}

void sdcClksPrint()
{
    int i;
    for(i=0;i<numberClocks;i++)
    {
        printf("Clock:");
        puts(clocks[i].name);
        printf("%f\n",clocks[i].period);
    }
}

int sdcClkSearch(char * name)
{
    int i;
    for(i=0;i<numberClocks;i++)
    {
        if(strcmp(name, clocks[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}

