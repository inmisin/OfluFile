#include <stdio.h>
#include <string.h>


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

    FILE *file = fopen("test.oflu", "w");

    fwrite(&f1, sizeof(struct OfluFile), 1, file);
    fwrite(&f2, sizeof(struct OfluFile), 1, file);
    fwrite(&f3, sizeof(struct OfluFile), 1, file);


    fclose(file);
}

void ReadFile()
{
    struct OfluFile f;
    FILE *file = fopen("test.oflu", "r");

    fread(&f, sizeof(struct OfluFile), 2, file);
    
    printf("What's written in the file is: %d \n" , f.id);

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