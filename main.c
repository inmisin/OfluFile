#include <stdio.h>
#include <string.h>

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
    struct OfluFile f1;
    struct Vector p1;
    p1.x = 1.5;
    p1.y = 2.5;
    p1.z = 3.5;
    f1.id = 1;
    f1.position = p1;

    struct OfluFile f2;
    struct Vector p2;
    p2.x = 11;
    p2.y = 42.5;
    p2.z = 3.1;
    f2.id = 2;
    f2.position = p2;

    struct OfluFile f3;
    struct Vector p3;
    p3.x = 5.5;
    p3.y = 1.5;
    p3.z = 3.5;
    f3.id = 3;
    f3.position = p3;

    struct OfluFile f4;
    struct Vector p4;
    p4.x = 5.5;
    p4.y = 1.5;
    p4.z = 3.5;
    f4.id = 4;
    f4.position = p4;

    struct OfluFile f5;
    struct Vector p5;
    p5.x = 5.5;
    p5.y = 1.5;
    p5.z = 3.5;
    f5.id = 5;
    f5.position = p5;

    struct OfluFile f6;
    struct Vector p6;
    p6.x = 5.5;
    p6.y = 1.5;
    p6.z = 3.5;
    f6.id = 6;
    f6.position = p6;

    FILE *file = fopen("test.oflu", "w");

    fwrite(&f1, sizeof(struct OfluFile), 1, file);
    fwrite(&f2, sizeof(struct OfluFile), 1, file);
    fwrite(&f3, sizeof(struct OfluFile), 1, file);
    fwrite(&f4, sizeof(struct OfluFile), 1, file);
    fwrite(&f5, sizeof(struct OfluFile), 1, file);
    fwrite(&f6, sizeof(struct OfluFile), 1, file);


    fclose(file);
}

void ReadFile()
{
    struct OfluFile f;
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
    for (int i = 0; i < count; i++)
    {
        fread(&f, sizeof(struct OfluFile), 1, file);
        printf("Element id: %d \n" , f.id);
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