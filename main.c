#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#pragma pack(push, 1)
struct Vector
{
    double x;
    double y;
    double z;
};


struct OfluFile
{
    int id;
    struct Vector position;
};
#pragma pack(pop)

int HowManyDataExits(FILE *fl)
{
    fseek(fl, 0L, SEEK_END);
    int lastByte = ftell(fl);
    fseek(fl, 0L, SEEK_SET);
    return lastByte / sizeof(struct OfluFile);
}


void CreateFile()
{

    struct Vector p1 = {1.5,2,3};
    struct OfluFile f1 = {1,p1};

    struct Vector p2 = {11,42.5,3.1};
    struct OfluFile f2 = {2, p2};
    
    struct Vector p3 = {5.5,1.5,3.5};
    struct OfluFile f3 = {3, p3};

    struct OfluFile datas[3] = { f1,f2,f3 };


    FILE *file = fopen("test.oflu", "w");

    fwrite(&datas, sizeof(struct OfluFile), 3, file);



    fclose(file);
}

void ReadFile()
{
    FILE *file = fopen("test.oflu", "rb");

    // fseek belirtilen nokta burada 0L yani başından seed_end yani en sonuna kadar git diyoruz
    // ftell ise pointer'in hangi noktada olduğunu söylüyor bize yani burada en sona git dediğimiz için 
    // en son bayt da

    /*
    // bu kodlar ile beraber çalışamaz aşağıdaki kod çünkü kaykmış oluyor bulunduğu komut
    fseek(file, 0L, SEEK_END);
    long int fileSize = ftell(file);
    printf("uzunluk: %ld \n", fileSize);
    int itemCount = fileSize / sizeof(struct OfluFile);
    printf("file sayısı: %d \n", itemCount);
    // bu kod ile beraber aşağıdaki okuma kodları çalışabilir
    fseek(file, 0L, SEEK_SET);
    */
    
    // fread bir veir okudukdan sonra hemen sonraki için hazırlık yapar yani art arta yazarsan
    // sırayla bütün verileri çeker

    /*
    fread(&f, sizeof(struct OfluFile), 1, file);
    printf("Element id: %d \n" , f.id);
    fseek(file, 0L, SEEK_CUR);
    printf("Current byte: %ld \n", ftell(file));

    fread(&f, sizeof(struct OfluFile), 1, file);
    printf("Element id: %d \n" , f.id);
    fseek(file, 0L, SEEK_CUR);
    printf("Current byte: %ld \n", ftell(file));
    */

    int count = HowManyDataExits(file);
    struct OfluFile* datas = (struct OfluFile*)malloc(count* sizeof(struct OfluFile));
    fread(datas, sizeof(struct OfluFile), count, file);

    for (int i = 0; i < count; i++)
    {
        printf("Element id: %d \n", datas[i].id);
    }
    

    fclose(file);
}



int main()
{
    // tek tek kullan yoksa 
    // bellekten bilgileri aldığı için doğru çalışıp çalışmadığı belli olmuyor
    //CreateFile();
    ReadFile();
    return 0;
}