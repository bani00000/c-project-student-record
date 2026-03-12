#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct prisoner
{
    char id[10];
    char name[30];
    int age;
    char gender[10];
    char crime[50];
    char court[30];
    char lawyer[30];
    char nid[30]
};

void add();
void view();
void search();
void edit();
void delete_record();
void login();

void clear_all_records();
struct prisoner p;

int main()
{
    int ch;

    login();

    while(1)
    {
        printf("\n\n===== PRISON MANAGEMENT SYSTEM =====\n");
        printf("1. Add Record\n");
        printf("2. Search Record\n");
        printf("3. Edit Record\n");
        printf("4. View Records\n");
        printf("5. Delete Record\n");
        printf("6. Delete all Record\n");
        printf("7. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d",&ch);



        switch(ch)
        {
            case 1: add(); break;
            case 2: search(); break;
            case 3: edit(); break;
            case 4: view(); break;
            case 5: delete_record(); break;
            case 6: clear_all_records();
            case 7: exit(0);
            default: printf("Invalid Choice\n");
        }
    }

    return 0;
}

void login()
{
    char username[20];
    char password[20];

    printf("===== LOGIN SYSTEM =====\n");

    printf("Username: ");
    scanf("%s",username);

    printf("Password: ");
    scanf("%s",password);

    if(strcmp(username,"user")==0 && strcmp(password,"pass")==0)
    {
        printf("\nLogin Successful!\n");
    }
    else
    {
        printf("\nInvalid Login!\n");
        exit(0);
    }
}

void add()
{
    FILE *fp;
    char id_check[10];
    int found = 0;
    printf("\nEnter Prisoner ID: ");
    scanf("%s", id_check);

    fp = fopen("prison.dat","rb");

    if(fp != NULL)
    {
        while(fread(&p,sizeof(p),1,fp)==1)
        {
            if(strcmp(p.id,id_check)==0)
            {
                found = 1;
                break;
            }
        }
        fclose(fp);
    }

    if(found==1)
    {
        printf("\nID already exists! Record not added.\n");
        return;
    }

    fp = fopen("prison.dat","ab");

    strcpy(p.id,id_check);

    printf("Enter Name: ");
    scanf(" %[^\n]",p.name);

    printf("Enter Age: ");
    scanf("%d",&p.age);

    printf("Enter Gender (M/F/Other): ");
    scanf("%s",p.gender);

    printf("Enter Crime: ");
    scanf(" %[^\n]",p.crime);

    printf("Enter Court: ");
    scanf(" %[^\n]",p.court);

    printf("Enter Lawyer: ");
    scanf(" %[^\n]",p.lawyer);

    printf("Enter national id numbe: ");
    scanf(" %[^\n]",p.nid);


    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);

    printf("\nRecord Added Successfully!\n");
}

