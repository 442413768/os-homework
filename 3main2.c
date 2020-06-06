#include<stdio.h>

void myffs(const char *input,const char *output);
void myffgetc(const char *input,const char *output);
void myffgets(const char *input,const char *output);

int main()
{
        //printf("hehe");
        myffs("test_input","test_output");
        myffgetc("test_input","test_output");
        myffgets("test_input","test_output");
}
void myffs(const char *input,const char *output)
{
        //printf("here!");
        FILE *flag1 = fopen(input,"r");
        FILE *flag2 = fopen(output,"w");
        char file[1024];
        if(flag1==NULL)
        {
                printf("Errors!Can't open the input file \n");
                return ;
        }
        if(flag2 == NULL)
        {
                printf("Errors!Can't open the output file \n");
                return ;
        }
        while(1)
        {
                if(fscanf(flag1,"%s",file)==EOF)
                {
                        break;
                }
                else
                {
                        fprintf(flag2,"%s",file);
                }
        }
        fclose(flag1);
        fclose(flag2);
        printf("Method: fscanf & fprintf finished!\n");
}
void myffgetc(const char *input,const char *output)
{
        FILE *flag1 = fopen(input,"r");
        FILE *flag2 = fopen(output,"w");
        char file[1024];
        char ch;
        if(flag1==NULL)
        {
                printf("Errors!Can't open the input file \n");
                return ;
        }
        if(flag2 == NULL)
        {
                printf("Errors!Can't open the output file \n");
                return ;
        }
        while(1)
        {
                ch = fgetc(flag1);
                if(ch==EOF)
                {
                         break;
                }
                else
                {
                        fputc(ch,flag2);
                }
        }
        fclose(flag1);
        fclose(flag2);
        printf("Method: fgetc & fputc  finished!\n");

}
void myffgets(const char *input,const char *output)
{
        FILE *flag1 = fopen(input,"r");
        FILE *flag2 = fopen(output,"w");
        char file[1024];
        if(flag1==NULL)
        {
                printf("Errors!Can't open the input file \n");
                return ;
        }
        if(flag2 == NULL)
        {
                printf("Errors!Can't open the output file \n");
                return ;
        }
        while(1)
        {
                if(fgets(file,1024,flag1)==NULL)
                {
                          break;
                }
                else
                {
                          fputs(file,flag2);
                }
        }                                                                                             
        fclose(flag1);
        fclose(flag2);
        printf("Method: fgets&fputs finished!\n");
}
