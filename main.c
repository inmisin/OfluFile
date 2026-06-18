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


struct MyFile
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
    return lastByte / sizeof(struct MyFile);
}


void CreateFile()
{

    struct Vector p1 = {1.5,2,3};
    struct MyFile f1 = {1,p1};

    struct Vector p2 = {11,42.5,3.1};
    struct MyFile f2 = {2, p2};
    
    struct Vector p3 = {5.5,1.5,3.5};
    struct MyFile f3 = {3, p3};

    struct MyFile datas[3] = { f1,f2,f3 };


    FILE *file = fopen("test.oflu", "wb");

    fwrite(&datas, sizeof(struct MyFile), 3, file);



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
    struct MyFile* datas = (struct MyFile*)malloc(count* sizeof(struct MyFile));
    fread(datas, sizeof(struct MyFile), count, file);

    for (int i = 0; i < count; i++)
    {
        printf("ID: %d, Vector: x: %.2f y: %.2f z: %.2f \n", datas[i].id, datas[i].position.x, datas[i].position.y, datas[i].position.z);
    }
    

    fclose(file);
}

void AddValue()
{
    struct MyFile data;
    printf("Type new position:\n");
    printf("Type X: ");
    scanf("%lf",&data.position.x);
    printf("\nType Y: ");
    scanf("%lf",&data.position.y);
    printf("\nType Z: ");
    scanf("%lf",&data.position.z);
    FILE *file = fopen("test.oflu", "a");
    int count = HowManyDataExits(file);
    data.id = count+1;
    fwrite(&data, sizeof(struct MyFile), 1, file);
    
    fclose(file);
}

void DeleteValue()
{
    printf("Type ID to delete: ");
    int dID;
    scanf("%d", &dID);
    FILE *file = fopen("test.oflu", "rb+");
    int count = HowManyDataExits(file);

    struct MyFile* datas = (struct MyFile*)malloc(count * sizeof(struct MyFile));
    struct MyFile* newDatas = datas;


    fread(datas, sizeof(struct MyFile),count, file);
    fclose(file);

    int newCount = 0;
    for (int i = 0; i < count; i++)
    {
        if(datas[i].id != dID)
        {
            *newDatas = datas[i];
            newDatas++;
            newCount++;
        }
        
    }

    // pointer kaydırması yaptığımız için burada kaydırdığımız kadar geri alıyoruz ki
    // ilk adresten itibaren dosyaya yazabilelim
    // burada herhangi bir değer ataması yapılmıyor sadece adres en başataki haline geliyor
    newDatas = datas;
    


    file = fopen("test.oflu", "wb");
    

    fwrite(newDatas, sizeof(struct MyFile), newCount, file);
    fclose(file);
    free(datas);
}

void ChooseOperation()
{
    int op =
    printf("Please choose an operation\n");
    printf("1. Create a file\n");
    printf("2. Add new value\n");
    printf("3. Read a value\n");
    printf("4. Delete a value\n");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        CreateFile();
        break;
    case 2:
        AddValue();
        break;
    case 3:
        ReadFile();
        break;
    case 4:
        DeleteValue();
        break;
    default:
        printf("Wut?");
        break;
    }
}


int main()
{
    // tek tek kullan yoksa 
    // bellekten bilgileri aldığı için doğru çalışıp çalışmadığı belli olmuyor
    //CreateFile();
    //ReadFile();

    ChooseOperation();
    

    return 0;
}