void view()
{
    FILE *fp;
    struct prisoner pr[500], temp;
    int i,j,c=0;

    fp = fopen("prison.dat","rb");

    while(fread(&pr[c],sizeof(struct prisoner),1,fp)==1)
    {
        c++;
    }

    fclose(fp);

    for(i=0;i<c-1;i++)
    {
        for(j=i+1;j<c;j++)
        {
            if(strcmp(pr[i].name,pr[j].name)>0)
            {
                temp=pr[i];
                pr[i]=pr[j];
                pr[j]=temp;
            }
        }
    }

    printf("\n===== PRISONER LIST =====\n");

    for(i=0;i<c;i++)
    {
        printf("\nID: %s",pr[i].id);
        printf("\nName: %s",pr[i].name);
        printf("\nAge: %d",pr[i].age);
        printf("\nGender: %s",pr[i].gender);
        printf("\nCrime: %s",pr[i].crime);
        printf("\nCourt: %s",pr[i].court);
        printf("\nLawyer: %s",pr[i].lawyer);
        printf("\n national id no: %s",pr[i].nid);
        printf("\n-------------------------\n");
    }
}
void search()
{
    FILE *fp;
    char id[10], Nid[20], name[100], crime[100];
    int found = 0;
    int c;

    fp = fopen("prison.dat", "rb");
    if(fp == NULL)
    {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nSearch by:\n1. ID\n2. Name\n3. National ID\n4. Crime\nEnter your choice: ");
    scanf("%d", &c);

    switch(c)
    {
        case 1:
            printf("Enter Prisoner ID: ");
            scanf("%s", id);

            while(fread(&p, sizeof(p), 1, fp) == 1)
            {
                if(strcmp(p.id, id) == 0)
                {
                    found = 1;
                    break;
                }
            }
            break;

        case 2:
            printf("Enter Prisoner Name: ");
            scanf(" %[^\n]", name); // note the space

            while(fread(&p, sizeof(p), 1, fp) == 1)
            {
                if(strcmp(p.name, name) == 0)
                {
                    found = 1;
                    break;
                }
            }
            break;

        case 3:
            printf("Enter National ID: ");
            scanf("%s", Nid);

            while(fread(&p, sizeof(p), 1, fp) == 1)
            {
                if(strcmp(p.nid, Nid) == 0)
                {
                    found = 1;
                    break;
                }
            }
            break;

        case 4:
            printf("Enter Crime: ");
            scanf(" %[^\n]", crime);

            while(fread(&p, sizeof(p), 1, fp) == 1)
            {
                if(strcmp(p.crime, crime) == 0)
                {
                    found = 1;
                    break;
                }
            }
            break;

        default:
            printf("Invalid choice!\n");
            fclose(fp);
            return;
    }

    if(found)
    {
        printf("\nRecord Found!\n");
        printf("ID: %s\nName: %s\nAge: %d\nGender: %s\nCrime: %s\nCourt: %s\nLawyer: %s\n",
               p.id, p.name, p.age, p.gender, p.crime, p.court, p.lawyer);
    }
    else
    {
        printf("\nRecord Not Found\n");
    }

    fclose(fp);
}

void edit()
{
    FILE *fp;
    char id[10];
    int found = 0;

    fp = fopen("prison.dat", "rb+");
    if(fp == NULL)
    {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Prisoner ID to edit: ");
    scanf("%s", id);

    while(fread(&p, sizeof(p), 1, fp) == 1)
    {
        if(strcmp(p.id, id) == 0)
        {
            found = 1;
            printf("\nRecord Found. Enter new details:\n");

            printf("Enter New Name: ");
            scanf(" %[^\n]", p.name);

            printf("Enter New Age: ");
            scanf("%d", &p.age);

            printf("Enter New Crime: ");
            scanf(" %[^\n]", p.crime);

            printf("Enter New Lawyer: ");
            scanf(" %[^\n]", p.lawyer);

            printf("Enter New Court: ");
            scanf(" %[^\n]", p.court);

            printf("Enter New National ID: ");
            scanf("%s", p.nid);

            fseek(fp, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, fp);

            printf("\nRecord Updated Successfully!\n");
            break;
        }
    }

    if(!found)
        printf("\nRecord Not Found!\n");

    fclose(fp);
}
void delete_record()
{
    FILE *fp,*temp;
    char id[10];

    fp = fopen("prison.dat","rb");
    temp = fopen("temp.dat","wb");

    printf("\nEnter Prisoner ID to delete: ");
    scanf("%s",id);

    while(fread(&p,sizeof(p),1,fp)==1)
    {
        if(strcmp(p.id,id)!=0)
        {
            fwrite(&p,sizeof(p),1,temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("prison.dat");
    rename("temp.dat","prison.dat");

    printf("\nRecord Deleted Successfully\n");
}
void clear_all_records()
{
    FILE *fp;

    fp = fopen("prison.dat","wb");  // wb clears the file

    if(fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fclose(fp);

    printf("\nAll records deleted successfully!\n");
}
