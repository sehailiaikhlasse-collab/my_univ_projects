#include <stdio.h> //لاستعمال output,input, printf, scanf
#include <string.h>// للتعامل مع النصوص 
#include <stdbool.h>// لاستعمال true و false

// تعريف المتغيرات الثلاثة لكتابة تاريخ ميلاد الزبون
struct Date {
    int day, month, year;
};

// تعريف المتغيرات الخاصة ببيانات الزبون
struct Client {
    int id; //رقم الهوية الخاص بالزبون 
    char name[30];//  لقب الزبون من 30    حرف
    char firstName[30];// اسم الزبون من 30 حرف
    struct Date birthDate;// تاريخ ميلاد الزبون بإستخدام struct date  الذي عرفناها سابقا
    char address[50];//عنوان سكن الزبون من 50 حرف
    char tel[15];// رقم هاتف الزبون من 15 رقم 
};

// تعريف المتغيرات الخاصة ببيانات الحساب البنكي
struct Account {
    int clientId; // يمثل رقم الزبون (الزبون رقم كم)
    char accountType; // خاص بأحد المتغيرات P,M,C 
    int balance; // الرصيد المالي الحالي
    bool blocked; //   false او عاطل true حالة الحساب يعمل 
};

//تعريف المتغيرات التي تمثل المعلومات العامة للزبائن
struct Client clients[100];// مكان قائمة الزبائن 
struct Account accounts[100];//  مكان أرصدة الزبائن
int clientCount = 0; // هذا المتغير يحسب كم زبون أضفنا حتى الآن

//الدالة التي تجعل المستخدم هو التي يدخل المعلومات 
void addClient()//اخبار الحاسوب للقيام بالعمليات التي داخل الة addclient وهي اضافة زبون 
{
    printf("--- Register a new customer---\n");
    
    printf("Enter the ID number: ");
    scanf("%d"//اخبار الحاسوب ان المستخدم سيدخل عددا صحيحا وليس شيء اخر
        , &clients[clientCount].id);// مسار الرقم انه يذهب للمصفوفةclients  ويبحث عن مكان Id ويضعه هناك
    
    printf("Enter the last name: ");
    scanf("%s" // اخبار الحاسوب ان المستخدم سيدخل نصا وليس شيء اخر
        , clients[clientCount].name);
    
    printf("Enter the first name: ");
    scanf("%s", clients[clientCount].firstName);
        clientCount++;    // بعد ما نكملوا تعمير البيانات، نزيدو 1 للعداد باش الزبون الجاي يروح للخانة اللي بعدها

}
int main() {
    addClient();    // استدعاء الدالة لتجربتها

    
    return 0;
}